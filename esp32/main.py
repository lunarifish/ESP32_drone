### WIP ###
### FOR TEST PURPOSE ###

from libs.drone.motor import Motor

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
    else:
        try:
            motor1.set_throttle(float(user_in))
        except ValueError:
            print("Enter a number between 0 and 1")
            continue
