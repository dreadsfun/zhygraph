from ctypes import *
from vector import *

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
        self.x = v3.x
        self.y = v3.y
        self.z = v3.z

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


