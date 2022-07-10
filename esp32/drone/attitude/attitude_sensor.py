''' attitude_sensor.py

    packed class to run an attitude sensor asyncly
'''

import drone.libs.mpu6050 as mpu6050
from drone.attitude.attitude_algorithm import KalmanFilter, KalmanFilter3D
from machine import Timer


class AttitudeSensor:
    def __init__(self, scl, sda):
        self.mpu = mpu6050.MPU6050(sclIO=scl, sdaIO=sda)
        self.euler_angles = (0, 0, 0)
        self.attitude_solver = KalmanFilter3D(KalmanFilter(), KalmanFilter(), KalmanFilter())
        self.timer = Timer(0)
        
    def update(self, timer_arg):
        self.euler_angles = self.attitude_solver.calc(self.euler_angles, self.mpu.GetGyro(), self.mpu.GetAccel())
        
    def start(self):
        self.timer.init(period=50, mode=Timer.PERIODIC, callback=self.update)
        
    def stop(self):
        self.timer.deinit()