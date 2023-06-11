import pygame
import os
import time
from pi.libs.serial_module import SerialModule

os.environ["SDL_VIDEODRIVER"] = "dummy"


ser = SerialModule("/dev/ttyAMA1", 9600)


pygame.init()
pygame.joystick.init()

joystick = pygame.joystick.Joystick(0)

joystick.init()
 
while True:
    try:
        for event in pygame.event.get():
            if event.type == pygame.JOYBUTTONDOWN:
                if joystick.get_button(0):
                    ser.write("a")
                    print("a")
                if joystick.get_button(1):
                    ser.write("b")
                    print("b")
    
            if event.type == pygame.JOYAXISMOTION:
                # for i in range(4):
                #     axis = joystick.get_axis(i)
                #     print(axis)

                axis = joystick.get_axis(1)
                ser.write(str(int(-axis * 100)))
                print(axis)
    except KeyboardInterrupt:
        pygame.quit()
    time.sleep(0.1)
