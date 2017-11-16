from ctypes import *
from vector_proxy import *
import os

os.environ['PATH'] = os.path.dirname(__file__) + '\\..' + ';' + os.environ['PATH']

lib = cdll.LoadLibrary('cAPI.dll')

# input class' restypes
lib.input_get_key_down.restype = c_bool
lib.input_get_key_up.restype = c_bool
lib.input_get_key.restype = c_bool
lib.input_get_button_down.restype = c_bool
lib.input_get_button_up.restype = c_bool
lib.input_get_button.restype = c_bool
lib.input_get_cursor_position.restype = prvec2
lib.input_get_cursor_displacement.restype = prvec2

# transform class' restypes
lib.transform_get_local_position.restype = prvec3
lib.transform_get_local_rotation.restype = prvec4
lib.transform_get_local_scale.restype = prvec3
lib.transform_get_world_matrix.restype = prmat4x4
lib.transform_get_local_matrix.restype = prmat4x4
lib.transform_get_position.restype = prvec3
lib.transform_get_rotation.restype = prvec4
lib.transform_get_scale.restype = prvec3
lib.transform_get_local_euler_angles.restype = prvec3
lib.transform_has_changed.restype = c_bool
lib.transform_inverse_transform_position.restype = prvec3
lib.transform_inverse_transform_direction.restype = prvec3
lib.transform_transform_position.restype = prvec3
lib.transform_transform_direction.restype = prvec3
lib.transform_get_up.restype = prvec3

# scene_node class' restypes
lib.scene_node_get_class_string.restype = c_char_p
lib.scene_node_find.restype = c_longlong
lib.scene_node_get_name.restype = c_char_p
lib.scene_node_get_parent.restype = c_longlong
lib.scene_node_get_root.restype = c_longlong
lib.scene_node_is_root.restype = c_bool

# mesh_renderer_node class' restypes
lib.mesh_renderer_node_get_mesh.restype = c_char_p

# mesh_renderer_node class' argtypes
lib.mesh_renderer_node_set_mesh.argtypes = [c_longlong, c_char_p, c_bool]
