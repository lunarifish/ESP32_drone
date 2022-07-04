''' motor.py

    Brushless motor/ESC Driver
'''

from machine import PWM, Pin

class Motor:
    def __init__(self, num, pin):
        self.num = num
        self.pwm_duty = 0
        self.throttle = 0
        self.is_armed = False
        
        if type(pin) is int:
            self.pwm = PWM(Pin(pin), Pin.OUT)
        elif type(pin) is Pin:
            self.pwm = PWM(pin)
        self.pwm.freq(50)
        
    def _set_PWM_duty(self, duty):
        self.pwm.duty(duty)
        self.pwm_duty = duty
        
    def set_throttle(self, throttle):
        if not self.is_armed:
            print(f"Motor{self.num} is not armed")
            return None
        if throttle < 0 or throttle > 1:
            raise ValueError("Throttle value not in 0~1")
        
        raw_throttle = int(throttle * (655 - 600) + 600)
        self._set_PWM_duty(raw_throttle)
        print(f"Motor{self.num}: {throttle * 100}%(raw pwm duty {self.pwm_duty})")
        
    def arm(self):
        if not self.is_armed:
            self.is_armed = True
            self._set_PWM_duty(600)
            print(f"Motor{self.num} armed")
        else:
            print(f"Motor{self.num} is already armed")
        
    def disarm(self):
        if self.is_armed:
            self.is_armed = False
            self._set_PWM_duty(0)
            print(f"Motor{self.num} disarmed")
        else:
            print(f"Motor{self.num} is already disarmed")
