import serial
import RPi.GPIO as GPIO

class SerialModule:
    def __init__(self, dev: str, baudrate: int, MD0: int, MD1: int, AUX: int):
        GPIO.setmode(GPIO.BCM)
        [GPIO.setup(pin, GPIO.OUT) for pin in [MD0, MD1, AUX]]
        GPIO.output(MD0, 1)
        GPIO.output(MD0, 0)

        self.uart = serial.Serial(dev, baudrate)
        if not self.uart.isOpen():
            print("Serial fail")
        else:
            print("Serial success")
            print(self.uart)

    def write(self, message: str):
        self.uart.write((message + "\n").encode())

    def readline(self):
        return self.uart.readline().decode()