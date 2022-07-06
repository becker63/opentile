#!/usr/bin/env python3
import subprocess
import sys

arg = sys.argv[1:]

def check_close(w_id):
    w_data = get(["xprop", "-id", w_id])
    if "_NET_WM_WINDOW_TYPE_NORMAL" in w_data:
        subprocess.call(["wmctrl", "-ic", w])

def get(cmd):
    return subprocess.check_output(cmd).decode("utf-8")

wlist = [l.split() for l in get(["wmctrl", "-lG"]).splitlines()]

arg = arg[0] if arg else [
    l.split()[0] for l in get(["wmctrl", "-d"]).splitlines() if '*' in l
    ][0]

for w in [w[0] for w in wlist if w[1] == arg]:
    check_close(w)
