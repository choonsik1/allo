# from_verification — the Vitis-verified EVA chips, ported to this flow

**Byte-identical copies** (verified with `cmp`) of
`/work/shared/users/zsm9/verification/{fp16,int16}_{elastic,skid}/eva_*.py`:
`eva_fp16_elastic.py` · `eva_fp16_skid.py` · `eva_int16_elastic.py` · `eva_int16_skid.py`

**Local experiment (NOT a copy):** `eva_fp16_elastic_bud.py` = fp16_elastic with the
`6*LANELEN` budget floor made settable via the `BUDMUL` env var, to test whether that floor
is necessary. It is: at 4x4/LANELEN=132, 660 iters PASS but 594/554/528 FAIL, and
break-even vs v16 is 533 — so no early exit can make elastic win. See the top-level README.

Driver: `scripts/run_elastic_systemc.py` (`CHIP=eva_fp16_elastic MMM_MESH=4 LANE_MARGIN=50`).
Not matched by the drivers' `v[0-9]*` glob — the driver adds this dir to `sys.path` itself.

Only **fp16_elastic** was exercised end-to-end (csyn + csim 1x1..8x8 + cosim 2x2/4x4).
`fp16_skid` was synthesized once (area 113,585 = +81 % vs v16 — not a candidate).
The int16 chips were never run: per the source FINDINGS they fail correctness by design
against fp16 vectors, and throughput is their only valid metric.
