#include "editor/CinematicEditor.hpp"
#include "raymath.h"
#include <cctype>
#include <iomanip>
#include <sstream>

namespace dw {
namespace {
constexpr Color Background{17,23,26,255}, Panel{26,34,36,248}, Line{59,73,73,255},
    Paper{236,226,201,255}, Muted{147,161,153,255}, Gold{224,168,86,255}, Teal{112,204,180,255};
constexpr const char *Tracks[] = {"CAMERA", "SANDSTORM", "TRAIN", "SOUND", "ACTORS", "DIALOGUE"};
constexpr Color TrackColors[] = {{112,204,180,255},{224,168,86,255},{147,170,223,255},{218,142,176,255},{152,186,117,255},{232,203,145,255}};
constexpr Rectangle IntroPause{1070,858,140,34}, IntroSkip{1230,858,190,34};
std::string decimal(float value, int places = 1) {
    std::ostringstream out; out << std::fixed << std::setprecision(places) << value; return out.str();
}
} // namespace
std::filesystem::path CinematicEditor::openingDirectory() {
#ifdef __EMSCRIPTEN__
    return "/persist/train_opening";
#else
    auto source=std::filesystem::path(DEATHWARD_ASSET_DIR)/"train_opening";
    return std::filesystem::exists(source/"town.scene")?source:std::filesystem::path(GetApplicationDirectory())/"assets/train_opening";
#endif
}
void CinematicEditor::playStory(bool rewind) {
    if(rewind)seek(0);
    runtimeIntro_=false;
    screening_=cleanPreview_=true;storyFinished=storyCancelled=false;player_.play();
}
void CinematicEditor::playIntro(bool rewind) {
    playStory(rewind);
    runtimeIntro_=true;
}
void CinematicEditor::previewDestination() {
    if(runtimeIntro_)return; // Runtime arrival belongs to Game, never to an editor preview.
    storyFinished=false;
    if(document_.destination.empty())return;
    const auto hub=document_.destination=="redstone"?HubKind::Redstone:document_.destination=="frontier"?HubKind::Frontier:HubKind::BlackCreek;
    const auto directory=TownScene::assetDirectory(hub);
    if(!endingScene_.load(directory)) {status="Cannot preview the destination map.";return;}
    TownNavigation navigation;navigation.load(directory/"town.nav");
    endingCamera_={add(navigation.spawn,{20,26,20}),navigation.spawn,{0,1,0},45,CAMERA_PERSPECTIVE};
    ending_=true;endingTime_=0;
    audio_.update(0,true,audioSettings_,{{0,"cinematic/storm_wind.wav",.55f,600}},audioDirectory_);
}
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
        openingRequested=storyFinished=storyCancelled=screening_=dialogueFocus_=false;
        active = true;
        player_.reset(world_,document_,[&](Vector3 p) { return navigation_.height(p); });
        actorsTime_=-1;syncActors();
        status = "Cinematic preview only. The town and campaign stay untouched.";
        return true;
    } catch (const std::exception &e) { status = e.what(); active = false; return false; }
}
void CinematicEditor::unload() {
    endingScene_.unload();ending_=false;
    audio_.stop(); castModels_.unload(); scene_.unload(); post_.unload(); characterModels_.unload(); animalModels_.unload();
    active = false;
    runtimeIntro_=screening_=cleanPreview_=false;
    storyFinished=storyCancelled=false;
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
    const auto selectedActor=track_==4&&selected_>=0&&size_t(selected_)<document_.actors.size()
        ?std::optional<ActorKey>(document_.actors[size_t(selected_)]):std::nullopt;
    audio_.stop(); auditioning_=false; document_.sort();
    if(selectedActor) {
        const auto found=std::find_if(document_.actors.begin(),document_.actors.end(),[&](const auto &key){
            return key.actor==selectedActor->actor&&key.time==selectedActor->time;
        });
        selected_=found==document_.actors.end()?-1:int(found-document_.actors.begin());
    }
    try {
        player_.reset(world_,document_,[&](Vector3 p) { return navigation_.height(p); });
        player_.seek(time); actorsTime_ = -1; syncActors();
    } catch (const std::exception &e) {
        status=std::string("Change rejected: ")+e.what();
        if(!undo_.empty()) {
            document_=undo_.back().first;revision_=undo_.back().second;undo_.pop_back();selected_=-1;
            player_.reset(world_,document_,[&](Vector3 p){return navigation_.height(p);});player_.seek(time);actorsTime_=-1;syncActors();
        }
    }
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
    ending_=false;endingScene_.unload();screening_=cleanPreview_=false;
    if (dirty()) closePrompt_ = true;
    else { active = false; quitRequested = closingWindow_; }
}
size_t CinematicEditor::keyCount(int track) const {
    switch (track) { case 0:return document_.cameras.size(); case 1:return document_.weather.size();
                    case 2:return document_.trains.size(); case 3:return document_.sounds.size(); case 4:return document_.actors.size(); default:return document_.dialogue.size(); }
}
float CinematicEditor::keyTime(int track, size_t n) const {
    switch (track) { case 0:return document_.cameras[n].time; case 1:return document_.weather[n].time;
                    case 2:return document_.trains[n].time; case 3:return document_.sounds[n].time; case 4:return document_.actors[n].time; default:return document_.dialogue[n].time; }
}
void CinematicEditor::setKeyTime(int track, size_t n, float time) {
    switch (track) { case 0:document_.cameras[n].time=time;break; case 1:document_.weather[n].time=time;break;
                    case 2:document_.trains[n].time=time;break; case 3:document_.sounds[n].time=time;break; case 4:document_.actors[n].time=time;break; default:document_.dialogue[n].time=time;break; }
}
void CinematicEditor::changeTime(float time) {
    if (selected_ < 0 || size_t(selected_) >= keyCount(track_)) return;
    float low = 0, high = document_.duration;
    if(track_==5)high-=document_.dialogue[size_t(selected_)].duration;
    if(track_==4) {
        const auto &selected=document_.actors[size_t(selected_)];
        for(size_t i=0;i<document_.actors.size();++i) {
            const auto &key=document_.actors[i];
            if(i==size_t(selected_)||key.actor!=selected.actor)continue;
            if(key.time<selected.time)low=std::max(low,key.time+.05f);
            else high=std::min(high,key.time-.05f);
        }
    } else {
        if (selected_ > 0) low = keyTime(track_,size_t(selected_-1)) + (track_ < 2 ? .05f : 0);
        if (size_t(selected_+1) < keyCount(track_)) high = std::min(high,keyTime(track_,size_t(selected_+1)) - (track_ < 2 ? .05f : 0));
    }
    setKeyTime(track_,size_t(selected_),std::clamp(time,low,high));
}
void CinematicEditor::addKey(int track) {
    const float time = player_.time();
    if(track==5&&time>=document_.duration)return;
    const std::string selectedActor=track_==4&&selected_>=0&&size_t(selected_)<document_.actors.size()
        ?document_.actors[size_t(selected_)].actor:std::string{};
    std::string capturedActor;
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
    else if(track==3) document_.sounds.push_back({time,"cinematic/train_brake.wav",.8f});
    else if(track==4) {
        if(document_.cast.empty()) document_.cast.push_back({"hero","YOU","bandit",1});
        std::string actor=document_.cast.front().id;
        if(!selectedActor.empty())actor=selectedActor;
        capturedActor=actor;
        auto states=player_.actors();
        ActorKey key{time,actor,view_.target,0,ActorPose::Standing,{}};
        for(const auto &state:states)if(state.member.id==actor) {
            key.position=state.position;key.yaw=std::atan2(state.facing.x,state.facing.z)*RAD2DEG;key.pose=state.pose;
        }
        if(anchorChoice_>=0) {
            key.anchor=world_.groups[size_t(anchorChoice_)].id;
            auto frame=*player_.anchor(key.anchor);key.position=Vector3Transform(key.position,MatrixInvert(frame));
            key.yaw-=std::atan2(frame.m8,frame.m10)*RAD2DEG;
        }
        auto found=std::find_if(document_.actors.begin(),document_.actors.end(),[&](const auto &k){return k.actor==actor&&std::abs(k.time-time)<.05f;});
        if(found==document_.actors.end())document_.actors.push_back(key);else {*found=key;}
    } else if(time<document_.duration)document_.dialogue.push_back({time,std::min(4.f,document_.duration-time),document_.cast.empty()?"Narrator":document_.cast.front().id,"Enter dialogue here."});
    document_.sort();
    selected_ = 0;
    for (size_t n = 0; n < keyCount(track); ++n)
        if (std::abs(keyTime(track,n)-time)<.05f&&(track!=4||document_.actors[n].actor==capturedActor)) selected_=int(n);
    editCamera_ = false; rebuild();
}
void CinematicEditor::deleteKey() {
    if (selected_ < 0 || size_t(selected_) >= keyCount(track_) || (track_ == 0 && keyCount(0) == 1)) return;
    remember();
    switch (track_) { case 0:document_.cameras.erase(document_.cameras.begin()+selected_);break;
        case 1:document_.weather.erase(document_.weather.begin()+selected_);break;
        case 2:document_.trains.erase(document_.trains.begin()+selected_);break;
        case 3:document_.sounds.erase(document_.sounds.begin()+selected_);break;
        case 4:document_.actors.erase(document_.actors.begin()+selected_);break;
        default:document_.dialogue.erase(document_.dialogue.begin()+selected_);break; }
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
    if(track_==4&&selected_>=0&&size_t(selected_)<document_.actors.size()) {
        remember();auto &key=document_.actors[size_t(selected_)];
        if(auto frame=player_.anchor(key.anchor)) {
            key.position=Vector3Transform(key.position,*frame);key.yaw+=std::atan2(frame->m8,frame->m10)*RAD2DEG;
        }
        key.anchor=anchorChoice_<0?"":world_.groups[size_t(anchorChoice_)].id;
        if(auto frame=player_.anchor(key.anchor)) {
            key.position=Vector3Transform(key.position,MatrixInvert(*frame));key.yaw-=std::atan2(frame->m8,frame->m10)*RAD2DEG;
        }
        rebuild();return;
    }
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
    const bool hover=CheckCollisionPointRec(mouse(),r)&&!closePrompt_&&!dialogueFocus_;
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
    if(runtimeIntro_) {
        // Hold the cinematic image until main completes the gameplay handoff.
        // Editor hotkeys and timeline input must never run in the game opening.
        if(storyFinished||storyCancelled)return;
        const bool click=IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        if(IsKeyPressed(KEY_ESCAPE)||(click&&CheckCollisionPointRec(mouse(),IntroSkip))) {
            player_.pause();audio_.stop();storyCancelled=true;return;
        }
        if(IsKeyPressed(KEY_SPACE)||(click&&CheckCollisionPointRec(mouse(),IntroPause)))play();
        advancePlayback(dt,audio);
        return;
    }
    if(ending_) {
        if(IsKeyPressed(KEY_ESCAPE)) {ending_=false;endingScene_.unload();audio_.stop();rebuild();return;}
        endingTime_+=dt;audio_.update(endingTime_,true,audio,{},audioDirectory_);return;
    }
    const bool ctrl=IsKeyDown(KEY_LEFT_CONTROL)||IsKeyDown(KEY_RIGHT_CONTROL);
    if(dialogueFocus_) {
        if(ctrl&&IsKeyPressed(KEY_A))dialogueText_.clear();
        for(int c=GetCharPressed();c;c=GetCharPressed())if(c>=32&&c<127&&dialogueText_.size()<480)dialogueText_+=char(c);
        if(IsKeyPressed(KEY_BACKSPACE)&&!dialogueText_.empty())dialogueText_.pop_back();
        if(IsKeyPressed(KEY_ENTER)&&!dialogueText_.empty()) {
            remember();document_.dialogue[size_t(selected_)].text=dialogueText_;dialogueFocus_=false;rebuild();
        }
        if(IsKeyPressed(KEY_ESCAPE))dialogueFocus_=false;
        return;
    }
    if(screening_) {
        if(IsKeyPressed(KEY_ESCAPE)) {screening_=cleanPreview_=false;player_.pause();audio_.stop();storyCancelled=true;return;}
    }
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
    if (!screening_&&IsKeyPressed(KEY_ESCAPE)) {
        if (cleanPreview_) cleanPreview_=false; else requestClose();
        return;
    }
    if (ctrl&&IsKeyPressed(KEY_S)) save();
    if (ctrl&&IsKeyPressed(KEY_Z)) undo(IsKeyDown(KEY_LEFT_SHIFT)||IsKeyDown(KEY_RIGHT_SHIFT));
    if (ctrl&&IsKeyPressed(KEY_Y)) undo(true);
    if (IsKeyPressed(KEY_SPACE)) play();
    if (IsKeyPressed(KEY_HOME)) seek(0);
    if (IsKeyPressed(KEY_F11)) cleanPreview_=!cleanPreview_;
    if (!screening_&&IsKeyPressed(KEY_DELETE)) deleteKey();
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
    advancePlayback(dt,audio);
}
void CinematicEditor::advancePlayback(float dt,const AudioSettings &audio) {
    const bool wasPlaying=player_.playing();
    player_.advance(std::min(dt,.1f));syncActors();
    if(wasPlaying&&!player_.playing()) {
        audio_.stop();
        if(screening_) {
            storyFinished=true;screening_=false;
            // main unloads the runtime intro after this frame has been presented.
            // Clearing cleanPreview here exposed the editor during the hub load.
            cleanPreview_=runtimeIntro_;
        }
    }
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
    } else if(track_==3) {
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
    if(track_==4) {
        auto &key=document_.actors[size_t(selected_)];
        if(button("Actor: "+document_.speakerName(key.actor),{1130,336,286,30})) {
            auto c=std::find_if(document_.cast.begin(),document_.cast.end(),[&](const auto &v){return v.id==key.actor;});
            if(!document_.cast.empty()) {remember();key.actor=(c==document_.cast.end()||std::next(c)==document_.cast.end()?document_.cast.front():*std::next(c)).id;changed=true;}
        }
        changed|=number("Position X",key.position.x,373,.1f,-10000,10000);
        changed|=number("Position Y",key.position.y,408,.1f,-10000,10000);
        changed|=number("Position Z",key.position.z,443,.1f,-10000,10000);
        changed|=number("Facing",key.yaw,478,5,-360,360);
        const char *pose=key.pose==ActorPose::Seated?"Seated":key.pose==ActorPose::Walking?"Walking":"Standing";
        if(button(std::string("Pose: ")+pose,{1130,517,286,30})) {remember();key.pose=ActorPose((int(key.pose)+1)%3);changed=true;}
        label(key.anchor.empty()?"World coordinates":"Attached to "+key.anchor,1130,566,12,Muted);
    } else if(track_==5) {
        auto &line=document_.dialogue[size_t(selected_)];
        changed|=number("Duration",line.duration,340,.5f,.1f,document_.duration-line.time);
        if(button("Speaker: "+document_.speakerName(line.speaker),{1130,380,286,32},false,!document_.cast.empty())) {
            auto c=std::find_if(document_.cast.begin(),document_.cast.end(),[&](const auto &v){return v.id==line.speaker;});
            remember();line.speaker=(c==document_.cast.end()||std::next(c)==document_.cast.end()?document_.cast.front():*std::next(c)).id;changed=true;
        }
        if(button("Edit dialogue text",{1130,423,286,32})) {player_.pause();audio_.stop();dialogueText_=line.text;dialogueFocus_=true;}
        wrapped(line.text,1130,473,280,14,Paper);
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
        float last=1;for(int t=0;t<6;++t)for(size_t n=0;n<keyCount(t);++n)last=std::max(last,keyTime(t,n));
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
    const bool expanded=!document_.actors.empty()||!document_.dialogue.empty();
    const float row=expanded?24.f:35.f,height=expanded?22.f:27.f;
    for(int t=0;t<(expanded?6:4);++t) {
        const float y=724+float(t)*row;
        label(Tracks[t],18,y+4,14,TrackColors[t]);panel({155,y,1230,height},Panel);
        int nearest=-1;float closest=10;
        for(size_t n=0;n<keyCount(t);++n) {
            const float x=155+keyTime(t,n)/document_.duration*1230;
            const bool selected=t==track_&&int(n)==selected_;
            panel({x-5,y+3,10,height-6},selected?Paper:TrackColors[t]);
            const float delta=std::abs(p.x-x);
            if(p.y>=y&&p.y<=y+height&&delta<closest) {nearest=int(n);closest=delta;}
        }
        const bool hit=nearest>=0&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        if(hit&&t==4&&track_==4&&selected_>=0&&std::abs(keyTime(t,size_t(selected_))-keyTime(t,size_t(nearest)))<.01f) {
            for(size_t n=size_t(selected_+1);n<keyCount(t);++n)
                if(std::abs(keyTime(t,n)-keyTime(t,size_t(nearest)))<.01f) {nearest=int(n);break;}
        }
        if(hit) {
            track_=t;selected_=nearest;keyDragChanged_=false;draggingKey_=true;seek(keyTime(t,size_t(nearest)));
            if(t==0||t==4) {anchorChoice_=-1;for(size_t g=0;g<world_.groups.size();++g)
                if(world_.groups[g].id==(t==0?document_.cameras[size_t(nearest)].anchor:document_.actors[size_t(nearest)].anchor))anchorChoice_=int(g);}
        }
        if(!hit&&CheckCollisionPointRec(p,{155,y,1230,height})&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            scrubbing_=true;seek(std::clamp((p.x-155)/1230,0.f,1.f)*document_.duration);
        }
    }
    panel({155+player_.time()/document_.duration*1230,718,2,143},Gold);
    label("Scrub to preview. Drag keys to retime. Space: play/pause. Home: rewind. F11: clean preview.",18,878,13,Muted);
}
void CinematicEditor::wrapped(const std::string &text,float x,float y,float width,int size,Color color) const {
    std::istringstream words(text);std::string word,line;
    while(words>>word) {
        auto next=line.empty()?word:line+" "+word;
        if(!line.empty()&&MeasureText(next.c_str(),int(size*sy_))>width*sx_) {label(line,x,y,size,color);y+=size+5;line=word;}
        else line=next;
    }
    if(!line.empty())label(line,x,y,size,color);
}
void CinematicEditor::subtitles() {
    const auto *line=document_.line(player_.time());if(!line)return;
    const float y=cleanPreview_?722.f:462.f;
    panel({180,y,860,109},{12,18,22,225});
    label(document_.speakerName(line->speaker),202,y+13,16,Gold);
    wrapped(line->text,202,y+39,816,21,Paper);
}
void CinematicEditor::draw() {
    sx_=float(GetScreenWidth())/1440;sy_=float(GetScreenHeight())/900;
    if(ending_) {
        endingScene_.prepareLighting(endingCamera_);
        endingScene_.prepareSandstorm(endingCamera_,document_.destinationStorm,[](Vector3){return 0.f;});
        post_.begin({142,174,188,255},distance(endingCamera_.position,endingCamera_.target));BeginMode3D(endingCamera_);
        post_.sandstorm(document_.destinationStorm,endingTime_);endingScene_.draw(endingCamera_.target);
        endingScene_.drawEffects(endingCamera_);endingScene_.draw(endingCamera_.target,true);EndMode3D();post_.end();
        panel({0,0,1440,48},BLACK);panel({0,852,1440,48},BLACK);
        label(document_.destination=="redstone"?"REDSTONE CANYON":"ARRIVAL",50,765,32,Paper);
        label("Escape: return to the cinematic editor",50,817,16,Paper);return;
    }
    characterModels_.prepare(characters_);animalModels_.prepare(animals_);
    scene_.prepareLighting(view_,[&](Shader shader) {characterModels_.draw(characters_,shader);animalModels_.draw(animals_,shader);castModels_.draw(player_,shader);});
    scene_.prepareSandstorm(view_,player_.storm(),[&](Vector3 p){return navigation_.height(p);});
    post_.begin({142,174,188,255},distance(view_.position,view_.target));BeginMode3D(view_);
    post_.sandstorm(player_.storm(),player_.time());scene_.draw(view_.target);
    characterModels_.draw(characters_,scene_.actorShader(),scene_.shadowTexture());
    animalModels_.draw(animals_,scene_.actorShader(),scene_.shadowTexture());
    castModels_.draw(player_,scene_.actorShader(),scene_.shadowTexture());
    scene_.drawEffects(view_);scene_.draw(view_.target,true);EndMode3D();post_.end();
    if((cleanPreview_||runtimeIntro_)&&!closePrompt_) {
        panel({0,0,1440,48},BLACK);panel({0,852,1440,48},BLACK);subtitles();
        if(runtimeIntro_&&(storyFinished||storyCancelled)) {
            label("Arriving...",24,868,15,Paper);
        } else if(runtimeIntro_) {
            label(player_.playing()?"Space: pause":"Paused / Space: resume",24,868,15,Muted);
            // Hit testing runs in update, so a skip cannot also activate a game HUD button.
            button(player_.playing()?"Pause":"Resume",IntroPause);
            button("Skip intro",IntroSkip);
        }
        return;
    }
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
    if(button("Train opening",{1215,50,200,28})) {
        if(dirty()&&!undo_.empty())status="Save this sequence before opening the train scene.";
        else openingRequested=true;
    }
    if(button("Play story",{1060,50,145,28},false,!document_.destination.empty()))playStory();
    if(button("+ Actor",{18,580,95,28}))addKey(4);
    if(button("+ Dialogue",{123,580,117,28}))addKey(5);
    label(status.substr(0,130),18,614,13,Paper);
    inspector();timeline();
    subtitles();
    if(dialogueFocus_) {
        panel({0,0,1440,900},{0,0,0,200});panel({340,250,760,340},Panel);
        label("EDIT DIALOGUE",365,273,23,Gold);
        wrapped(dialogueText_+"|",365,328,710,21,Paper);
        label("Enter: keep text   Escape: cancel   Ctrl+A: replace all",365,544,16,Muted);
    }
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
