# DRIM4HLS provenance

Sources copied from ic-lab-duth/DRIM4HLS, commit `ad1d23c`, Apache 2.0
(LICENSE beside this file). Only `core/src/` is used -- the `caches/`,
`floating_point/` and `prediction/` variants are not.

Re-fetch:
    git clone https://github.com/ic-lab-duth/DRIM4HLS.git
    git -C DRIM4HLS checkout ad1d23c
    cp DRIM4HLS/core/src/*.h DRIM4HLS/core/src/top.cpp .

Files one level up are these sources with the Allo MMIO hook added; see the
top-level README for exactly what changed.
