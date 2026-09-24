#!/usr/bin/env python3
"""Rewrite an elastic chip's full()/empty() guards as try_put/try_get (PushNB/PopNB).

    python3 scripts/convert_guards_to_nb.py <in.py> <out.py>

WHY: the guards are the only reason the emitter instantiates AlloFifoC (see
streamValueQueried() in EmitSystemC.cpp) -- the occupancy sideband exists solely to
answer empty()/full(). With try_* the attempt returns its own success, so every stream
drops to a plain Connections::Fifo and the sideband (ports + signals + status process)
disappears entirely.

Data-driven firing is PRESERVED: the outer work-gating condition (`if oh_v==1`,
`if ig_v==0`, `if hold_cnt<2`) is untouched. Only the channel-readiness QUERY is
replaced by the attempt's return value.

PRECONDITION -- CHECK BEFORE TRUSTING THE OUTPUT: at most one NB site per port per
region. v16 failed to schedule (SCHD-30) with six NB sites driving one port
(`vld.write#6`); the guarded elastic source is one-site-per-port, so a mechanical
conversion is safe. Verify with the counter this script prints.
"""
import re, sys

CH = r"([A-Za-z_]\w*\[[^\]]*\])"

def convert(s):
    c = [0]; n = {"put": 0, "get": 0}
    def nxt():
        c[0] += 1; return c[0]
    # producer: `if COND and CH.full() == 0:\n  CH.put(X); TAIL`
    def p_inline(m):
        ind, cond, ch, i2, ch2, arg, tail = m.groups()
        if ch != ch2: return m.group(0)
        t = nxt(); n["put"] += 1
        return (f"{ind}if {cond}:\n{i2}_ok{t} = {ch2}.try_put({arg})\n"
                f"{i2}if _ok{t} == 1: {tail}\n")
    s = re.sub(rf"( *)if (.+?) and {CH}\.full\(\) == 0:\n( *){CH}\.put\((.+?)\); (.+?)\n", p_inline, s)
    # producer, driver form: `elif CH.full() == 0:\n  CH.put(X)\n  STMT`
    def p_elif(m):
        ind, ch, i2, ch2, arg, i3, stmt = m.groups()
        if ch != ch2: return m.group(0)
        t = nxt(); n["put"] += 1
        return (f"{ind}else:\n{i2}_ok{t} = {ch2}.try_put({arg})\n"
                f"{i2}if _ok{t} == 1:\n{i2}    {stmt}\n")
    s = re.sub(rf"( *)elif {CH}\.full\(\) == 0:\n( *){CH}\.put\((.+?)\)\n( *)(.+?)\n", p_elif, s)
    def p_elif2(m):
        ind, ch, i2, ch2, arg, tail = m.groups()
        if ch != ch2: return m.group(0)
        t = nxt(); n["put"] += 1
        return (f"{ind}else:\n{i2}_ok{t} = {ch2}.try_put({arg})\n"
                f"{i2}if _ok{t} == 1: {tail}\n")
    s = re.sub(rf"( *)elif {CH}\.full\(\) == 0:\n( *){CH}\.put\((.+?)\); (.+?)\n", p_elif2, s)
    # consumer, inline: `if COND and CH.empty() == 0:\n  DST = CH.get(); TAIL`
    def g_inline(m):
        ind, cond, ch, i2, dst, ch2, tail = m.groups()
        if ch != ch2: return m.group(0)
        t = nxt(); n["get"] += 1
        return (f"{ind}if {cond}:\n{i2}_g{t}, _k{t} = {ch2}.try_get()\n"
                f"{i2}if _k{t} == 1: {dst} = _g{t}; {tail}\n")
    s = re.sub(rf"( *)if (.+?) and {CH}\.empty\(\) == 0:\n( *)(\S+?) = {CH}\.get\(\); (.+?)\n", g_inline, s)
    # producer, BLOCK-AWARE. int16 wraps the put in `with allo.meta_if/meta_else`
    # blocks (compile-time select), so the put is not on the guard's next line.
    # Convert EVERY put in the block to try_put assigning the SAME _ok, then gate the
    # trailing statement(s) on it. meta_if/meta_else are mutually exclusive at compile
    # time, so only one assignment survives -- this stays one NB site per port.
    lines = s.split("\n"); out_l = []; i = 0
    pat_p = re.compile(rf"( *)if (.+?) and {CH}\.full\(\) == 0: *$")
    while i < len(lines):
        m = pat_p.match(lines[i])
        if m:
            ind, cond, ch = m.group(1), m.group(2), m.group(3)
            body, j = [], i + 1
            while j < len(lines) and (not lines[j].strip() or
                    len(lines[j]) - len(lines[j].lstrip()) > len(ind)):
                body.append(lines[j]); j += 1
            while body and not body[-1].strip(): body.pop()
            if any(f"{ch}.put(" in b for b in body):
                t = nxt(); n["put"] += 1
                newb, tail = [], []
                for b in body:
                    if f"{ch}.put(" in b:
                        bi = b[:len(b) - len(b.lstrip())]
                        arg = b.strip()[len(ch) + 5:-1]
                        newb.append(f"{bi}_ok{t} = {ch}.try_put({arg})")
                    elif b.strip().startswith("with "):
                        newb.append(b)
                    elif newb and not tail and b.strip():
                        tail.append(b)          # trailing stmts after the put block
                    else:
                        newb.append(b)
                out_l.append(f"{ind}if {cond}:")
                out_l += newb
                if tail:
                    out_l.append(f"{ind}    if _ok{t} == 1:")
                    out_l += ["    " + b for b in tail]
                i = j; continue
        out_l.append(lines[i]); i += 1
    s = "\n".join(out_l)

    # consumer, annotated + BLOCK-AWARE. The body after `NM: T = CH.get()` can be
    # several lines (int16 uses `with allo.meta_if(...)` blocks), so a regex that
    # captures one line truncates it and corrupts the indentation. Walk lines instead:
    # take everything more-indented than the guard, and re-indent it under `if _k == 1:`.
    lines = s.split("\n"); out_l = []; i = 0
    # the guard may or may not carry a work-gating prefix (`if COND and ch.empty()...`
    # in the node, bare `if ch.empty()...` in the collectors)
    pat_g = re.compile(rf"( *)if (?:(.+?) and )?{CH}\.empty\(\) == 0: *$")
    pat_a = re.compile(r"( *)(\w+): (\w+) = " + CH + r"\.get\(\) *$")
    while i < len(lines):
        m = pat_g.match(lines[i])
        a = pat_a.match(lines[i+1]) if m and i+1 < len(lines) else None
        if m and a and m.group(3) == a.group(4):
            ind, cond, ch = m.group(1), m.group(2), m.group(3)
            i2, nm, ty = a.group(1), a.group(2), a.group(3)
            t = nxt(); n["get"] += 1
            body, j = [], i + 2
            while j < len(lines) and (not lines[j].strip() or
                                      len(lines[j]) - len(lines[j].lstrip()) >= len(i2)):
                body.append(lines[j]); j += 1
            while body and not body[-1].strip(): body.pop()
            if cond:                     # work-gated: keep the outer condition
                out_l += [f"{ind}if {cond}:",
                          f"{i2}_g{t}, _k{t} = {ch}.try_get()",
                          f"{i2}if _k{t} == 1:",
                          f"{i2}    {nm}: {ty} = _g{t}"]
                out_l += ["    " + b if b.strip() else b for b in body]
            else:                            # bare collector poll: no outer if needed
                out_l += [f"{ind}_g{t}, _k{t} = {ch}.try_get()",
                          f"{ind}if _k{t} == 1:",
                          f"{i2}{nm}: {ty} = _g{t}"]
                out_l += body
            i = j
        else:
            out_l.append(lines[i]); i += 1
    s = "\n".join(out_l)
    return s, n

if __name__ == "__main__":
    src, dst = sys.argv[1], sys.argv[2]
    s = open(src).read()
    out, n = convert(s)
    left = len(re.findall(r"\.(full|empty)\(\)", out))
    open(dst, "w").write(out)
    import ast; ast.parse(out)                      # syntax gate
    print(f"  converted : {n['put']} put-guards, {n['get']} get-guards")
    print(f"  remaining full()/empty() : {left}   {'OK' if left == 0 else '*** NOT ZERO -- sideband will persist ***'}")
    # PRECONDITION: at most ONE NB site per port PER REGION (a def ... block).
    # Counting by channel name across the whole file is wrong -- a name legitimately
    # appears once per region and once per array index. v16's SCHD-30 came from
    # multiple sites inside ONE region driving one port (`vld.write#6`).
    import collections
    regions = re.split(r"\n(?= *def \w+\()", out)
    worst = {}
    for r in regions:
        m = re.match(r"\s*def (\w+)", r)
        if not m: continue
        h = collections.Counter(re.findall(r"([A-Za-z_]\w*\[[^\]]*\])\.try_(?:put|get)\(", r))
        for port, k in h.items():
            if k > 1: worst[f"{m.group(1)}:{port}"] = k
    if worst:
        print(f"  *** MULTI-DRIVE within a region: {worst} -- will hit SCHD-30 ***")
    else:
        print("  precondition OK : <=1 NB site per port per region")
