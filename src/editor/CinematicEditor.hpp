#pragma once
#include "cinematic/CinematicAudio.hpp"
#include "cinematic/CinematicCast.hpp"
#include "render/AnimalModels.hpp"
#include "render/PostProcess.hpp"
#include "render/TownActorModels.hpp"
#include "render/TownScene.hpp"
#include "world/TownNavigation.hpp"
#include <deque>

namespace dw {
// A separate document/editor, sharing only rendering assets with the town editor.
class CinematicEditor {
  public:
    bool active = false, quitRequested = false;
    std::string status;
    bool open(const std::filesystem::path &directory, Camera3D view,
              const TownDocument *snapshot = nullptr, const std::filesystem::path &file = {});
    void update(float dt, const AudioSettings &audio);
    void draw();
    void requestClose(bool quit = false);
    void unload();
    bool save();
    void seek(float seconds);
    void play();
    bool dirty() const { return revision_ != savedRevision_; }
    const Cinematic &document() const { return document_; }
    const CinematicPlayer &preview() const { return player_; }
    size_t audioVoices() const { return audio_.voices(); }
    static std::filesystem::path openingDirectory();
    bool openingRequested = false, storyFinished = false, storyCancelled = false;
    void playStory(bool rewind = true);
    void playIntro(bool rewind = true);
    void previewDestination();
    bool screening() const { return screening_; }
    bool runtimeIntro() const { return runtimeIntro_; }
    bool editorVisible() const { return active && !ending_ && !cleanPreview_ && !runtimeIntro_; }
    bool showingDestination() const { return ending_; }
    int selectedTrack() const { return track_; }
    int selectedKey() const { return selected_; }
    float previewTrainSpeed() const { return active&&!world_.paths.empty()?player_.animation().pathSpeed():0.f; }

  private:
    TownDocument world_;
    TownNavigation navigation_;
    TownScene scene_;
    PostProcess post_;
    Cinematic document_;
    CinematicPlayer player_;
    CinematicAudio audio_;
    CinematicCast castModels_;
    HubWorld ground_;
    TownCharacters characters_;
    Animals animals_;
    TownActorModels characterModels_;
    AnimalModels animalModels_;
    double actorsTime_ = 0;
    Camera3D view_{};
    std::filesystem::path directory_, file_, audioDirectory_;
    std::vector<std::string> soundFiles_;
    std::deque<std::pair<Cinematic,uint64_t>> undo_, redo_;
    uint64_t revision_ = 0, savedRevision_ = 0, nextRevision_ = 0;
    int track_ = 0, selected_ = 0, anchorChoice_ = -1;
    float sx_ = 1, sy_ = 1;
    bool editCamera_ = false, cleanPreview_ = false, closePrompt_ = false, closingWindow_ = false;
    bool draggingKey_ = false, keyDragChanged_ = false, scrubbing_ = false;
    bool auditioning_ = false;
    float auditionTime_ = 0;
    bool filenameFocus_ = false;
    std::string filenameText_;
    bool screening_ = false, dialogueFocus_ = false;
    bool runtimeIntro_ = false;
    std::string dialogueText_;
    TownScene endingScene_;
    Camera3D endingCamera_{};
    bool ending_ = false;
    float endingTime_ = 0;
    AudioSettings audioSettings_;
    void remember();
    void rebuild();
    void syncActors();
    void undo(bool redo);
    void addKey(int track);
    void deleteKey();
    void cameraPreset(bool interior);
    void attachCamera(int direction);
    void changeTime(float time);
    size_t keyCount(int track) const;
    float keyTime(int track, size_t index) const;
    void setKeyTime(int track, size_t index, float time);
    void label(const std::string &text, float x, float y, int size, Color color) const;
    void panel(Rectangle rect, Color color) const;
    bool button(const std::string &text, Rectangle rect, bool selected = false, bool enabled = true) const;
    bool number(const std::string &name, float &value, float y, float step, float min, float max);
    Vector2 mouse() const;
    void inspector();
    void timeline();
    void subtitles();
    void advancePlayback(float dt, const AudioSettings &audio);
    void wrapped(const std::string &text, float x, float y, float width, int size, Color color) const;
};
} // namespace dw
