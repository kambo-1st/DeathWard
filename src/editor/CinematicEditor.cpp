#include "editor/CinematicEditor.hpp"
#include "raymath.h"
#include <cctype>
#include <iomanip>
#include <sstream>

namespace dw {
namespace {
constexpr Color Background{17,23,26,255}, Panel{26,34,36,248}, Line{59,73,73,255},
    Paper{236,226,201,255}, Muted{147,161,153,255}, Gold{224,168,86,255}, Teal{112,204,180,255};
constexpr const char *Tracks[] = {"CAMERA", "SANDSTORM", "TRAIN", "SOUND"};
constexpr Color TrackColors[] = {{112,204,180,255},{224,168,86,255},{147,170,223,255},{218,142,176,255}};
std::string decimal(float value, int places = 1) {
    std::ostringstream out; out << std::fixed << std::setprecision(places) << value; return out.str();
}
} // namespace
bool CinematicEditor::open(const std::filesystem::path &directory, Camera3D view,
                           const TownDocument *snapshot, const std::filesystem::path &file) {
    unload();
    try {
        directory_ = directory;
        file_ = file.empty() ? directory / "arrival.cinematic" : file;
        filenameText_ = file_.filename().string();
        if (!scene_.load(directory)) throw std::runtime_error("Cannot load the cinematic's town scene.");
        world_ = snapshot ? *snapshot : scene_.document();
        scene_.applyDocument(world_);
        navigation_.load(directory / "town.nav");
        ground_.load(directory / "town.nav");
        audioDirectory_ = std::filesystem::path(DEATHWARD_ASSET_DIR) / "audio";
        if (!std::filesystem::is_directory(audioDirectory_)) audioDirectory_ = std::filesystem::path(GetApplicationDirectory()) / "assets/audio";
        soundFiles_.clear();
        if (std::filesystem::exists(audioDirectory_))
            for (const auto &entry : std::filesystem::recursive_directory_iterator(audioDirectory_))
                if (entry.is_regular_file() && (entry.path().extension() == ".wav" || entry.path().extension() == ".ogg"))
                    soundFiles_.push_back(std::filesystem::relative(entry.path(), audioDirectory_).generic_string());
        std::sort(soundFiles_.begin(),soundFiles_.end());
        if (std::filesystem::exists(file_)) {
            if (!document_.load(file_,status)) throw std::runtime_error(status);
        } else document_ = Cinematic::demo(world_,view);
        document_.validate(&world_);
        undo_.clear(); redo_.clear(); revision_ = savedRevision_ = nextRevision_ = 0;
        if (!std::filesystem::exists(file_)) revision_ = ++nextRevision_;
        track_ = selected_ = 0; anchorChoice_ = -1;
        for (size_t i = 0; i < world_.groups.size(); ++i)
            if (world_.groups[i].id == document_.cameras.front().anchor) anchorChoice_ = int(i);
        closePrompt_ = closingWindow_ = quitRequested = editCamera_ = cleanPreview_ = filenameFocus_ = false;
        active = true;
        player_.reset(world_,document_,[&](Vector3 p) { return navigation_.height(p); });
        actorsTime_=-1;syncActors();
        status = "Cinematic preview only. The town and campaign stay untouched.";
        return true;
    } catch (const std::exception &e) { status = e.what(); active = false; return false; }
}
void CinematicEditor::unload() {
    audio_.stop(); scene_.unload(); post_.unload(); characterModels_.unload(); animalModels_.unload();
    active = false;
    draggingKey_=keyDragChanged_=scrubbing_=auditioning_=false;
}
void CinematicEditor::remember() {
    undo_.push_back({document_,revision_}); if (undo_.size() > 64) undo_.pop_front();
    redo_.clear(); revision_ = ++nextRevision_;
}
void CinematicEditor::syncActors() {
    if (actorsTime_ > player_.time() || actorsTime_ < 0) {
        characters_.reset(world_,ground_); animals_.reset(world_.animals,ground_); actorsTime_ = 0;
    }
    // Fixed steps make the same timeline frame reproducible after a rewind.
    while (actorsTime_ + 1.0/60 <= player_.time() + 1e-6) {
        characters_.update(Tick,ground_); animals_.update(Tick,ground_); actorsTime_ += 1.0/60;
    }
    scene_.applyAnimation(player_.animation());
    if (!editCamera_) view_ = player_.camera();
}
void CinematicEditor::rebuild() {
    const float time = std::min(player_.time(),document_.duration);
    audio_.stop(); auditioning_=false; document_.sort();
    try {
        player_.reset(world_,document_,[&](Vector3 p) { return navigation_.height(p); });
        player_.seek(time); actorsTime_ = -1; syncActors();
    } catch (const std::exception &e) { status = e.what(); }
}
void CinematicEditor::seek(float seconds) {
    audio_.stop(); auditioning_=false; player_.seek(seconds); editCamera_ = false; syncActors();
}
void CinematicEditor::play() {
    if(auditioning_) {audio_.stop();auditioning_=false;}
    editCamera_ = false;
    if (player_.playing()) player_.pause(); else player_.play();
}
bool CinematicEditor::save() {
    if (document_.save(file_,status)) { savedRevision_ = revision_; status = "Saved " + file_.string(); return true; }
    return false;
}
void CinematicEditor::undo(bool redo) {
    auto &from = redo ? redo_ : undo_; auto &to = redo ? undo_ : redo_;
    if (from.empty()) return;
    to.push_back({document_,revision_}); document_ = from.back().first; revision_ = from.back().second;
    from.pop_back(); selected_ = -1; rebuild();
}
void CinematicEditor::requestClose(bool quit) {
    player_.pause(); audio_.stop(); closingWindow_ |= quit;
    if (dirty()) closePrompt_ = true;
    else { active = false; quitRequested = closingWindow_; }
}
size_t CinematicEditor::keyCount(int track) const {
    switch (track) { case 0:return document_.cameras.size(); case 1:return document_.weather.size();
                    case 2:return document_.trains.size(); default:return document_.sounds.size(); }
}
float CinematicEditor::keyTime(int track, size_t n) const {
    switch (track) { case 0:return document_.cameras[n].time; case 1:return document_.weather[n].time;
                    case 2:return document_.trains[n].time; default:return document_.sounds[n].time; }
}
void CinematicEditor::setKeyTime(int track, size_t n, float time) {
    switch (track) { case 0:document_.cameras[n].time=time;break; case 1:document_.weather[n].time=time;break;
                    case 2:document_.trains[n].time=time;break; default:document_.sounds[n].time=time;break; }
}
void CinematicEditor::changeTime(float time) {
    if (selected_ < 0 || size_t(selected_) >= keyCount(track_)) return;
    float low = 0, high = document_.duration;
    if (selected_ > 0) low = keyTime(track_,size_t(selected_-1)) + (track_ < 2 ? .05f : 0);
    if (size_t(selected_+1) < keyCount(track_)) high = keyTime(track_,size_t(selected_+1)) - (track_ < 2 ? .05f : 0);
    setKeyTime(track_,size_t(selected_),std::clamp(time,low,high));
}
void CinematicEditor::addKey(int track) {
    const float time = player_.time();
    remember(); track_ = track;
    if (track == 0) {
        CameraKey key{time,view_.position,view_.target,view_.fovy,{}};
        if (anchorChoice_ >= 0) {
            key.anchor = world_.groups[size_t(anchorChoice_)].id;
            const auto inverse = MatrixInvert(*player_.anchor(key.anchor));
            key.position = Vector3Transform(key.position,inverse); key.target = Vector3Transform(key.target,inverse);
        }
        auto found = std::find_if(document_.cameras.begin(),document_.cameras.end(),[&](const auto &k){return std::abs(k.time-time)<.05f;});
        if (found != document_.cameras.end()) { key.time=found->time; key.blend=found->blend; *found=key; }
        else document_.cameras.push_back(key);
    } else if (track == 1) {
        auto found = std::find_if(document_.weather.begin(),document_.weather.end(),[&](const auto &k){return std::abs(k.time-time)<.05f;});
        if (found != document_.weather.end()) found->amount=player_.storm();
        else document_.weather.push_back({time,player_.storm()});
    } else if (track == 2) document_.trains.push_back({time,0,12,"*"});
    else document_.sounds.push_back({time,"cinematic/train_brake.wav",.8f});
    document_.sort();
    selected_ = 0;
    for (size_t n = 0; n < keyCount(track); ++n)
        if (std::abs(keyTime(track,n)-time)<.05f) selected_=int(n);
    editCamera_ = false; rebuild();
}
void CinematicEditor::deleteKey() {
    if (selected_ < 0 || size_t(selected_) >= keyCount(track_) || (track_ == 0 && keyCount(0) == 1)) return;
    remember();
    switch (track_) { case 0:document_.cameras.erase(document_.cameras.begin()+selected_);break;
        case 1:document_.weather.erase(document_.weather.begin()+selected_);break;
        case 2:document_.trains.erase(document_.trains.begin()+selected_);break;
        default:document_.sounds.erase(document_.sounds.begin()+selected_);break; }
    selected_ = -1; rebuild();
}
void CinematicEditor::cameraPreset(bool interior) {
    if (world_.groups.empty()) { status="This scene has no train groups. Use the free camera."; return; }
    if (anchorChoice_ < 0 || interior) {
        anchorChoice_ = 0;
        for (const auto &i : world_.instances)
            if (world_.assets[i.asset].label.find("Carriage") != std::string::npos)
                for (size_t n=0;n<world_.groups.size();++n)
                    if (i.group == world_.groups[n].id) { anchorChoice_=int(n); break; }
    }
    player_.pause(); audio_.stop(); editCamera_ = true;
    const auto frame = *player_.anchor(world_.groups[size_t(anchorChoice_)].id);
    view_ = {Vector3Transform(interior?Vector3{-3,2.6f,0}:Vector3{10,7,14},frame),
             Vector3Transform(interior?Vector3{3,2.4f,0}:Vector3{0,2,0},frame),{0,1,0},interior?70.f:45.f,CAMERA_PERSPECTIVE};
    status="Position the camera, then Capture shot to keep this view.";
}
void CinematicEditor::attachCamera(int direction) {
    const int count=int(world_.groups.size())+1;
    anchorChoice_ = (anchorChoice_+1+direction+count)%count-1;
    if (track_ != 0 || selected_ < 0 || size_t(selected_) >= document_.cameras.size()) return;
    remember(); auto &key=document_.cameras[size_t(selected_)];
    if (auto old=player_.anchor(key.anchor)) {
        key.position=Vector3Transform(key.position,*old); key.target=Vector3Transform(key.target,*old);
    }
    key.anchor=anchorChoice_<0?"":world_.groups[size_t(anchorChoice_)].id;
    if (auto next=player_.anchor(key.anchor)) {
        const auto inverse=MatrixInvert(*next);
        key.position=Vector3Transform(key.position,inverse); key.target=Vector3Transform(key.target,inverse);
    }
    rebuild();
}
Vector2 CinematicEditor::mouse() const { auto p=GetMousePosition();return {p.x/sx_,p.y/sy_}; }
void CinematicEditor::label(const std::string &text,float x,float y,int size,Color color) const {
    DrawText(text.c_str(),int(x*sx_),int(y*sy_),std::max(9,int(size*sy_)),color);
}
void CinematicEditor::panel(Rectangle r,Color color) const {
    DrawRectangleRec({r.x*sx_,r.y*sy_,r.width*sx_,r.height*sy_},color);
}
bool CinematicEditor::button(const std::string &text,Rectangle r,bool selected,bool enabled) const {
    const bool hover=CheckCollisionPointRec(mouse(),r)&&!closePrompt_;
    panel(r,selected?Color{83,65,40,255}:hover&&enabled?Color{52,67,69,255}:Line);
    label(text,r.x+9,r.y+(r.height-15)*.5f,15,enabled?Paper:Muted);
    return enabled&&hover&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}
bool CinematicEditor::number(const std::string &name,float &value,float y,float step,float min,float max) {
    label(name,1130,y+7,14,Muted); label(decimal(value,2),1260,y+7,14,Paper);
    if(IsKeyDown(KEY_LEFT_SHIFT)||IsKeyDown(KEY_RIGHT_SHIFT)) step*=.1f;
    float next=value;
    if (button("-",{1344,y,32,29})) next-=step;
    if (button("+",{1382,y,32,29})) next+=step;
    next=std::clamp(next,min,max);
    if (next==value) return false;
    remember(); value=next; return true;
}
void CinematicEditor::update(float dt,const AudioSettings &audio) {
    sx_=float(GetScreenWidth())/1440;sy_=float(GetScreenHeight())/900;
    audioSettings_=audio;
    if (!active||closePrompt_) return;
    const bool ctrl=IsKeyDown(KEY_LEFT_CONTROL)||IsKeyDown(KEY_RIGHT_CONTROL);
    if (filenameFocus_) {
        for (int c=GetCharPressed();c;c=GetCharPressed())
            if ((c<128&&(std::isalnum(static_cast<unsigned char>(c))||c=='-'||c=='_'||c=='.'))&&filenameText_.size()<64) filenameText_+=char(c);
        if (IsKeyPressed(KEY_BACKSPACE)&&!filenameText_.empty()) filenameText_.pop_back();
        if (IsKeyPressed(KEY_ENTER)) {
            if (filenameText_.empty()||filenameText_=="."||filenameText_=="..") status="Enter a sequence filename.";
            else { if (!filenameText_.ends_with(".cinematic")) filenameText_+=".cinematic";
                file_=directory_/filenameText_;filenameFocus_=false; }
        }
        if (IsKeyPressed(KEY_ESCAPE)) { filenameFocus_=false;filenameText_=file_.filename().string(); }
        return;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        if (cleanPreview_) cleanPreview_=false; else requestClose();
        return;
    }
    if (ctrl&&IsKeyPressed(KEY_S)) save();
    if (ctrl&&IsKeyPressed(KEY_Z)) undo(IsKeyDown(KEY_LEFT_SHIFT)||IsKeyDown(KEY_RIGHT_SHIFT));
    if (ctrl&&IsKeyPressed(KEY_Y)) undo(true);
    if (IsKeyPressed(KEY_SPACE)) play();
    if (IsKeyPressed(KEY_HOME)) seek(0);
    if (IsKeyPressed(KEY_F11)) cleanPreview_=!cleanPreview_;
    if (IsKeyPressed(KEY_DELETE)) deleteKey();
    if (IsKeyPressed(KEY_LEFT)) seek(std::max(0.f,player_.time()-.1f));
    if (IsKeyPressed(KEY_RIGHT)) seek(std::min(document_.duration,player_.time()+.1f));
    const auto p=mouse();
    if (!cleanPreview_&&p.y>90&&p.y<640&&p.x<1110) {
        const auto delta=GetMouseDelta();const float wheel=GetMouseWheelMove();
        const bool fly=IsKeyDown(KEY_W)||IsKeyDown(KEY_A)||IsKeyDown(KEY_S)||IsKeyDown(KEY_D)||IsKeyDown(KEY_Q)||IsKeyDown(KEY_E);
        const bool look=IsMouseButtonDown(MOUSE_BUTTON_RIGHT)||IsMouseButtonDown(MOUSE_BUTTON_MIDDLE);
        if ((fly&&!ctrl)||(look&&(delta.x||delta.y))||wheel) {
            player_.pause();audio_.stop();editCamera_=true;
            Vector3 forward=unit(sub(view_.target,view_.position));
            float yaw=std::atan2(forward.x,forward.z),pitch=std::asin(std::clamp(forward.y,-1.f,1.f));
            const float focus=std::max(.5f,distance(view_.position,view_.target));
            if (look) { yaw-=delta.x*.004f;pitch=std::clamp(pitch-delta.y*.004f,-1.48f,1.48f); }
            forward={std::sin(yaw)*std::cos(pitch),std::sin(pitch),std::cos(yaw)*std::cos(pitch)};
            if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) view_.position=sub(view_.target,mul(forward,focus));
            else view_.target=add(view_.position,mul(forward,focus));
            const Vector3 right=unit(Vector3CrossProduct(forward,{0,1,0}));
            auto move=add(mul(forward,float(IsKeyDown(KEY_W))-float(IsKeyDown(KEY_S))),mul(right,float(IsKeyDown(KEY_D))-float(IsKeyDown(KEY_A))));
            move.y+=float(IsKeyDown(KEY_E))-float(IsKeyDown(KEY_Q));
            if (!ctrl) { const float speed=IsKeyDown(KEY_LEFT_SHIFT)?24.f:4.f;
                move=mul(move,std::min(dt,.1f)*speed);view_.position=add(view_.position,move);view_.target=add(view_.target,move); }
            view_.fovy=std::clamp(view_.fovy-wheel*2,10.f,110.f);
        }
    }
    if (draggingKey_) {
        const float time=std::round(std::clamp((p.x-155)/1230,0.f,1.f)*document_.duration*10)/10;
        if (std::abs(time-keyTime(track_,size_t(selected_)))>.051f) {
            if(!keyDragChanged_) {remember();keyDragChanged_=true;}
            changeTime(time);
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            draggingKey_=false;
            if(keyDragChanged_) {rebuild();seek(keyTime(track_,size_t(selected_)));}
        }
    }
    if (scrubbing_) {
        seek(std::clamp((p.x-155)/1230,0.f,1.f)*document_.duration);
        if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) scrubbing_=false;
    }
    const bool wasPlaying=player_.playing();
    player_.advance(std::min(dt,.1f));syncActors();
    if(wasPlaying&&!player_.playing()) audio_.stop();
    if(auditioning_) auditionTime_+=std::min(dt,.1f);
    audio_.update(auditioning_?auditionTime_:player_.time(),player_.playing()||auditioning_,audio,player_.takeSounds(),audioDirectory_);
    if(auditioning_&&!audio_.voices())auditioning_=false;
    if (!audio_.error.empty()) { status=audio_.error;audio_.error.clear(); }
}
void CinematicEditor::inspector() {
    panel({1110,88,330,552},Panel);
    label("SHOT / EVENT",1130,107,21,Gold);
    if (button("Wide train",{1130,144,135,32},false,!world_.groups.empty())) cameraPreset(false);
    if (button("Inside carriage",{1275,144,145,32},false,!world_.groups.empty())) cameraPreset(true);
    if (button("<",{1130,188,30,30})) attachCamera(-1);
    if (button(">",{1388,188,30,30})) attachCamera(1);
    label(anchorChoice_<0?"Anchor: world":"Anchor: vehicle "+std::to_string(anchorChoice_+1),1168,196,14,Teal);
    label("FOV "+decimal(view_.fovy)+" deg",1130,229,14,Paper);
    if (selected_<0||size_t(selected_)>=keyCount(track_)) { label("Select a timeline key.",1130,275,16,Muted);return; }
    label(Tracks[track_],1130,265,18,TrackColors[track_]);
    float time=keyTime(track_,size_t(selected_));
    if (number("Time (sec)",time,297,.25f,0,document_.duration)) { changeTime(time);rebuild(); }
    bool changed=false;
    if (track_==0) {
        auto &key=document_.cameras[size_t(selected_)];
        changed|=number("FOV (zoom)",key.fov,334,2,10,110);
        const char *blend=key.blend==CameraBlend::Smooth?"Smooth":key.blend==CameraBlend::Linear?"Linear":"Cut";
        if (button(std::string("To next: ")+blend,{1130,375,286,32})) { remember();key.blend=CameraBlend((int(key.blend)+1)%3);changed=true; }
        if (button("View selected shot",{1130,423,286,32})) seek(key.time);
        if (button("Capture current camera",{1130,465,286,32})) addKey(0);
        label("Move the free camera in the viewport",1130,520,12,Muted);
        label("then capture it at the playhead.",1130,541,12,Muted);
        label("Wheel changes lens zoom.",1130,566,13,Muted);
    } else if (track_==1) {
        changed|=number("Strength",document_.weather[size_t(selected_)].amount,340,.1f,0,1);
        label("0 = clear, 1 = full sandstorm",1130,395,14,Muted);
        label("Weather blends between its keys.",1130,422,13,Muted);
    } else if (track_==2) {
        auto &key=document_.trains[size_t(selected_)];
        changed|=number("Speed (m/s)",key.speed,340,1,0,40);
        changed|=number("Accel / brake",key.acceleration,380,1,.1f,40);
        if (button("Emergency stop",{1130,429,286,34})) { remember();key.speed=0;key.acceleration=12;changed=true; }
        if (button("Route: "+key.path,{1130,477,286,34},false,!world_.paths.empty())) {
            remember();
            auto found=std::find_if(world_.paths.begin(),world_.paths.end(),[&](const auto &p){return p.id==key.path;});
            key.path=found==world_.paths.end()?world_.paths.front().id:
                     std::next(found)==world_.paths.end()?"*":std::next(found)->id;changed=true;
        }
        label("* controls every train route.",1130,535,13,Muted);
    } else {
        auto &key=document_.sounds[size_t(selected_)];
        label(std::filesystem::path(key.file).filename().string(),1130,342,14,Paper);
        int change=0;
        if (button("Previous sound",{1130,376,137,32})) change=-1;
        if (button("Next sound",{1277,376,139,32})) change=1;
        if (change&&!soundFiles_.empty()) {
            remember();auto found=std::find(soundFiles_.begin(),soundFiles_.end(),key.file);
            int n=found==soundFiles_.end()?0:int(found-soundFiles_.begin());
            key.file=soundFiles_[size_t((n+change+int(soundFiles_.size()))%int(soundFiles_.size()))];changed=true;
        }
        changed|=number("Volume",key.volume,430,.1f,0,1);
        changed|=number("Duration",key.duration,470,.5f,0,600);
        label("0 sec = whole clip; otherwise loop/trim",1130,514,12,Muted);
        if (button("Audition sound",{1130,546,286,32})) {
            player_.pause();audio_.stop();auditionTime_=0;auditioning_=true;
            auto cue=key;cue.time=0;audio_.update(0,true,audioSettings_,{cue},audioDirectory_);
        }
    }
    if (changed) rebuild();
    if (button("Delete selected key",{1130,596,286,30},false,track_!=0||document_.cameras.size()>1)) deleteKey();
}
void CinematicEditor::timeline() {
    panel({0,640,1440,260},Background);
    if (button(player_.playing()?"Pause":"Play",{18,651,95,34},player_.playing())) play();
    if (button("Stop",{122,651,76,34})) seek(0);
    label(decimal(player_.time(),2)+" / "+decimal(document_.duration)+" sec",216,661,18,Paper);
    if (button("Capture shot",{438,651,137,34})) addKey(0);
    if (button("+ Weather",{585,651,124,34})) addKey(1);
    if (button("+ Train cue",{719,651,132,34},false,!world_.paths.empty())) addKey(2);
    if (button("+ Sound",{861,651,116,34})) addKey(3);
    if (button("Length -5",{1034,651,110,34},false,document_.duration>5)) {
        float last=1;for(int t=0;t<4;++t)for(size_t n=0;n<keyCount(t);++n)last=std::max(last,keyTime(t,n));
        if(last<=document_.duration-5) {remember();document_.duration-=5;rebuild();} else status="Move or delete keys beyond the new end first.";
    }
    if (button("Length +5",{1154,651,110,34},false,document_.duration<=595)) {remember();document_.duration+=5;rebuild();}
    if (button("Preview",{1274,651,144,34})) {cleanPreview_=true;if(!player_.playing())play();}
    for(int n=0;n<=10;++n) {
        const float x=155+1230*float(n)/10;
        label(decimal(document_.duration*float(n)/10),x-8,699,12,Muted);
        panel({x,718,1,143},Line);
    }
    const auto p=mouse();
    if(CheckCollisionPointRec(p,{155,694,1230,23})&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        scrubbing_=true;seek(std::clamp((p.x-155)/1230,0.f,1.f)*document_.duration);
    }
    for(int t=0;t<4;++t) {
        const float y=724+float(t)*35;
        label(Tracks[t],18,y+4,14,TrackColors[t]);panel({155,y,1230,27},Panel);
        int nearest=-1;float closest=10;
        for(size_t n=0;n<keyCount(t);++n) {
            const float x=155+keyTime(t,n)/document_.duration*1230;
            const bool selected=t==track_&&int(n)==selected_;
            panel({x-5,y+4,10,19},selected?Paper:TrackColors[t]);
            const float delta=std::abs(p.x-x);
            if(p.y>=y&&p.y<=y+27&&delta<closest) {nearest=int(n);closest=delta;}
        }
        const bool hit=nearest>=0&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        if(hit) {
            track_=t;selected_=nearest;keyDragChanged_=false;draggingKey_=true;seek(keyTime(t,size_t(nearest)));
            if(t==0) {anchorChoice_=-1;for(size_t g=0;g<world_.groups.size();++g)
                if(world_.groups[g].id==document_.cameras[size_t(nearest)].anchor)anchorChoice_=int(g);}
        }
        if(!hit&&CheckCollisionPointRec(p,{155,y,1230,27})&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            scrubbing_=true;seek(std::clamp((p.x-155)/1230,0.f,1.f)*document_.duration);
        }
    }
    panel({155+player_.time()/document_.duration*1230,718,2,143},Gold);
    label("Scrub to preview. Drag keys to retime. Space: play/pause. Home: rewind. F11: clean preview.",18,878,13,Muted);
}
void CinematicEditor::draw() {
    sx_=float(GetScreenWidth())/1440;sy_=float(GetScreenHeight())/900;
    characterModels_.prepare(characters_);animalModels_.prepare(animals_);
    scene_.prepareLighting(view_,[&](Shader shader) {characterModels_.draw(characters_,shader);animalModels_.draw(animals_,shader);});
    scene_.prepareSandstorm(view_,player_.storm(),[&](Vector3 p){return navigation_.height(p);});
    post_.begin({142,174,188,255},distance(view_.position,view_.target));BeginMode3D(view_);
    post_.sandstorm(player_.storm(),player_.time());scene_.draw(view_.target);
    characterModels_.draw(characters_,scene_.actorShader(),scene_.shadowTexture());
    animalModels_.draw(animals_,scene_.actorShader(),scene_.shadowTexture());
    scene_.drawEffects(view_);scene_.draw(view_.target,true);EndMode3D();post_.end();
    if(cleanPreview_&&!closePrompt_) { panel({0,0,1440,48},BLACK);panel({0,852,1440,48},BLACK);return; }
    panel({0,0,1440,88},Background);
    label("DEATHWARD / CINEMATIC EDITOR",18,15,23,Gold);
    label(editCamera_?"FREE CAMERA / Capture shot to keep changes":"TIMELINE CAMERA",18,52,14,editCamera_?Gold:Teal);
    if(button((dirty()?"* ":"")+filenameText_,{462,12,316,31},filenameFocus_))filenameFocus_=true;
    if(button("Save",{790,12,82,31}))save();
    if(button("Reload",{880,12,85,31},false,!dirty()&&std::filesystem::exists(file_))) {
        Cinematic next;if(next.load(file_,status)) {
            try {next.validate(&world_);document_=next;selected_=0;track_=0;rebuild();}
            catch(const std::exception &e) {status=e.what();}
        }
    }
    if(button("Undo",{976,12,72,31},false,!undo_.empty()))undo(false);
    if(button("Redo",{1058,12,72,31},false,!redo_.empty()))undo(true);
    if(button("Close cinematic",{1225,12,192,31}))requestClose();
    label("RMB: look  MMB: orbit  WASD / Q E: fly  Shift: faster  Wheel: lens zoom",462,58,13,Muted);
    label(status.substr(0,130),18,614,13,Paper);
    inspector();timeline();
    if(closePrompt_) {
        panel({0,0,1440,900},{0,0,0,190});panel({405,300,630,240},Panel);
        label("Save cinematic changes?",432,328,27,Paper);
        label("The town scene has not been changed.",432,380,16,Muted);
        auto modal=[&](const char *title,Rectangle r) {
            panel(r,Line);label(title,r.x+16,r.y+13,17,Paper);
            return CheckCollisionPointRec(mouse(),r)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        };
        if(modal("Save & close",{433,443,175,45})&&save()){active=false;quitRequested=closingWindow_;closePrompt_=false;}
        if(modal("Discard",{624,443,170,45})){active=false;quitRequested=closingWindow_;closePrompt_=false;}
        if(modal("Keep editing",{810,443,197,45})){closePrompt_=closingWindow_=false;}
    }
}
} // namespace dw
