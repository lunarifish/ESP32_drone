''' multithreads_test.py

    RT
    CAN'T STOP!!!!
    src: https://www.bilibili.com/read/cv16282686/
'''

import _thread
from time import sleep

class Thread:
    """创建新线程并循环运行指定函数"""

    def __init__(self, func=lambda: None, sec=-1, *args, **kwargs):
        """
        * func 需要循环运行的函数
        * sec  每次循环的延迟，负数则只运行一次
        * args kwagrs 函数的参数
        * enable 使能运行
        """
        self.sec = sec
        self.func = func
        self.args, self.kwargs = args, kwargs
        self.enable = True
        self.lock = _thread.allocate_lock()
        self.stop_lock = _thread.allocate_lock()
        self.lock.acquire()
        self.stop_lock.acquire()
        _thread.start_new_thread(self.__run, ())

    def __run(self):
        """
        # 请勿调用
        * 线程运行函数
        """
        while True:
            self.lock.acquire()
            try:
                self.func(*self.args, **self.kwargs)
            except Exception as e:
                print('Task_function_error:', e)
            if self.sec < 0 or not self.enable:
                self.stop_lock.release()
            else:
                sleep(self.sec)
                self.lock.release()

    def start(self):
        """运行线程"""
        self.lock.release()

    def stop(self):
        """暂停线程"""
        self.enable = False
        self.stop_lock.acquire()
        self.enable = True
        
        
def task():
    while True:
        print("123")
        sleep(0.2)
    
t = Thread(func=task)
t.start()
sleep(3)
t.stop()
print("stopped")
