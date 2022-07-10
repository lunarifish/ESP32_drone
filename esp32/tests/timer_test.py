''' timer_test.py

    _thread module can't run very well so here's an alternative solution
    using HW timer to execute multiple functions at the same time
'''

import machine
import time


def f1(timer):
    print(1)
    
timer0 = machine.Timer(0)
timer0.init(period=1000, mode=machine.Timer.PERIODIC, callback=f1)

time.sleep(3)
timer0.deinit()