from __future__ import print_function
from threading import Thread
import signal, os, sys
from time import sleep

def sigintHandler(signo, _):
    print("signal %d caught"%signo)

def fn():
    print("thr sleeping")
    for i in range(10):
        sleep(1)
    print("thr awakes")

signal.signal(signal.SIGINT, sigintHandler)

ls = []
for i in range(5):
    t = Thread(target=fn)
    ls.append(t)
    t.start()

print("All threads up, pid=%d"%os.getpid())
for i in ls:
    i.join()

while True:
    sleep(20)
