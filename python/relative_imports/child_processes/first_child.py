import subprocess
import os, sys, signal

os.setpgrp()
signal.signal(signal.SIGTERM, lambda s, t: os.killpg(0, signal.SIGTERM))

print("{}: PPID={}".format(sys.argv[0], os.getppid()))
print("{}: PID={}".format(sys.argv[0], os.getpid()))

subprocess.call(['python', './second_child.py'])
