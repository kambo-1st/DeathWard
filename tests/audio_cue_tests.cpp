#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok, const char *message) {
    if (!ok)
        throw std::runtime_error(message);
}
size_t count(const Simulation &run, AudioCueKind kind) {
    return size_t(std::count_if(run.audioCues.cues().begin(), run.audioCues.cues().end(),
                                [=](auto cue) { return cue.kind == kind; }));
}
void verify() {
    AudioCueQueue queue;
    for (int i = 0; i < 10000; ++i)
        queue.push(AudioCueKind::StoneHit);
    queue.push(AudioCueKind::Hurt);
    queue.push(AudioCueKind::PlayerDeath);
    check(queue.cues().size() == AudioCueQueue::Capacity, "unconsumed cues stay bounded");
    check(std::any_of(queue.cues().begin(), queue.cues().end(),
                      [](auto c) { return c.kind == AudioCueKind::PlayerDeath; }),
          "important cues displace impacts when full");
    Simulation run(42, 1, {});
    run.debugScenario = true;
    run.grant(ItemId::Split);
    run.audioCues.clear();
    Input input;
    input.aim = add(run.player.position, {0, 0, -10});
    input.fire = true;
    for (int i = 0; i < 40; ++i)
        run.step(input);
    check(run.stats.shots >= 2 && count(run, AudioCueKind::Shot) == run.stats.shots,
          "one report per actual trigger pull across multiple fixed steps");
    const auto reports = count(run, AudioCueKind::Shot);
    Event child;
    child.position = run.player.position;
    child.direction = {1, 0, 0};
    run.queueRoot(child);
    run.drainEvents();
    check(count(run, AudioCueKind::Shot) == reports,
          "derived projectile events do not replay the revolver report");
    const auto target = run.spawn(EnemyKind::Gunman, add(run.player.position, {2, 0, 0}));
    Event hit;
    hit.type = EventType::Damage;
    hit.target = target;
    hit.damage = 1;
    run.audioCues.clear();
    run.queueRoot(hit);
    run.drainEvents();
    check(count(run, AudioCueKind::FleshHit) == 1 && count(run, AudioCueKind::EnemyDeath) == 0,
          "a nonlethal hit produces impact without death");
    hit.damage = 10000;
    run.queueRoot(hit);
    run.drainEvents();
    run.queueRoot(hit);
    run.drainEvents();
    check(count(run, AudioCueKind::EnemyDeath) == 1, "dead targets cannot emit duplicate death sounds");
    run.audioCues.clear();
    input.fire = false;
    input.dodge = true;
    run.step(input);
    run.step(input);
    check(count(run, AudioCueKind::Dodge) == 1, "dodge cooldown blocks repeated cues");
    run.finishDebug(false);
    run.finishDebug(false);
    check(count(run, AudioCueKind::PlayerDeath) == 1, "player death emits once");
    const auto epoch = run.audioEpoch;
    run.enterRoom(0);
    check(run.audioEpoch > epoch && count(run, AudioCueKind::Shot) == 0 &&
              count(run, AudioCueKind::PlayerDeath) == 0,
          "room replacement discards old presentation cues");

    Simulation a(1866, 1, {}), b(1866, 1, {});
    a.debugScenario = b.debugScenario = true;
    input.dodge = false;
    input.fire = true;
    input.aim = a.arena.rooms[0].center;
    for (int i = 0; i < 120; ++i) {
        a.step(input);
        b.step(input);
        b.audioCues.clear();
    }
    check(a.stats.shots == b.stats.shots && a.stats.projectiles == b.stats.projectiles &&
              a.combatRng.state == b.combatRng.state && a.encounterRng.state == b.encounterRng.state &&
              a.rewardRng.state == b.rewardRng.state && distance(a.player.position, b.player.position) == 0,
          "consuming audio has no effect on simulation state or randomness");
}
} // namespace
int main() {
    try {
        verify();
        std::cout << "PASS bounded/prioritized audio cues, confirmed actions, cleanup and determinism\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
