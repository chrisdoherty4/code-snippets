from __future__ import print_function
import subprocess
import os, sys
import time
import signal

print("{}: PPID={}".format(sys.argv[0], os.getppid()))
print("{}: PID={}".format(sys.argv[0], os.getpid()))

signal.signal(15, lambda s, t: print("Signal received {}".format(s)))

sleep_time = 60

print("Sleeping for {}".format(sleep_time))

time.sleep(sleep_time)

print("Finished sleep")
