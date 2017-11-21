from ctypes import *
from py_api.vector import *

class prvec2(Structure):
    _fields_ = [('x', c_float),
                ('y', c_float)]

    def __init__(self,v2):
        self.x = v2.x
        self.y = v2.y

class prvec3(Structure):
    _fields_ = [('x', c_float),
                ('y', c_float),
                ('z', c_float)]

    def __init__(self,v3):
        self.x = c_float(v3.x)
        self.y = c_float(v3.y)
        self.z = c_float(v3.z)

class prvec4(Structure):
    _fields_ = [('x', c_float),
                ('y', c_float),
                ('z', c_float),
                ('w', c_float)]

    def __init__(self,v4):
        self.x = v4.x
        self.y = v4.y
        self.z = v4.z
        self.w = v4.w

class prmat4x4(Structure):
    _fields_ = [('_1', prvec4),
                ('_2', prvec4),
                ('_3', prvec4),
                ('_4', prvec4)]


