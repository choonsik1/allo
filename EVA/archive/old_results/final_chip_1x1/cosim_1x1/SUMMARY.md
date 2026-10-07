# 1x1 rtprime cosim results — consolidated (2026-07-24)
RTL verdict = the PASS/FAIL line AFTER 'Starting C post checking' (the first one is the all-zero C-sim artifact).

build                                      II         dep-false RTL verdict
-----                                      --         --------- -----------
II=1 dep-false FP_LAT=1                    1          yes(4)    FAIL (out_s=0x0000)
II=1 dep-false FP_LAT=3                    1          yes(4)    FAIL (out_s=0x0000)
II=1 resq/cmpq-only dep-false              1          yes(2)    FAIL
II=2 no-dep-false FP_LAT=1                 2          no        PASS (0 mismatch)  <-- best correct scheduled
II=2 no-dep-false FP_LAT=3                 2          no        PASS (0 mismatch)  belt-and-suspenders
NOSCHED rtprime (prime sweep)              hi         n/a       PASS
FIFO scheduled II=1 (reverted)             1          yes       FAIL
FIFO NOSCHED (reverted)                    hi         n/a       PASS (chip sound)

## raw logs (persistent):
  sched_logs/run.log run_fp3.log (II=1 dep-false); cosim_1x1/ii2_fp3_cosim.log (II=2 fp3)
  P&R: final_chip_1x1/ii2/ (II=2 fp1), final_chip_1x1/fp3/ (II=1 dep-false fp3)
