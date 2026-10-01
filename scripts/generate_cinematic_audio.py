#!/usr/bin/env python3
"""Original synthesized train and storm preview sounds; no source recordings."""
from pathlib import Path
import numpy as np
import wave as wave_file

OUT = Path(__file__).resolve().parents[1] / 'assets/audio/cinematic'
OUT.mkdir(parents=True, exist_ok=True)
RATE = 22050
rng = np.random.default_rng(1866)


def noise(seconds, cutoff):
    t = np.arange(int(seconds * RATE)) / RATE
    f = np.fft.rfftfreq(len(t), 1 / RATE)
    spectrum = np.fft.rfft(rng.normal(size=len(t))) / (1 + (f / cutoff) ** 2)
    spectrum[0] = 0
    wave = np.fft.irfft(spectrum, len(t))
    return t, wave / max(.001, np.std(wave))


def save(name, wave):
    wave = .7 * wave / max(.001, np.max(np.abs(wave)))
    with wave_file.open(str(OUT / name), 'wb') as output:
        output.setnchannels(1)
        output.setsampwidth(2)
        output.setframerate(RATE)
        output.writeframes((wave * 32767).astype('<i2').tobytes())


t, rumble = noise(6, 420)
beat = np.exp(-((t * 3) % 1) * 28) + .5 * np.exp(-((t * 3 + .23) % 1) * 32)
save('train_roll.wav', rumble * (.2 + beat * .35) + .1 * np.sin(2 * np.pi * 54 * t) * beat)
t, air = noise(12, 1500)
save('storm_wind.wav', air * (.5 + .23 * np.sin(2 * np.pi * t / 6) + .15 * np.sin(2 * np.pi * t / 3)))
t, brake = noise(3.5, 3300)
envelope = (1 - np.exp(-t * 18)) * np.maximum(0, 1 - t / 3.5) ** 1.3
squeal = np.sin(2 * np.pi * (1050 * t - 85 * t * t) + .9 * np.sin(t * 27))
save('train_brake.wav', (.3 * brake + .3 * squeal + .14 * np.sin(2 * np.pi * 73 * t)) * envelope)
print('Wrote original train roll, wind and emergency brake sounds to', OUT)
