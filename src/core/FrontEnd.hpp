#pragma once
#include "audio/AudioSystem.hpp"
#include "core/VisualSettings.hpp"
#include "world/SaveSlots.hpp"

namespace dw {
enum class FrontPage { Studio, Title, Slots, Settings, Loading };
// Presentation is independent of Game and both editors. No hub is constructed
// and no campaign is modified while browsing the front end.
class FrontEnd {
  public:
    FrontEnd(std::filesystem::path slots, std::filesystem::path audioFile,
             std::filesystem::path visualFile, AudioSettings audio, VisualSettings visual, AudioStatus status);
    ~FrontEnd();
    FrontEnd(const FrontEnd &) = delete;
    FrontEnd &operator=(const FrontEnd &) = delete;
    void update(float dt);
    void draw() const;
    void publish() const;
    FrontPage page = FrontPage::Studio;
    std::optional<SaveSlot> launch;
    AudioSettings audioSettings;
    VisualSettings visualSettings;
    bool quit = false;
  private:
    SaveSlots store_;
    std::array<SaveSlot, SaveSlots::Count> slots_;
    std::filesystem::path audioFile_, visualFile_;
    AudioSettings beforeAudio_;
    VisualSettings beforeVisual_;
    AudioStatus audioStatus_;
    Font titleFont_{}, bodyFont_{};
    int selected_ = 0, focus_ = 0, dragging_ = -1;
    float elapsed_ = 0, time_ = 0;
    std::string error_;
    void openSettings();
    void activate(int control);
    void adjust(int control, float amount);
    void refresh();
    void background() const;
    void title(float y, float size, float opacity = 1) const;
    void text(const std::string &label, float x, float y, float size, Color color, bool center = false,
              bool display = false) const;
    void button(Rectangle rect, const char *label, bool focused, bool enabled = true) const;
};
}
