from py_api.scene_node import camera_node
from py_api.input import input, keys, buttons
from py_api.transform import transform, coordinate_space
from py_api.vector import vec3

maincamera = camera_node.find('camera')

def update():
   if input.get_key(keys.w):
      maincamera.transform.translate(vec3(0.02, 0.0, 0.0))
     
   if input.get_key(keys.s):
      maincamera.transform.translate(vec3(-0.02, 0.0, 0.0))
      
   if input.get_key(keys.a) or input.get_key(keys.left):
      maincamera.transform.rotate(vec3(0.0, 0.0, -0.02), coordinate_space.local)
      
   if input.get_key(keys.d) or input.get_key(keys.right):
      maincamera.transform.rotate(vec3(0.0, 0.0, 0.02), coordinate_space.local)
      
   if input.get_key(keys.up):
      maincamera.transform.translate(vec3(0.0, 0.0, -0.02))
      
   if input.get_key(keys.down):
      maincamera.transform.translate(vec3(0.0,0.0,0.02))