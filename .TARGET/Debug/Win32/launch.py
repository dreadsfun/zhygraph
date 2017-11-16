import sys
import os

pyapi_path = os.path.dirname(os.path.abspath(__file__)) + '\\py_api'
sys.path.append(pyapi_path)

from lib import *
from cppapi_object import *
from logger import *
from scene_node import *
from input import *

launcher = cdll.LoadLibrary('launcher.dll')
launcher.launcher_thread()
