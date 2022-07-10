''' attitude_algorithm.py

    attitude solving algorithms
'''

from math import atan

class Filter:
    @staticmethod
    def preCalc(gyro, acc):
        """预先分别计算出加速度计和陀螺仪得到的角度
            等待进一步滤波处理
            gyro: 陀螺仪原始数据
            acc: 加速度计原始数据"""
        try:
            ax = atan(acc[1] / acc[2]) * 57.3;        # 加速度计得到的角度
            gx = gyro[0] / 7510.0                     # 陀螺仪得到的角速度
            ay = atan(acc[0] / acc[2]) * 57.3
            gy = gyro[1] / 7510.0
            az = atan(acc[0] / acc[1]) * 57.3
            gz = gyro[2] / 7510.0
        except ZeroDivisionError:                     # 处理空数据
            return 0, 0, 0, 0, 0, 0
        return ax, gx, ay, gy, az, gz


# 一阶互补滤波
class ComplementaryFilter(Filter):
    def __init__(self):
        self.K = 0.1               # 对加速度计取值的权重
        self.dt = 0.1             # 滤波器采样时间
        
    def calcAxis(self, angle, a, g):
        return self.K * a + (1 - self.K) * (angle + g * self.dt)
    
    def calc(self, angle, gyro, acc):
        """
        angle: 当前欧拉角
        gyro: 陀螺仪原始数据
        acc: 加速度计原始数据
        """
        ax, gx, ay, gy, az, gz = self.preCalc(gyro, acc)
        
        return (self.calcAxis(angle[0], ax, gx),
                self.calcAxis(angle[1], ay, gy),
                self.calcAxis(angle[2], az, gz))


class KalmanFilter(Filter):
    def __init__(self):
        self.dt = 1                                  # sampling interval of the filter
        self.P = [[1, 0], [0, 1]]
        self.Pdot =[0, 0, 0, 0]
        self.Q_angle = 0.001                         # angle data confidence
        self.Q_gyro = 0.005                          # angular velocity data confidence
        self.R_angle = 0.6
        self.C_0 = 0.55
        self.q_bias = 0
        
    def calcAxis(self, angle, a, g):
        angle += (g - self.q_bias) * self.dt
        angle_err = a - angle
        self.Pdot[0] = self.Q_angle - self.P[0][1] - self.P[1][0]
        self.Pdot[1] = -self.P[1][1]
        self.Pdot[2] = -self.P[1][1]
        self.Pdot[3] = self.Q_gyro
        self.P[0][0] += self.Pdot[0] * self.dt
        self.P[0][1] += self.Pdot[1] * self.dt
        self.P[1][0] += self.Pdot[2] * self.dt
        self.P[1][1] += self.Pdot[3] * self.dt
        PCt_0 = self.C_0 * self.P[0][0]
        PCt_1 = self.C_0 * self.P[1][0]
        E = self.R_angle + self.C_0 * PCt_0
        K_0 = PCt_0 / E
        K_1 = PCt_1 / E
        t_0 = PCt_0
        t_1 = self.C_0 * self.P[0][1]
        self.P[0][0] -= K_0 * t_0
        self.P[0][1] -= K_0 * t_1
        self.P[1][0] -= K_1 * t_0
        self.P[1][1] -= K_1 * t_1
        angle += K_0 * angle_err                    # best angle
        self.q_bias += K_1 * angle_err
        angle_dot = g - self.q_bias                 # best angular velocity 
        return angle
        
        
class KalmanFilter3D(Filter):
    def __init__(self, solver_x, solver_y, solver_z):
        self.dt = 1
        self.solver_x = solver_x
        self.solver_y = solver_y
        self.solver_z = solver_z
    def calc(self, angle, gyro, acc):
        """
        angle: 当前欧拉角
        gyro: 陀螺仪原始数据
        acc: 加速度计原始数据
        """
        ax, gx, ay, gy, az, gz = self.preCalc(gyro, acc)
        
        return (self.solver_x.calcAxis(angle[0], ax, gx),
                self.solver_y.calcAxis(angle[1], ay, gy),
                self.solver_z.calcAxis(angle[2], az, gz))