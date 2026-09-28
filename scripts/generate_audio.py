#!/usr/bin/env python3
"""Rebuild DeathWard's original synthesized audio. Requires numpy, scipy, soundfile.
No source recordings or downloaded audio are used. Run from any directory.
"""
from pathlib import Path
import numpy as np
from scipy.signal import butter, sosfilt
import soundfile as sf

OUT = Path(__file__).resolve().parents[1] / "assets" / "audio"
OUT.mkdir(parents=True, exist_ok=True)
RATE = 44100
rng = np.random.default_rng(1866)


def clock(seconds):
    return np.arange(round(seconds * RATE)) / RATE


def noise(t, cutoff=1600):
    return sosfilt(butter(2, cutoff, fs=RATE, output="sos"), rng.normal(size=len(t)))


def tone(t, frequency, decay):
    return np.sin(2 * np.pi * frequency * t) * np.exp(-t * decay)


def save(name, data, peak=.7):
    data = np.asarray(data, dtype=float)
    # Short fades avoid discontinuities when a voice starts or finishes.
    n = min(220, len(data) // 4)
    data[:n] *= np.linspace(0, 1, n).reshape((-1,) + (1,) * (data.ndim - 1))
    data[-n:] *= np.linspace(1, 0, n).reshape((-1,) + (1,) * (data.ndim - 1))
    data *= peak / max(.001, np.max(np.abs(data)))
    sf.write(OUT / name, data, RATE, subtype="VORBIS" if name.endswith(".ogg") else "PCM_16")


for variant in range(3):
    t = clock(.48)
    blast = noise(t, 9000) * np.exp(-t * 70)
    body = .7 * np.sin(2 * np.pi * (85 * t + 40 * (1 - np.exp(-t * 35)) / 35)) * np.exp(-t * 24)
    tail = noise(t, 1400) * np.exp(-t * 13)
    gun = np.tanh(2 * (blast + body + .45 * tail))
    echo = np.zeros_like(gun)
    delay = int(.067 * RATE)
    echo[delay:] = .12 * gun[:-delay]
    save(f"shot_{variant}.wav", gun + echo, .8)

    t = clock(.25)
    save(f"stone_{variant}.wav", noise(t, 6500) * np.exp(-t * 48) + .15 * tone(t, 1800 + variant * 130, 25))
    save(f"flesh_{variant}.wav", noise(t, 850) * np.exp(-t * 28) + .3 * tone(t, 110, 32), .6)
    for material, cutoff, pitch in (("gravel", 3400, 115), ("wood", 1500, 210), ("mine", 2400, 90)):
        step = noise(t, cutoff) * np.exp(-t * 35)
        step += .3 * tone(t, pitch + variant * 11, 42)
        # Heel, then granular toe contact.
        at = int(.07 * RATE)
        step[at:] += .32 * noise(t[:-at], cutoff) * np.exp(-t[:-at] * 45)
        save(f"step_{material}_{variant}.wav", step, .48)

t = clock(.5)
save("hurt.wav", noise(t, 650) * np.exp(-t * 13) + .3 * tone(t, 75, 12), .7)
save("dodge.wav", noise(t, 3600) * np.sin(np.pi * np.minimum(t / .3, 1)) ** 2 * np.exp(-t * 8), .55)
save("enemy_death.wav", noise(t, 800) * np.exp(-t * 10) + .3 * tone(t, 65, 10), .55)
save("monster_attack.wav", noise(t, 2200) * np.exp(-t * 22) + .3 * np.sin(2 * np.pi * (250 * t - 100 * t * t)) * np.exp(-t * 18), .6)
save("door.wav", noise(t, 1000) * np.exp(-t * 10) + .25 * tone(t, 230, 16), .55)
t = clock(.85)
save("explosion.wav", np.tanh(noise(t, 2300) * 3 + .35 * np.sin(2 * np.pi * 48 * t)) * np.exp(-t * 6), .8)
save("player_death.wav", (tone(t, 130, 4) + .6 * tone(t, 97, 3) + noise(t, 450)) * np.exp(-t * 3), .65)
t = clock(.3)
save("warning.wav", (tone(t, 620, 12) + .3 * tone(t, 930, 15)) * (1 - np.exp(-t * 170)), .55)
save("ui.wav", tone(t, 720, 45) + .25 * tone(t, 1080, 50), .35)
for name, notes in (("pickup", (660, 880, 1320)), ("clear", (330, 440, 660)), ("test", (440, 660, 880))):
    t = clock(1.05)
    sound = np.zeros_like(t)
    for i, hz in enumerate(notes):
        at = int(i * .12 * RATE)
        s = t[:len(t) - at]
        sound[at:] += (tone(s, hz, 7) + .22 * tone(s, hz * 2, 12)) * (1 - np.exp(-s * 250))
    save(name + ".wav", sound, .5)

# Stereo ambience is quiet, sparse and seamless. Periodic FFT-filtered noise and
# oscillators span complete cycles; localized details wrap across the loop boundary.
DURATION = 16
t = clock(DURATION)
frequencies = np.fft.rfftfreq(len(t), 1 / RATE)


def air(cutoff):
    spectrum = np.fft.rfft(rng.normal(size=len(t)))
    spectrum *= 1 / (1 + (frequencies / cutoff) ** 2)
    spectrum[0] = 0
    wave = np.fft.irfft(spectrum, len(t))
    return wave / max(.001, np.std(wave))


def detail(track, at, signal, pan):
    indices = (np.arange(len(signal)) + int(at * RATE)) % len(track)
    track[indices, 0] += signal * np.sqrt(1 - pan)
    track[indices, 1] += signal * np.sqrt(pan)


for place in ("town", "frontier", "canyon", "mine"):
    cutoff = {"town": 700, "frontier": 2200, "canyon": 450, "mine": 180}[place]
    common = air(cutoff)
    gust = .45 + .18 * np.sin(2 * np.pi * t / DURATION) + .12 * np.sin(6 * np.pi * t / DURATION)
    track = np.column_stack([(.7 * common + .3 * air(cutoff)) * gust for _ in range(2)]) * .12
    for n in range(5 if place != "frontier" else 10):
        at, pan = rng.uniform(0, DURATION), rng.uniform(.15, .85)
        s = clock(.6)
        if place in ("frontier", "canyon"):
            hz = rng.uniform(1300, 2300)
            chirp = np.sin(2 * np.pi * (hz * s + 85 * np.sin(s * 20)))
            signal = chirp * np.sin(np.pi * s / .6) ** 4 * np.exp(-s * 5) * .055
        elif place == "town":
            signal = (tone(s, rng.uniform(180, 240), 9) + noise(s, 550)) * .04
        else:
            signal = tone(s, rng.uniform(600, 1400), 22) * .07
        detail(track, at, signal, pan)
    if place == "frontier":
        track += np.column_stack([air(6500), air(6500)]) * .013
    # The periodic noise and wrapped details already join at the loop boundary.
    sf.write(OUT / (place + ".ogg"), track, RATE, subtype="VORBIS")
print(f"Generated {len(list(OUT.glob('*.wav')))} effects and four ambience loops in {OUT}")
