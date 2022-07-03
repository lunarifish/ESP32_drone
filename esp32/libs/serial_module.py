''' serial_module.py
    
    packed driver for serial communication
'''

from machine import UART
import machine
import time

class SerialModule:
    def __init__(self, uart_id, baudrate):
        self.uart = UART(uart_id, baudrate)
        
        self.uart.init(baudrate, bits=8, parity=None, stop=1)
    def write(message):
        self.uart.write((message + "n").encode())
    def readline():
        while not self.uart.any():
            time.sleep_ms(100)
        return self.uart.readline().decode()[:-1]


if __name__ == "__main__":
    ser = SerialModule(2, 9600)