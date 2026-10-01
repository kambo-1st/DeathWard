#include "editor/CinematicEditor.hpp"
#include <atomic>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

using namespace dw;
namespace {
void check(bool ok, const char *message) {
    if (!ok) throw std::runtime_error(message);
}
std::string bytes(const std::filesystem::path &path) {
    std::ifstream in(path, std::ios::binary);
    return {std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()};
}
std::atomic<bool> soundReachedMixer{false};
void meter(void *data, unsigned frames) {
    auto *samples = static_cast<float *>(data);
    for (size_t i = 0; i < size_t(frames) * 2; ++i) {
        if (std::abs(samples[i]) > .0001f) soundReachedMixer = true;
        samples[i] = 0; // Verify the real device without playing test sounds aloud.
    }
}
}
int main() {
    const auto directory = std::filesystem::temp_directory_path() /
        ("deathward-cinematic-editor-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    try {
        SetTraceLogLevel(LOG_ERROR);
        SetConfigFlags(FLAG_WINDOW_HIDDEN);
        InitWindow(1440, 900, "Cinematic editor verification");
        SetExitKey(KEY_NULL);
        check(IsWindowReady(), "graphics display required");
        InitAudioDevice();
        check(IsAudioDeviceReady(), "audio device required for the explicit editor/device test");
        AttachAudioMixedProcessor(meter);
        SetMasterVolume(.6f);
        std::filesystem::create_directories(directory);
        const auto source = TownScene::assetDirectory(HubKind::Redstone);
        for (const auto *name : {"town.scene", "town.nav", "town.glb", "town.labels"})
            std::filesystem::copy_file(source / name, directory / name);
        const auto sceneBytes = bytes(directory / "town.scene"), navBytes = bytes(directory / "town.nav");
        TownDocument snapshot;
        std::string error;
        check(snapshot.load(directory / "town.scene", error), error.c_str());
        snapshot.instances.back().transform.m12 += .2f; // Unsaved map-editor change.
        const float unsavedX = snapshot.instances.back().transform.m12;
        Camera3D camera{{20,20,20},{0,0,0},{0,1,0},45,CAMERA_PERSPECTIVE};
        CinematicEditor editor;
        check(editor.previewTrainSpeed()==0,"an unopened cinematic has no train telemetry");
        check(editor.open(directory, camera, &snapshot), editor.status.c_str());
        check(editor.dirty() && editor.document().cameras.size() == 7, "first open creates the train demonstration");
        check(editor.save() && !editor.dirty(), "new sequence saves independently from the town");
        auto event = [](unsigned type, int a, int b = 0) { PlayAutomationEvent({0,type,{a,b,0,0}}); };
        auto frame = [&](Vector2 pixel = Vector2{20,700}, bool left = false) {
            event(7,int(pixel.x),int(pixel.y)); event(left ? 6 : 5,MOUSE_BUTTON_LEFT);
            editor.update(Tick,{});
            BeginDrawing(); editor.draw(); EndDrawing();
        };
        auto click = [&](float x, float y) { frame({x,y}); frame({x,y},true); frame({x,y}); };
        auto undo = [&] {
            event(2,KEY_LEFT_CONTROL);event(2,KEY_Z);frame();
            event(1,KEY_Z);event(1,KEY_LEFT_CONTROL);frame();
        };
        click(155 + 5.f / 20 * 1230,735);
        check(!editor.dirty() && std::abs(editor.preview().time()-5)<.001f,
              "selecting the first of two nearby cut keys picks the nearest key without editing");
        click(155 + 5.1f / 20 * 1230,735);
        check(!editor.dirty() && std::abs(editor.preview().time()-5.1f)<.001f,
              "the second nearby cut key is independently selectable");
        const auto lens = editor.document().cameras[2].fov;
        click(1398,348);
        check(editor.dirty() && editor.document().cameras[2].fov == lens+2, "camera inspector edits the lens");
        undo();
        check(!editor.dirty() && editor.document().cameras[2].fov == lens, "undo restores both lens and saved revision");
        const float keyX = 155 + 5.f / 20 * 1230, destinationX = 155 + 4.5f / 20 * 1230;
        frame({keyX,735});frame({keyX,735},true);frame({destinationX,735},true);frame({destinationX,735});
        check(editor.dirty() && std::abs(editor.document().cameras[1].time-4.5f)<.001f,
              "dragging a key retimes it on the timeline");
        undo();check(!editor.dirty(), "one undo reverses the complete key drag");
        editor.seek(12);
        check(editor.preview().animation().pathSpeed()==0 && editor.preview().storm()>.99f,
              "scrubbing previews the emergency stop and storm together");
        editor.seek(6);editor.play();frame();
        check(editor.audioVoices()==1, "playback from the middle resumes the existing train loop");
        for(int n=0;n<10;++n) {frame();std::this_thread::sleep_for(std::chrono::milliseconds(20));}
        check(soundReachedMixer, "the streamed cinematic soundtrack produces PCM on the shared device");
        editor.seek(6);check(editor.audioVoices()==0, "scrubbing stops audition and playback audio");
        click(1340,160); // Inside carriage preset.
        check(!editor.dirty(), "positioning a shot is temporary until Capture");
        click(500,667);
        check(editor.document().cameras.size()==8 && editor.dirty(), "Capture adds the interior shot at the playhead");
        check(editor.save(), editor.status.c_str());
        editor.requestClose();check(!editor.active, "clean document closes without prompting");
        check(editor.open(directory,camera,&snapshot), editor.status.c_str());
        check(editor.preview().time()==0 && editor.document().cameras.size()==8 && !editor.dirty(),
              "reopening starts at zero and preserves saved shots");
        click(1200,667); // Length +5.
        check(editor.document().duration==25 && editor.dirty(), "sequence length is editable");
        editor.requestClose();check(editor.active, "unsaved sequence asks before closing");
        click(890,464);check(editor.active, "Keep editing cancels closing");
        editor.requestClose();click(700,464);check(!editor.active, "Discard closes without writing changes");
        Cinematic saved;
        check(saved.load(directory/"arrival.cinematic",error) && saved.duration==20, "discard retains the saved sequence");
        check(snapshot.instances.back().transform.m12==unsavedX &&
              bytes(directory/"town.scene")==sceneBytes && bytes(directory/"town.nav")==navBytes,
              "preview, saving and closing preserve the unsaved map snapshot and original scene/navigation files");
        const auto opening=std::filesystem::path(DEATHWARD_ASSET_DIR)/"train_opening";
        std::filesystem::copy_file(opening/"arrival.cinematic",directory/"opening.cinematic");
        check(editor.open(opening,camera,nullptr,directory/"opening.cinematic"),editor.status.c_str());
        click(155,831);check(editor.selectedTrack()==4&&editor.selectedKey()==0,"cast keys are selectable");
        click(155,831);check(editor.selectedKey()==1,"clicking coincident cast keys cycles to the second passenger");
        click(155,831);check(editor.selectedKey()==2,"all three seated passengers remain independently editable");
        click(1395,386);check(editor.dirty(),"actor local position edits are recorded");undo();check(!editor.dirty(),"actor transform undo preserves the saved document");
        click(155,831);
        const auto retimedActor=editor.document().actors[size_t(editor.selectedKey())].actor;
        click(1395,310);
        check(editor.document().actors[size_t(editor.selectedKey())].actor==retimedActor&&
              editor.document().actors[size_t(editor.selectedKey())].time==.25f,
              "actor keys retime independently of other passengers and retain selection after sorting");
        undo();
        click(155+5.f/82*1230,852);check(editor.selectedTrack()==5,"dialogue has its own timeline track");
        const float length=editor.document().dialogue.front().duration;
        click(1395,354);check(editor.document().dialogue.front().duration==length+.5f,"dialogue timing is editable");undo();
        editor.seek(81.9f);editor.playStory(false);
        for(int n=0;n<10;++n)frame();
        check(editor.storyFinished,"story preview reaches its authored ending");
        editor.previewDestination();check(editor.showingDestination(),"editor cuts to the Redstone destination preview");frame();
        event(2,KEY_ESCAPE);frame();event(1,KEY_ESCAPE);frame();
        check(!editor.showingDestination()&&editor.active&&!editor.dirty(),"Escape returns from the destination without altering cinematic edits");
        click(155+5.f/82*1230,852);click(1395,354);
        editor.previewDestination();editor.requestClose(true);frame();
        check(editor.active&&!editor.showingDestination(),"closing a modified destination preview exposes the save prompt");
        click(890,464);check(editor.active&&!editor.quitRequested,"Keep editing cancels quitting from the arrival preview");
        undo();check(!editor.dirty(),"arrival preview preserves existing undo history");
        editor.unload();
        DetachAudioMixedProcessor(meter);CloseAudioDevice();CloseWindow();
        std::filesystem::remove_all(directory);
        std::cout << "PASS separate cinematic editor: input, retiming, lens, undo, save/reload, private preview and device audio\n";
    } catch(const std::exception &e) {
        if(IsAudioDeviceReady()) {DetachAudioMixedProcessor(meter);CloseAudioDevice();}
        if(IsWindowReady()) CloseWindow();
        std::filesystem::remove_all(directory);
        std::cerr << "FAIL " << e.what() << '\n';return 1;
    }
}
