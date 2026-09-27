#include "world/Campaign.hpp"
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOGDI
#define NOUSER
#include <windows.h>
#else
#include <fcntl.h>
#include <unistd.h>
#endif

namespace dw {
namespace {
uint64_t checksum(const std::string &text) {
    uint64_t h = 14695981039346656037ULL;
    for (unsigned char c : text) {
        h ^= c;
        h *= 1099511628211ULL;
    }
    return h;
}
void writeStats(std::ostream &out, const Stats &s) {
    out << std::setprecision(17) << s.duration << ' ' << s.bossDuration << ' ' << s.damageDealt << ' '
        << s.damageTaken << ' ' << s.shots << ' ' << s.projectiles << ' ' << s.kills << ' ' << s.explosions
        << ' ' << s.bounces << ' ' << s.splits << ' ' << s.ghosts << ' ' << s.maxProjectiles << ' '
        << s.maxDepth << ' ' << s.largestKillChain << ' ' << s.rooms << ' ' << s.suppressed << '\n';
}
void readStats(std::istream &in, Stats &s) {
    in >> s.duration >> s.bossDuration >> s.damageDealt >> s.damageTaken >> s.shots >> s.projectiles >>
        s.kills >> s.explosions >> s.bounces >> s.splits >> s.ghosts >> s.maxProjectiles >> s.maxDepth >>
        s.largestKillChain >> s.rooms >> s.suppressed;
    if (!std::isfinite(s.duration) || !std::isfinite(s.bossDuration) || !std::isfinite(s.damageDealt) ||
        !std::isfinite(s.damageTaken) || s.duration < 0)
        throw std::runtime_error("Invalid run statistics in save");
}
size_t count(std::istream &in, size_t limit) {
    size_t n = 0;
    if (!(in >> n) || n > limit)
        throw std::runtime_error("Invalid save collection size");
    return n;
}
void writeSummary(std::ostream &out, const RunSummary &s) {
    out << s.id << ' ' << s.seed << ' ' << std::quoted(s.version) << ' ' << std::quoted(s.expedition) << ' '
        << std::quoted(s.startingContext) << ' ' << int(s.reason) << ' ' << s.rescued << ' ' << s.bossKilled
        << ' ' << s.altarDestroyed << ' ' << s.interrupted << '\n';
    writeStats(out, s.stats);
    out << s.items.size();
    for (auto id : s.items)
        out << ' ' << int(id);
    out << '\n' << s.consequences.size() << '\n';
    for (const auto &line : s.consequences)
        out << std::quoted(line) << '\n';
}
RunSummary readSummary(std::istream &in) {
    RunSummary s;
    int reason = 0;
    in >> s.id >> s.seed >> std::quoted(s.version) >> std::quoted(s.expedition) >>
        std::quoted(s.startingContext) >> reason >> s.rescued >> s.bossKilled >> s.altarDestroyed >>
        s.interrupted;
    if (reason < 0 || reason > 3)
        throw std::runtime_error("Invalid outcome in save");
    s.reason = EndReason(reason);
    readStats(in, s.stats);
    size_t n = count(in, 4096);
    for (size_t i = 0; i < n; ++i) {
        int id = -1;
        in >> id;
        if (id < 0 || id >= ItemCount)
            throw std::runtime_error("Invalid saved item");
        s.items.push_back(ItemId(id));
    }
    n = count(in, 100);
    for (size_t i = 0; i < n; ++i) {
        std::string line;
        in >> std::quoted(line);
        s.consequences.push_back(line);
    }
    return s;
}
std::string serialize(const Campaign &c) {
    std::ostringstream out;
    const auto &w = c.world;
    out << c.nextRunId << ' ' << w.population << ' ' << w.prosperity << ' ' << w.law << ' ' << w.minersRescued
        << ' ' << w.bossDefeated << ' ' << w.mineOpen << ' ' << w.altarDestroyed << ' ' << w.mineDebt << ' '
        << w.completed << '\n';
    out << w.flags.size() << '\n';
    for (const auto &flag : w.flags)
        out << std::quoted(flag) << '\n';
    for (const auto &npc : w.npcs)
        out << std::quoted(npc.name) << ' ' << std::quoted(npc.state) << ' ' << npc.relationship << '\n';
    out << bool(c.pending) << '\n';
    if (c.pending)
        writeSummary(out, *c.pending);
    out << c.history.size() << '\n';
    for (const auto &s : c.history)
        writeSummary(out, s);
    return out.str();
}
Campaign deserialize(const std::string &payload) {
    Campaign c;
    auto &w = c.world;
    std::istringstream in(payload);
    in >> c.nextRunId >> w.population >> w.prosperity >> w.law >> w.minersRescued >> w.bossDefeated >>
        w.mineOpen >> w.altarDestroyed >> w.mineDebt >> w.completed;
    size_t n = count(in, 1024);
    for (size_t i = 0; i < n; ++i) {
        std::string flag;
        in >> std::quoted(flag);
        w.flags.insert(flag);
    }
    for (auto &npc : w.npcs)
        in >> std::quoted(npc.name) >> std::quoted(npc.state) >> npc.relationship;
    bool pending = false;
    in >> pending;
    if (pending)
        c.pending = readSummary(in);
    n = count(in, 100000);
    for (size_t i = 0; i < n; ++i)
        c.history.push_back(readSummary(in));
    if (!in || c.nextRunId == 0 || w.population < 0 || w.prosperity < 0 || w.prosperity > 100 ||
        w.mineDebt < 0 || w.mineDebt > 50)
        throw std::runtime_error("Invalid campaign save");
    in >> std::ws;
    if (!in.eof())
        throw std::runtime_error("Unexpected data in save");
    std::set<uint64_t> ids;
    for (const auto &s : c.history)
        if (s.id == 0 || s.id >= c.nextRunId || !ids.insert(s.id).second)
            throw std::runtime_error("Invalid history IDs");
    if (c.pending && (c.pending->id == 0 || c.pending->id >= c.nextRunId || ids.contains(c.pending->id)))
        throw std::runtime_error("Invalid pending run ID");
    return c;
}
void saveAtomic(const std::filesystem::path &path, const Campaign &c) {
    if (!path.parent_path().empty())
        std::filesystem::create_directories(path.parent_path());
    const std::string payload = serialize(c);
    auto temp = path;
    temp += ".tmp";
    {
        std::ofstream out(temp, std::ios::binary | std::ios::trunc);
        if (!out)
            throw std::runtime_error("Cannot create save: " + temp.string());
        out << "DEATHWARD 1 " << checksum(payload) << '\n' << payload;
        out.flush();
        if (!out)
            throw std::runtime_error("Cannot write campaign save");
    }
#ifdef _WIN32
    if (!MoveFileExW(temp.c_str(), path.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
        throw std::runtime_error("Cannot replace campaign save");
#else
    int fd = ::open(temp.c_str(), O_RDONLY);
    if (fd < 0)
        throw std::runtime_error("Cannot open save for sync");
    int syncResult = ::fsync(fd);
    ::close(fd);
    if (syncResult != 0)
        throw std::runtime_error("Cannot sync campaign save");
    std::filesystem::rename(temp, path);
    auto parent = path.parent_path().empty() ? std::filesystem::path(".") : path.parent_path();
    fd = ::open(parent.c_str(), O_RDONLY | O_DIRECTORY);
    if (fd >= 0) {
        ::fsync(fd);
        ::close(fd);
    }
#endif
}
} // namespace

CampaignStore::CampaignStore(std::filesystem::path path) : path_(std::move(path)) {
    if (!std::filesystem::exists(path_))
        return;
    if (std::filesystem::file_size(path_) > 64 * 1024 * 1024)
        throw std::runtime_error("Campaign save exceeds size limit");
    std::ifstream in(path_, std::ios::binary);
    std::string magic;
    int version = 0;
    uint64_t hash = 0;
    in >> magic >> version >> hash;
    in.get();
    std::string payload((std::istreambuf_iterator<char>(in)), {});
    if (magic != "DEATHWARD" || version != 1 || checksum(payload) != hash)
        throw std::runtime_error("Campaign save is damaged or unsupported. Original file was preserved: " +
                                 path_.string());
    campaign_ = deserialize(payload);
}
void CampaignStore::commit(Campaign next) {
    saveAtomic(path_, next);
    campaign_ = std::move(next);
}
std::string CampaignStore::worldContext(const WorldState &w) {
    Campaign c;
    c.world = w;
    return serialize(c);
}
uint64_t CampaignStore::begin(uint64_t seed, const std::string &expedition) {
    if (campaign_.pending)
        throw std::runtime_error("An expedition is already pending");
    Campaign next = campaign_;
    RunSummary s;
    s.id = next.nextRunId++;
    s.seed = seed;
    s.expedition = expedition;
    s.startingContext = worldContext(next.world);
    next.pending = s;
    commit(std::move(next));
    return s.id;
}
void CampaignStore::checkpoint(const RunSummary &s) {
    if (!campaign_.pending || campaign_.pending->id != s.id)
        throw std::runtime_error("Cannot checkpoint an inactive expedition");
    Campaign next = campaign_;
    next.pending = s;
    commit(std::move(next));
}
RunSummary CampaignStore::resolve(const RunSummary &input, EndReason reason) {
    for (const auto &previous : campaign_.history)
        if (previous.id == input.id)
            return previous;
    if (!campaign_.pending || campaign_.pending->id != input.id)
        throw std::runtime_error("Cannot resolve an inactive expedition");
    Campaign next = campaign_;
    auto &w = next.world;
    RunSummary s = input;
    s.reason = reason;
    s.interrupted = reason == EndReason::Interrupted;
    s.consequences.clear();
    auto note = [&](std::string message) { s.consequences.push_back(std::move(message)); };
    if (s.rescued && !w.minersRescued) {
        w.minersRescued = true;
        w.population += 6;
        w.npcs[1].relationship += 2;
        w.flags.insert("miners_home");
        note("Six miners return. Population +6; Mary Bell remembers.");
    }
    if (s.bossKilled && !w.bossDefeated) {
        w.bossDefeated = true;
        w.law = std::min(100, w.law + 5);
        w.npcs[0].relationship++;
        w.flags.insert("hollow_sheriff_dead");
        note("The Hollow Sheriff falls. Law +5; Cole trusts you.");
    }
    if (s.altarDestroyed && !w.altarDestroyed) {
        w.altarDestroyed = true;
        w.flags.insert("altar_destroyed");
        w.flags.erase("something_followed");
        w.npcs[2].relationship++;
        note("The altar is broken. Black Creek sleeps more easily.");
    }
    if (reason == EndReason::Victory) {
        ++w.completed;
        if (w.bossDefeated && w.minersRescued) {
            if (w.mineDebt > 0) {
                int restored = std::min(w.mineDebt, 100 - w.prosperity);
                w.prosperity += restored;
                w.mineDebt = 0;
                note("The mine recovers its lost prosperity.");
            }
            if (!w.flags.contains("mine_reopened")) {
                w.prosperity = std::min(100, w.prosperity + 12);
                w.flags.insert("mine_reopened");
                note("Red Hollow reopens. Prosperity +12.");
            }
            w.mineOpen = true;
            w.flags.erase("mine_setback");
        } else {
            w.mineOpen = false;
            w.flags.insert("miners_stranded");
            note("The threat is beaten, but miners remain stranded. Return to rescue them.");
        }
    } else {
        int loss = std::min({8, w.prosperity, 50 - w.mineDebt});
        w.prosperity -= loss;
        w.mineDebt += loss;
        w.mineOpen = false;
        w.flags.insert("mine_setback");
        note("The expedition ends early. Mine closed; prosperity -" + std::to_string(loss) +
             ". A return can repair this.");
    }
    if (w.minersRescued)
        w.flags.erase("miners_stranded");
    if (!w.altarDestroyed) {
        w.flags.insert("something_followed");
        note("The altar remains. Something followed you home.");
    }
    if (s.interrupted)
        note("Interrupted expedition: history uses the last saved checkpoint.");
    if (s.consequences.empty())
        note("Black Creek remembers another journey. Previous rewards are not repeated.");
    next.history.push_back(s);
    next.pending.reset();
    commit(std::move(next));
    return s;
}
bool CampaignStore::recover() {
    if (!campaign_.pending)
        return false;
    resolve(*campaign_.pending, EndReason::Interrupted);
    return true;
}
void CampaignStore::reset() {
    if (std::filesystem::exists(path_))
        std::filesystem::copy_file(path_, path_.string() + ".bak",
                                   std::filesystem::copy_options::overwrite_existing);
    commit(Campaign{});
}
void CampaignStore::setFlag(const std::string &flag, bool value) {
    Campaign next = campaign_;
    if (value)
        next.world.flags.insert(flag);
    else
        next.world.flags.erase(flag);
    commit(std::move(next));
}
std::filesystem::path CampaignStore::defaultPath() {
    if (const char *custom = std::getenv("DEATHWARD_SAVE_PATH"))
        return custom;
#ifdef _WIN32
    if (const char *base = std::getenv("LOCALAPPDATA"))
        return std::filesystem::path(base) / "DeathWard" / "campaign.save";
#else
    if (const char *base = std::getenv("XDG_DATA_HOME"))
        return std::filesystem::path(base) / "deathward" / "campaign.save";
    if (const char *base = std::getenv("HOME"))
        return std::filesystem::path(base) / ".local/share/deathward/campaign.save";
#endif
    return "deathward-campaign.save";
}
std::string outcomeTitle(const RunSummary &s) {
    if (s.reason == EndReason::Death)
        return "THE FRONTIER TOOK ITS DUE";
    if (s.reason == EndReason::Interrupted)
        return "AN UNFINISHED EXPEDITION";
    if (s.reason == EndReason::Retreat)
        return "YOU LIVED TO RETURN";
    return s.rescued ? "SIX SOULS BROUGHT HOME" : "VICTORY HAS A HOLLOW SOUND";
}
std::string npcDialogue(const WorldState &w, size_t npc) {
    switch (npc) {
    case 0:
        return w.bossDefeated ? "That thing wore my badge. Thank you for ending it."
                              : "Something down there is wearing my face. Put it in the ground.";
    case 1:
        return w.minersRescued ? "Six places at the table. You brought every one of them home."
                               : "My brother is still in that mine. Bring them home, please.";
    case 2:
        return w.flags.contains("something_followed")
                   ? "Your shadow came through the door a moment before you did."
               : w.altarDestroyed ? "The church bell finally sounds like a bell again."
                                  : "If you find an altar below, leave nothing standing.";
    case 3:
        return w.mineOpen ? "Red Hollow is working again. This town has a tomorrow."
                          : "No ore, no wages. Clear the mine and get our people back.";
    default:
        return w.flags.contains("mine_setback")
                   ? "Rest here. A bad journey need not be your last."
                   : "A fresh bandage for every departure. Come back needing fewer.";
    }
}
} // namespace dw
