#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

namespace dw {

enum class HealthEffectKind { BlackBurst, BoneBreakVisuals, GoldenBurst, ConversionAnimation };
struct HealthEffect { HealthEffectKind kind; int count = 1; };

// Ordinary Isaac, empty inventory, Repentance 1.7.9b. These are native API
// units: red/soul/max are halves; bone/rotten/golden/broken are counters.
// Source add/remove API semantics are preserved, including raw negative rotten
// results. Gameplay callers must validate pickup/cost requests separately.
// See player-health/manifest.json for executed-code scope and effect boundaries.
// Simulation adapts its canonical health fields through a transient snapshot.
struct SourcePlayerHealth {
    int maxRed = 6, red = 6, eternal = 0, soul = 0;
    uint32_t blackMask = 0;
    int golden = 0, bone = 0;
    uint32_t boneMask = 0;
    int broken = 0, rotten = 0;
    std::vector<HealthEffect> effects;

    int limit() const { return std::max(0, 24 - 2 * broken); }
    int redCapacity() const { return maxRed + 2 * bone; }
    int occupiedSlots() const { return (std::min(maxRed, red) + 1) / 2 + (soul + 1) / 2 + bone; }
    bool isBone(int slot) const { return bone > 0 && (boneMask & bit(slot)); }
    bool isBlack(int halfIndex) const {
        return halfIndex >= 1 && halfIndex <= soul && (halfIndex & 1) && (blackMask & bit((halfIndex - 1) / 2));
    }
    // Admitted ordinary blended pickup, 0x6bf6be. Each of its two halves
    // checks red eligibility again; a remaining half may become soul health.
    bool collectBlended() {
        int remaining=2;
        while(remaining>0) {
            if(red<redCapacity()) {addRed(1);--remaining;}
            else if(soul+redCapacity()<limit()) {addSoul(remaining);return true;}
            else break;
        }
        return remaining<2;
    }

    void addRed(int amount) {
        const int previous = red;
        red = std::clamp(red + amount, 0, redCapacity());
        if (red != previous) reconcileRed();
        reconcileGolden();
        reconcileBone();
    }
    void addMaxRed(int amount) {
        maxRed = std::min(limit(), maxRed + amount);
        if (maxRed < 0) {
            const int excess = maxRed;
            maxRed = 0;
            addBone(excess / 2);
        }
        const int capacity = redCapacity();
        if (soul + capacity > limit()) soul = std::max(0, limit() - capacity);
        red = std::min(red, capacity);
        reconcileBlack();
        reconcileRed();
        reconcileGolden();
        reconcileBone();
    }
    void addSoul(int amount) {
        soul = std::max(0, soul + amount);
        if (soul + redCapacity() > limit()) soul = limit() - redCapacity();
        reconcileBlack();
        reconcileGolden();
        reconcileBone();
    }
    void addBlack(int amount) {
        int end = soul + (soul & 1);
        int odd = amount & 1, startAdjustment = 0;
        if ((soul & 1) && odd) { startAdjustment = -1; odd = 0; }
        if (end + redCapacity() >= limit() - 1) {
            int painted = 0;
            for (int half = end - 1; half > 0 && painted < amount; half -= 2) {
                if (!isBlack(half)) { blackMask |= bit(half / 2); painted += 2; }
            }
        } else {
            const int finish = (end + odd + amount) / 2;
            for (int slot = (end + startAdjustment) / 2; slot < finish; ++slot) blackMask |= bit(slot);
        }
        addSoul(amount);
        reconcileGolden();
        reconcileBone();
    }
    void addEternal(int amount) {
        eternal = std::max(0, eternal + amount);
        if (eternal <= 1) return;
        effects.push_back({HealthEffectKind::ConversionAnimation, 13});
        const int halves = (eternal / 2) * 2;
        addMaxRed(halves);
        addRed(halves);
        eternal %= 2;
    }
    void addGolden(int amount) {
        golden = std::clamp(golden + amount, 0, occupiedSlots());
        reconcileGolden();
    }
    void addBone(int amount) {
        if (amount < 0) {
            bone = std::max(0, bone + amount);
            red = std::min(red, redCapacity());
            reconcileBone();
            reconcileRed();
            return;
        }
        const int displaced = std::min(soul, soul + 2 * (bone + amount) + maxRed - limit());
        if (displaced > 0) addSoul(-displaced);
        amount = std::min(amount, limit() / 2 - (soul + 2 * bone + maxRed + 1) / 2);
        if (amount <= 0) return;
        const int first = (soul + 1) / 2 + bone;
        bone += amount;
        for (int i = 0; i < amount; ++i) boneMask |= bit(first + i);
        reconcileRed();
    }
    void addRotten(int amount) {
        red = std::clamp(red + amount, 0, redCapacity());
        rotten += amount > 0 ? (amount + 1) / 2 : (amount - 1) / 2;
        reconcileRed();
        reconcileGolden();
        reconcileBone();
    }
    void addBroken(int amount) {
        broken = std::clamp(broken + amount, 0, 12);
        addMaxRed(0);
    }
    void newFloor() {
        if (eternal <= 0) return;
        eternal = 0;
        effects.push_back({HealthEffectKind::ConversionAnimation, 13});
        addMaxRed(2);
        addRed(2);
    }

    // Integer health mutation only. Caller supplies validated source damage.
    // Dodge, hit cooldown, source flags/prechecks, death, deal chance and world
    // effects are outside this kernel. Effects are intents, not applied damage.
    void damage(int amount, bool requestRedFirst = false) {
        const int beforeNonRed = (soul + 1) / 2 + bone;
        const int beforeRed = (std::min(maxRed, red) + 1) / 2;
        const bool redFirst = requestRedFirst && red >= amount;
        int trailingSoul = soul;
        bool filledBone = false;
        if (bone > 0) {
            trailingSoul = 0;
            for (int slot = beforeNonRed - 1; slot >= 0 && !isBone(slot); --slot)
                trailingSoul += trailingSoul == 0 && (soul & 1) ? 1 : 2;
            trailingSoul = std::min(trailingSoul, soul);
            filledBone = red >= redCapacity() - 1;
        }
        if (trailingSoul > 0 && !redFirst) {
            amount = std::min(amount, trailingSoul);
            for (int half = soul; half > soul - amount; --half) {
                if (isBlack(half)) {
                    blackMask &= ~bit(half / 2);
                    reconcileGolden();
                    reconcileBone();
                    effects.push_back({HealthEffectKind::BlackBurst});
                }
            }
            if (eternal > 0 && red <= 0 && bone <= 0 && soul - amount <= 0) {
                amount = std::max(0, amount - eternal); eternal = 0;
            }
            if (amount > 0) soul -= std::min(soul, amount);
        } else if (bone > 0 && !filledBone && !redFirst) {
            if (eternal > 0 && red <= 0 && soul <= 0 && bone <= 1) {
                amount = std::max(0, amount - eternal); eternal = 0;
            }
            if (amount > 0) {
                --bone;
                reconcileRed();
                effects.push_back({HealthEffectKind::BoneBreakVisuals});
            }
        } else {
            if (rotten > 0) {
                const int eligible = redFirst ? std::max(0, 2 * rotten - red + amount) : amount;
                amount += std::min(rotten, eligible);
            }
            if (bone > 0 && filledBone) amount = std::min(amount, ((~red) & 1) + 1);
            if (eternal > 0 && (!requestRedFirst || amount > red - ((soul + bone <= 0) ? 1 : 0) - rotten)) {
                amount = std::max(0, amount - eternal); eternal = 0;
            }
            const int rottenDamage = redFirst ? std::max(0, 2 * rotten - red + amount) : amount;
            rotten = std::max(0, rotten - (rottenDamage + 1) / 2);
            addRed(-amount);
        }
        const int beforeGolden = golden;
        const int lost = std::max(0, beforeNonRed - ((soul + 1) / 2 + bone))
                       + std::max(0, beforeRed - (std::min(maxRed, red) + 1) / 2);
        golden = std::max(0, golden - lost);
        if (golden < beforeGolden) effects.push_back({HealthEffectKind::GoldenBurst, beforeGolden - golden});
    }

private:
    static uint32_t bit(int index) { return uint32_t{1} << (uint32_t(index) & 31); }
    void reconcileRed() {
        rotten = std::min(rotten, (red + 1) / 2);
        red = std::max(red, 2 * rotten);
    }
    void reconcileGolden() {
        const int slots = occupiedSlots();
        if (golden > slots) {
            effects.push_back({HealthEffectKind::GoldenBurst, golden - slots});
            golden = slots;
        }
    }
    void reconcileBlack() {
        if (soul == 0) { blackMask = 0; return; }
        const int slots = (soul + 1) / 2;
        int excess = 0;
        for (int slot = slots; slot < 32; ++slot) {
            if (blackMask & bit(slot)) { ++excess; blackMask &= ~bit(slot); }
        }
        for (int half = soul; half > 0 && excess > 0; --half) {
            if ((half & 1) && !isBlack(half)) { blackMask |= bit(half / 2); --excess; }
        }
    }
    void reconcileBone() {
        bone = std::min(bone, limit() / 2 - (maxRed + soul + 1) / 2);
        if (bone <= 0) { bone = 0; boneMask = 0; return; }
        const int slots = (soul + 1) / 2 + bone;
        boneMask &= (uint32_t{1} << slots) - 1;
        int remaining = bone;
        for (int slot = 0; slot < slots; ++slot) {
            if ((boneMask & bit(slot)) && --remaining < 0) boneMask &= ~bit(slot);
        }
        for (int slot = slots - 1; slot >= 0 && remaining > 0; --slot) {
            if (!(boneMask & bit(slot))) { boneMask |= bit(slot); --remaining; }
        }
    }
};

} // namespace dw
