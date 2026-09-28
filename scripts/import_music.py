#!/usr/bin/env python3
"""Import selected tracks from the user's Western Music asset pack.

Requires numpy and soundfile only when regenerating. The game uses the packaged
files. Original compositions, stereo channels, sample rates and durations are
retained; constant gain and 10 ms edge fades prepare them for the game mixer.
"""
import argparse
import hashlib
import json
from pathlib import Path

import numpy as np
import soundfile as sf

TRACKS = {
    "town.ogg": "12. In This Town.wav",
    "frontier.ogg": "Update v1_5/Rebuilding.wav",
    "canyon.ogg": "07. The Hunt - The Journey.wav",
    "mine.ogg": "04. Mystery at Sundown.wav",
    "combat.ogg": "08. The Hunt - The Thrill.wav",
    "boss.ogg": "09. The Hunt - The Terror.wav",
    "victory.ogg": "10. Chasing Victory.wav",
    "defeat.ogg": "Update v1_5/Sad Emotions.wav",
    "departure.wav": "Stingers/Stinger - 01 - Whistle & Guitar.wav",
    "boss_entry.wav": "Stingers/Stinger - 05 - Rattle.wav",
    "victory_stinger.wav": "Stingers/Stinger - 07 - Guitar Shimmer.wav",
    "defeat_stinger.wav": "Stingers/Stinger - 02 - Snare & Bell - B.wav",
}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path)
    parser.add_argument("--output", type=Path,
                        default=Path(__file__).resolve().parents[1] / "assets/audio/music")
    args = parser.parse_args()
    args.output.mkdir(parents=True, exist_ok=True)
    manifest = {"source_pack": "Western Music", "files": []}
    for name, original in TRACKS.items():
        source = args.source / original
        samples, rate = sf.read(source, dtype="float32", always_2d=True)
        if samples.shape[1] != 2 or not np.isfinite(samples).all():
            raise ValueError(f"Expected finite stereo audio: {source}")
        rms = float(np.sqrt(np.mean(samples.astype(np.float64) ** 2)))
        peak = float(np.max(np.abs(samples)))
        target = 0.10 if name.endswith(".ogg") else 0.16
        gain = min(target / max(rms, 1e-6), .89 / max(peak, 1e-6), 2.0)
        samples *= gain
        edge = min(round(rate * .01), len(samples) // 2)
        samples[:edge] *= np.linspace(0, 1, edge)[:, None]
        samples[-edge:] *= np.linspace(1, 0, edge)[:, None]
        output = args.output / name
        # Keep encoder writes bounded for libsndfile builds that cannot accept a
        # multi-minute Vorbis buffer in one call.
        with sf.SoundFile(output, "w", samplerate=rate, channels=2,
                          subtype="VORBIS" if name.endswith(".ogg") else "PCM_16") as encoded:
            for start in range(0, len(samples), 16384):
                encoded.write(samples[start:start + 16384])
        manifest["files"].append({
            "file": name, "source": original,
            "source_sha256": hashlib.sha256(source.read_bytes()).hexdigest(),
            "sha256": hashlib.sha256(output.read_bytes()).hexdigest(),
            "sample_rate": rate, "channels": 2, "frames": len(samples),
            "duration": len(samples) / rate, "gain": gain,
        })
        print(f"{name}: {len(samples) / rate:.2f}s, {output.stat().st_size / 1024:.0f} KiB", flush=True)
    (args.output / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")


if __name__ == "__main__":
    main()
