import os
from sys import path

path.append(os.path.dirname(__file__) + '\\py_api')

from lib import *
from cppapi_object import *
from logger import *
from scene_node import *

launcher = cdll.LoadLibrary('launcher.dll')
launcher.launcher_thread()
