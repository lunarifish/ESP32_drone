''' joystick_test.py

    to test joystick(a xbox controller)
'''


from drone.libs.serial_module import SerialModule
from drone.libs.motor import Motor


motor = Motor(1, 18)

MD0 = 2
MD1 = 0
AUX = 15
ser = SerialModule(2, 9600, MD0, MD1, AUX)

while True:
    try:
        msg = ser.readline()
    except UnicodeError:
        continue
    
    if msg == "a":
        motor.arm()
    if msg == "b":
        motor.disarm()
    else:
        try:
            motor.set_throttle(int(msg) / 100)
        except ValueError:
            pass