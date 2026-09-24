# Vendored from sld-columbia/hl5

Commit `3170ec9bbab5234d0d2c883ed5cb41a177fcb0c6` (2020-02-06), Apache 2.0 —
see LICENSE. Copyright 2017 Columbia University, SLD Group.

**Unmodified.** These are the only four files the port still needs from
upstream; everything else in HL5's `src/` and `tb/` is either ported (and lives
one directory up) or unused.

| file | why |
|---|---|
| `defines.hpp` | `ICACHE_SIZE`, `DCACHE_SIZE` |
| `globals.hpp` | `XLEN`, opcodes, the ISA constants |
| `hl5_datatypes.hpp` | the pipeline payload structs — verified to work with `Connections` as written |
| `colormod.hpp` | terminal colours for `fedec.cpp`'s debug trace |

Re-fetch with:

    git clone --depth 1 https://github.com/sld-columbia/hl5
    cd hl5 && git checkout 3170ec9bbab5234d0d2c883ed5cb41a177fcb0c6
