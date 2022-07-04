''' serial_test.py
    
    to test serial communication
'''

from machine import UART, Pin
import machine
import time

machine.freq(240000000)

MD0 = Pin(2, Pin.OUT)
MD1 = Pin(0, Pin.OUT)
AUX = Pin(15, Pin.IN)

MD0.value(1)
MD1.value(0)

while AUX.value() == 0:
    time.sleep(0.1)
print("Serial module initialized")

uart = UART(2, 9600)    # UART2
uart.init(baudrate=9600, tx=17, rx=16, bits=8, parity=None, stop=1)

while True:
    while not uart.any():
        pass
    data = uart.readline().decode()
    print(data)
    uart.write(data.encode())


