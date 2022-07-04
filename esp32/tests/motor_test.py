''' motor_test.py

    to test motor driver(libs/motor.py)
'''

from drone.libs.motor import Motor
import time

motor1 = Motor(1, 18)

while True:
    user_in = input("throttle:")
    if user_in == "q":
        motor1.disarm()
        break
    elif user_in == "d":
        motor1.disarm()
    elif user_in == "a":
        motor1.arm()
    elif user_in == "":
        continue
    elif user_in == "t":
        for i in range(0, 101):
            motor1.set_throttle(i / 100)
            time.sleep(0.1)
        time.sleep(3)
        motor1.disarm()
    else:
        try:
            motor1.set_throttle(float(user_in))
        except ValueError:
            print("Enter a number between 0 and 1")
            continue
