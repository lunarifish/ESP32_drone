''' serial_module.py

    packed class for A39C-T400A30D1A 433M serial module
'''

from machine import UART, Pin
import machine
import time

class SerialModule:
    def __init__(self, uart_id, baudrate, MD0, MD1, AUX):
        self.MD0 = MD0 if type(MD0) is Pin else Pin(MD0, Pin.OUT)
        self.MD1 = MD1 if type(MD1) is Pin else Pin(MD1, Pin.OUT)
        self.AUX = AUX if type(AUX) is Pin else Pin(AUX, Pin.IN)
        
        # MD0=1 MD1=0 stands for normal mode/quit configure mode
        self.MD0.value(1)
        self.MD1.value(0)
        
        while self.AUX.value() == 0:
            time.sleep(0.1)
        print("Serial module initialized")
        
        self.uart = UART(uart_id, baudrate)
        self.uart.init(baudrate, bits=8, parity=None, stop=1)
    def write(self, message):
        self.uart.write((message + "n").encode())
    def readline(self):
        while not self.uart.any():
            time.sleep_ms(100)
        return self.uart.readline().decode()[:-1]
