#-*- encoding: utf-8 -*-

import sys, os, time
from threading import Condition, Lock, Thread

VAL = 0
COND = Condition()
DONE = False

def Producer():
    global VAL, DONE
    cnt = 0
    while cnt<100:
        COND.acquire()
        cnt += 1
        VAL += 1
        COND.notify()
        COND.release()
    else:
        DONE = True
        print "Producer Done"

def Consumer(id):
    global VAL
    p = 0
    while True:
        COND.acquire()
        while VAL<1:
            COND.wait()
        print "thread%d %d"%(id, VAL)
        VAL -= 1
        COND.release()
        p += 1
        time.sleep(0.5)
        '''if DONE:
            print "consumer done: ", p
            break
        '''

print "PID : ", os.getpid()

Thread(target=Producer).start()
Thread(target=Consumer, args=(1,)).start()
Thread(target=Consumer, args=(2,)).start()
