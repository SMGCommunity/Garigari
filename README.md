Garigari  
=============
[![Discord Badge]][discord]
<!--
Replace with your repository's URL.
-->
[Build Status]: https://github.com/SMGCommunity/Garigari/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/SMGCommunity/Garigari/actions/workflows/build.yml
<!---
Code progress URL:
https://progress.decomp.club/data/[project]/[version]/all/?mode=shield&measure=code
URL encoded then appended to: https://img.shields.io/endpoint?label=Code&url=
-->
[Progress]: https://decomp.dev/SMGCommunity/Garigari.svg?mode=shield&measure=code&label=Code
<!---
DOL progress URL:
https://progress.decomp.club/data/[project]/[version]/dol/?mode=shield&measure=code
URL encoded then appended to: https://img.shields.io/endpoint?label=DOL&url=
-->

[Discord Badge]: https://img.shields.io/discord/727908905392275526?color=%237289DA&logo=discord&logoColor=%23FFFFFF
[discord]: https://discord.gg/ZxEqyYeZbf

A work-in-progress decompilation of Super Mario Galaxy 2.

This repository does **not** contain any game assets or assembly whatsoever. An existing copy of the game is required.

Supported versions:

- `SB4E01`: Rev 0 (USA)

Verified fork progress
======================
![All units and functions](docs/progress/treemap.svg)

This snapshot covers **2,239 units and 51,385 functions**. Rectangle area follows code/data size; unit borders group function rectangles. Green denotes source-linked code, blue exact instruction matches still using original objects, amber partial matches, and slate unreconstructed code. Exact scores do not establish relocation fidelity.

**62,832 / 6,281,816 code bytes (1.00022%)** are source-integrated. The complete mixed-source executable is byte-identical to retail, SHA-1 `7d79810889824edd01c4ff02624713060a69818c`; most code still comes from original objects.

[Full function inventory](docs/progress/functions.html) · [Machine-readable snapshot](docs/progress/snapshot.json) · [Provenance](docs/PROVENANCE.md).
Regenerate the map with `python3 tools/render_progress.py` after refreshing the verified snapshot. This chart represents this fork, not upstream decomp.dev progress.

Dependencies
============

Windows
--------

On Windows, it's **highly recommended** to use native tooling. WSL or msys2 are **not** required.  
When running under WSL, [objdiff](#diffing) is unable to get filesystem notifications for automatic rebuilds.

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
  - Quick install via pip: `pip install ninja`

macOS
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):

  ```sh
  brew install ninja
  ```

- Install [wine-crossover](https://github.com/Gcenx/homebrew-wine):

  ```sh
  brew install --cask --no-quarantine gcenx/wine/wine-crossover
  ```

After OS upgrades, if macOS complains about `Wine Crossover.app` being unverified, you can unquarantine it using:

```sh
sudo xattr -rd com.apple.quarantine '/Applications/Wine Crossover.app'
```

Linux
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).
- For non-x86(_64) platforms: Install wine from your package manager.
  - For x86(_64), [wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Building
========

- Clone the repository:

  ```sh
  git clone https://github.com/SMGCommunity/Garigari.git
  ```

- Copy your game's disc image to `orig/SB4E01`.
  - Supported formats: ISO (GCM), RVZ, WIA, WBFS, CISO, NFS, GCZ, TGC
  - After the initial build, the disc image can be deleted to save space.

- Configure:

  ```sh
  python configure.py
  ```

  To use a version other than `SB4E01` (USA), specify it with `--version`.

- Build:

  ```sh
  ninja
  ```

Diffing
=======

Once the initial build succeeds, an `objdiff.json` should exist in the project root.

Download the latest release from [encounter/objdiff](https://github.com/encounter/objdiff). Under project settings, set `Project directory`. The configuration should be loaded automatically.

Select an object from the left sidebar to begin diffing. Changes to the project will rebuild automatically: changes to source files, headers, `configure.py`, `splits.txt` or `symbols.txt`.

![](assets/objdiff.png)
