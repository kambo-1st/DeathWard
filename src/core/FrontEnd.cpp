#include "core/FrontEnd.hpp"
#include <cmath>

namespace dw {
namespace {
constexpr Color Ink{18, 24, 27, 255}, Paper{236, 225, 199, 255}, Gold{205, 158, 93, 255},
    Muted{161, 164, 153, 255}, Border{70, 77, 73, 255};
constexpr Rectangle Start{440, 610, 400, 58}, Settings{452, 698, 176, 44}, Exit{652, 698, 176, 44},
    Apply{662, 675, 294, 52}, Cancel{324, 675, 294, 52};
Rectangle card(int i) { return {140.f + i * 340.f, 333, 320, 230}; }
Rectangle settingRow(int i) { return {324, 242.f + i * 48, 632, 42}; }
float scale() { return std::min(GetScreenWidth() / 1280.f, GetScreenHeight() / 800.f); }
Vector2 offset() { const auto s = scale(); return {(GetScreenWidth()-1280*s)/2, (GetScreenHeight()-800*s)/2}; }
Vector2 mouse() { const auto o=offset(); const auto s=scale(); return {(GetMouseX()-o.x)/s,(GetMouseY()-o.y)/s}; }
bool hit(Rectangle r) { return CheckCollisionPointRec(mouse(),r); }
float fade(float time, float duration) { return std::min(std::clamp(time/.55f,0.f,1.f),std::clamp((duration-time)/.55f,0.f,1.f)); }
Font loadFont(const char *name, int size) {
#ifdef __EMSCRIPTEN__
    const auto path=std::filesystem::path("/assets/ui")/name;
#else
    auto path=std::filesystem::path(GetApplicationDirectory())/"assets/ui"/name;
    if(!std::filesystem::exists(path))path=std::filesystem::path(DEATHWARD_ASSET_DIR)/"ui"/name;
#endif
    auto font=LoadFontEx(path.string().c_str(),size,nullptr,0);
    if(!font.texture.id)font=GetFontDefault();
    SetTextureFilter(font.texture,TEXTURE_FILTER_BILINEAR);
    return font;
}
}
FrontEnd::FrontEnd(std::filesystem::path slots,std::filesystem::path audioFile,
                   std::filesystem::path visualFile,AudioSettings audio,VisualSettings visual,AudioStatus status)
    : audioSettings(audio),visualSettings(visual),store_(std::move(slots)),audioFile_(std::move(audioFile)),
      visualFile_(std::move(visualFile)),audioStatus_(status) {
    titleFont_=loadFont("title.ttf",110);bodyFont_=loadFont("body.ttf",32);
    refresh();
}
FrontEnd::~FrontEnd() {
    if(titleFont_.texture.id!=GetFontDefault().texture.id)UnloadFont(titleFont_);
    if(bodyFont_.texture.id!=GetFontDefault().texture.id)UnloadFont(bodyFont_);
}
void FrontEnd::refresh() { for(size_t i=0;i<slots_.size();++i)slots_[i]=store_.inspect(i); }
void FrontEnd::openSettings() {
    beforeAudio_=audioSettings;beforeVisual_=visualSettings;
    page=FrontPage::Settings;focus_=0;dragging_=-1;error_.clear();
}
void FrontEnd::activate(int control) {
    if(page==FrontPage::Slots) {
        if(control<3) {selected_=control;focus_=3;error_.clear();}
        else if(control==3) {
            try {
                if(slots_[size_t(selected_)].state==SlotState::Unavailable)return;
                launch=store_.start(size_t(selected_));
                if(launch->state==SlotState::Unavailable)throw std::runtime_error(launch->error);
                page=FrontPage::Loading;
            } catch(const std::exception &e) {launch.reset();error_="Could not open this journey. Your save has been kept.";TraceLog(LOG_WARNING,"SAVE SLOT: %s",e.what());refresh();}
        } else if(control==4)openSettings();
        else if(control==5)quit=true;
    } else if(page==FrontPage::Settings) {
        if(control==8) {
            const bool audioSaved=saveAudioSettings(audioFile_,audioSettings);
            const bool visualSaved=saveVisualSettings(visualFile_,visualSettings);
            if(!audioSaved||!visualSaved) {error_="Could not save settings. Check that the save folder is writable.";return;}
            page=FrontPage::Slots;focus_=4;error_.clear();
        } else if(control==9) {
            audioSettings=beforeAudio_;visualSettings=beforeVisual_;page=FrontPage::Slots;focus_=4;error_.clear();
        } else if(control==4||control==6||control==7)adjust(control,1);
    }
}
void FrontEnd::adjust(int control,float amount) {
    if(control<4) {
        float *volume[]={&audioSettings.master,&audioSettings.music,&audioSettings.effects,&audioSettings.ambience};
        *volume[control]=std::clamp(*volume[control]+amount*.05f,0.f,1.f);
    } else if(control==4)audioSettings.muted=!audioSettings.muted;
    else if(control==5)visualSettings.vegetation=std::clamp(visualSettings.vegetation+int(amount)*10,0,VisualSettings::MaxVegetation);
    else if(control==6)visualSettings.groundDetail=!visualSettings.groundDetail;
    else if(control==7)visualSettings.canyonRiver=!visualSettings.canyonRiver;
}
void FrontEnd::update(float dt) {
    dt=std::clamp(dt,0.f,.1f);elapsed_+=dt;time_+=dt;
    if(page==FrontPage::Studio||page==FrontPage::Title) {
        const auto duration=page==FrontPage::Studio?2.8f:3.2f;
        if(elapsed_>=duration||IsKeyPressed(KEY_ENTER)||IsKeyPressed(KEY_SPACE)||IsKeyPressed(KEY_ESCAPE)||IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            page=page==FrontPage::Studio?FrontPage::Title:FrontPage::Slots;elapsed_=0;
        }
        return;
    }
    if(page==FrontPage::Loading)return;
    const int count=page==FrontPage::Settings?10:6;
    if(IsKeyPressed(KEY_TAB))focus_=(focus_+(IsKeyDown(KEY_LEFT_SHIFT)||IsKeyDown(KEY_RIGHT_SHIFT)?count-1:1))%count;
    if(IsKeyPressed(KEY_DOWN))focus_=(focus_+1)%count;
    if(IsKeyPressed(KEY_UP))focus_=(focus_+count-1)%count;
    if(IsKeyPressed(KEY_ESCAPE)) {if(page==FrontPage::Settings)activate(9);else focus_=5;return;}
    const int direction=int(IsKeyPressed(KEY_RIGHT))-int(IsKeyPressed(KEY_LEFT));
    if(direction) {
        if(page==FrontPage::Settings&&focus_<8)adjust(focus_,float(direction));
        else if(page==FrontPage::Slots&&focus_<3) {selected_=focus_=(focus_+direction+3)%3;error_.clear();}
    }
    if(IsKeyPressed(KEY_ENTER)||IsKeyPressed(KEY_SPACE)) {activate(focus_);return;}
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if(page==FrontPage::Slots) {
            for(int i=0;i<3;++i)if(hit(card(i))) {selected_=focus_=i;error_.clear();return;}
            if(hit(Start)){focus_=3;activate(3);}
            else if(hit(Settings)){focus_=4;activate(4);}
            else if(hit(Exit)){focus_=5;activate(5);}
        } else {
            for(int i=0;i<8;++i)if(hit(settingRow(i))) {
                focus_=i;
                if((i<4||i==5)&&mouse().x>=694&&mouse().x<=906)dragging_=i;
                else if(i<4||i==5)adjust(i,mouse().x<694?-1.f:1.f);
                else activate(i);
            }
            if(hit(Apply))activate(8);
            else if(hit(Cancel))activate(9);
        }
    }
    if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT))dragging_=-1;
    if(page==FrontPage::Settings&&dragging_>=0) {
        const auto fraction=std::clamp((mouse().x-702)/196.f,0.f,1.f);
        if(dragging_==5)visualSettings.vegetation=int(std::round(fraction*20))*10;
        else {
            float *volume[]={&audioSettings.master,&audioSettings.music,&audioSettings.effects,&audioSettings.ambience};
            *volume[dragging_]=std::round(fraction*100)/100;
        }
    }
}
void FrontEnd::text(const std::string &label,float x,float y,float size,Color color,bool center,bool display) const {
    const auto font=display?titleFont_:bodyFont_;
    if(center)x-=MeasureTextEx(font,label.c_str(),size,1).x/2;
    DrawTextEx(font,label.c_str(),{x,y},size,1,color);
}
void FrontEnd::title(float y,float size,float opacity) const {
    text("DEATHWARD",640,y+3,size,Fade(Ink,opacity),true,true);
    text("DEATHWARD",640,y,size,Fade(Paper,opacity),true,true);
    DrawLineEx({490,y+size+20},{600,y+size+20},1,Fade(Gold,opacity));
    DrawPoly({640,y+size+20},4,5,0,Fade(Gold,opacity));
    DrawLineEx({680,y+size+20},{790,y+size+20},1,Fade(Gold,opacity));
}
void FrontEnd::background() const {
    DrawRectangleGradientV(0,0,1280,800,{27,37,44,255},{119,86,65,255});
    DrawCircleGradient(960,252,165,{203,144,90,35},{203,144,90,0});
    DrawCircle(960,252,46,{172,125,82,255});
    constexpr std::array<Vector2,10> far{{{0,350},{100,310},{160,315},{210,255},{320,258},{380,350},{570,376},{800,365},{1060,317},{1280,346}}};
    constexpr std::array<Vector2,9> near{{{0,415},{150,449},{270,407},{420,460},{680,440},{865,390},{975,394},{1100,440},{1280,420}}};
    auto ridge=[](const auto &points,Color color) {
        for(size_t i=1;i<points.size();++i) {
            auto p=points[i-1],q=points[i];
            DrawTriangle(p,{p.x,800},{q.x,800},color);DrawTriangle(p,{q.x,800},q,color);
        }
    };
    ridge(far,{69,62,57,255});ridge(near,{35,39,38,255});
    // Rails vanish into the same horizon; uneven sleepers and drifting grit
    // suggest the journey without loading a second 3D map behind the menu.
    for(int i=1;i<=15;++i) {
        const float t=i/15.f,t2=t*t,y=425+400*t2,x=790+380*t2,w=8+115*t2;
        DrawLineEx({x-w,y},{x+w,y+8*t2},1+5*t2,{51,49,43,255});
    }
    DrawLineEx({784,425},{1060,820},2,{83,78,63,255});
    DrawLineEx({796,425},{1290,820},2,{83,78,63,255});
    for(int i=0;i<40;++i) {
        const auto x=std::fmod(i*91.7f+time_*(8+i%5),1320.f)-20;
        const auto y=280+std::fmod(i*39.3f,430.f)+std::sin(time_*.3f+i)*4;
        DrawLineEx({x,y},{x+3+i%4,y-1},1,{202,174,130,25});
    }
    DrawRectangleGradientV(0,580,1280,220,{18,24,27,0},Ink);
}
void FrontEnd::button(Rectangle rect,const char *label,bool focused,bool enabled) const {
    const bool active=enabled&&(focused||hit(rect));
    DrawRectangleRec(rect,active?Color{58,58,47,245}:Color{22,29,31,245});
    DrawRectangleLinesEx(rect,active?2:1,active?Gold:Border);
    text(label,rect.x+rect.width/2,rect.y+(rect.height-21)/2,21,enabled?(active?Paper:Muted):Border,true);
}
void FrontEnd::draw() const {
    ClearBackground(Ink);
    const auto o=offset();BeginMode2D({o,{0,0},0,scale()});
    if(page==FrontPage::Studio) {
        const auto color=Fade(Paper,fade(elapsed_,2.8f));
        // A small ghost stamp, drawn as vectors so it scales on desktop and web.
        DrawCircleV({640,299},51,color);DrawRectangleRec({589,299,102,73},color);
        for(int i=0;i<3;++i)DrawTriangle({589.f+i*34,372},{606.f+i*34,392},{623.f+i*34,372},color);
        DrawEllipse(621,306,7,12,Ink);DrawEllipse(659,306,7,12,Ink);
        text("BUBAK",640,429,48,color,true,true);
        text("G A M E S",640,488,18,Fade(Gold,fade(elapsed_,2.8f)),true);
    } else {
        background();
        if(page==FrontPage::Title) {
            title(317,94,fade(elapsed_,3.2f));
            text("THE CONSEQUENCES REMAIN",640,468,16,Fade(Gold,fade(elapsed_,3.2f)),true);
        } else if(page==FrontPage::Slots||page==FrontPage::Loading) {
            text("B U B A K   G A M E S",640,63,15,Gold,true);
            title(107,86);
            text("CHOOSE YOUR JOURNEY",640,278,18,Paper,true);
            for(int i=0;i<3;++i) {
                const auto &slot=slots_[size_t(i)];const auto r=card(i);
                const bool selected=selected_==i;
                DrawRectangleRec(r,selected?Color{36,43,42,245}:Color{20,28,31,235});
                DrawRectangleLinesEx(r,selected?2:1,selected?Gold:focus_==i||hit(r)?Muted:Border);
                text("0"+std::to_string(i+1),r.x+22,r.y+18,34,selected?Gold:Muted,false,true);
                text(slot.state==SlotState::Empty?"EMPTY SLOT":slot.state==SlotState::Ready?"SAVED JOURNEY":"UNAVAILABLE",r.x+84,r.y+31,13,Muted);
                DrawLineEx({r.x+22,r.y+75},{r.x+298,r.y+75},1,Border);
                text(slot.chapter,r.x+22,r.y+100,21,Paper,false,true);
                text(slot.detail,r.x+22,r.y+139,13,Muted);
                const auto note=slot.state==SlotState::Empty?"The west is waiting.":slot.state==SlotState::Unavailable?"This slot cannot be overwritten.":std::to_string(slot.expeditions)+" expeditions recorded";
                text(note,r.x+22,r.y+193,13,selected?Gold:Muted);
                if(selected)DrawPoly({r.x+291,r.y+36},4,5,0,Gold);
            }
            const auto &slot=slots_[size_t(selected_)];
            text(error_.empty()?(slot.state==SlotState::Unavailable?"This save could not be read. Choose another slot.":"Progress is saved at story and expedition checkpoints."):error_,640,579,14,error_.empty()?Muted:Gold,true);
            button(Start,page==FrontPage::Loading?"LOADING YOUR JOURNEY...":slot.state==SlotState::Empty?"BEGIN JOURNEY":"CONTINUE JOURNEY",focus_==3,slot.state!=SlotState::Unavailable);
            button(Settings,"SETTINGS",focus_==4);button(Exit,"EXIT",focus_==5);
        } else if(page==FrontPage::Settings) {
            DrawRectangleRec({292,70,696,683},{20,28,31,247});
            DrawRectangleLinesEx({292,70,696,683},1,Border);
            text("Settings",640,101,42,Paper,true,true);
            text("Tune the frontier to your liking.",640,164,16,Muted,true);
            if(audioStatus_!=AudioStatus::Ready)text(audioStatus_==AudioStatus::Disabled?"Audio disabled for this launch":"Audio device unavailable",640,208,14,Gold,true);
            const char *labels[]={"Master volume","Music","Effects","Ambience","Mute sound","Vegetation","Ground detail","Canyon rivers"};
            const float values[]={audioSettings.master,audioSettings.music,audioSettings.effects,audioSettings.ambience,0,visualSettings.vegetation/200.f};
            for(int i=0;i<8;++i) {
                const auto r=settingRow(i);
                if(focus_==i||hit(r)) {DrawRectangleRec(r,{38,45,44,255});DrawRectangleLinesEx(r,1,Border);}
                text(labels[i],r.x+12,r.y+10,18,Paper);
                if(i<4||i==5) {
                    text(std::to_string(int(std::round(values[i]*(i==5?200:100))))+"%",628,r.y+11,16,Gold,true);
                    text("-",674,r.y+8,21,Muted,true);text("+",926,r.y+8,21,Muted,true);
                    DrawRectangleRec({702,r.y+20,196,3},Border);DrawRectangleRec({702,r.y+20,196*values[i],3},Gold);
                    DrawCircleV({702+196*values[i],r.y+21},5,Paper);
                } else {
                    const bool on=i==4?audioSettings.muted:i==6?visualSettings.groundDetail:visualSettings.canyonRiver;
                    text(on?"ON":"OFF",802,r.y+10,18,on?Gold:Muted,true);
                }
            }
            text(error_.empty()?"Changes are previewed. Apply to keep them.":error_,640,644,14,error_.empty()?Muted:Gold,true);
            button(Apply,"APPLY & BACK",focus_==8);button(Cancel,"CANCEL",focus_==9);
        }
    }
    if(page==FrontPage::Studio||page==FrontPage::Title)text("Click or press Enter to continue",640,747,14,Muted,true);
    else if(page!=FrontPage::Loading)text("Mouse to select   /   Tab to navigate   /   Enter to confirm",640,770,12,Muted,true);
    EndMode2D();
}
void FrontEnd::publish() const {
#ifdef __EMSCRIPTEN__
    EM_ASM({if(Module.verify)Module.frontend=({active:!$0&&!$1,page:$2,selected:$3,focus:$4,master:$5,music:$6,vegetation:$7,groundDetail:!!$8,river:!!$9,error:UTF8ToString($10)});},
        launch.has_value(),quit,int(page),selected_,focus_,audioSettings.master,audioSettings.music,
        visualSettings.vegetation,visualSettings.groundDetail,visualSettings.canyonRiver,error_.c_str());
    for(size_t i=0;i<slots_.size();++i) {
        const auto &slot=slots_[i];
        EM_ASM({if(Module.frontend){if(!Module.frontend.slots)Module.frontend.slots=[];Module.frontend.slots[$0]=({state:$1,chapter:UTF8ToString($2),opening:!!$3});}},
            int(i),int(slot.state),slot.chapter.c_str(),slot.opening);
    }
#endif
}
}
