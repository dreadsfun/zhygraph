from py_api.cppapi_object import cppapi_object
from py_api.vector import vec2, vec3, vec4
from py_api.vector_proxy import prvec3
from py_api.lib import capi
from py_api.logger import debug
from enum import Enum
from ctypes import c_int

class coordinate_space(Enum):
    world = 0
    local = 1

class transform(cppapi_object):
    @property
    def local_position(self):
        pr = capi.transform_get_local_position(self._handle)
        r = vec3(pr.x, pr.y, pr.z)
        return r

    @local_position.setter
    def local_position(self, pos):
        capi.transform_set_local_position(self._handle, prvec3(pos))

    @property
    def local_rotation(self):
        pr = capi.transform_get_local_rotation(self._handle)
        r = quat(pr.x, pr.y, pr.z, pr.w)
        return r

    @local_rotation.setter
    def local_rotation(self, rot):
        capi.transform_set_local_rotation(self._handle, prvec4(rot))

    @property
    def local_scale(self):
        pr = capi.transform_get_local_scale(self._handle)
        r = vec3(pr.x, pr.y, pr.z)
        return r

    @local_scale.setter
    def local_scale(self, scl):
        capi.transform_set_local_scale(self._handle, prvec3(scl))

    @property
    def get_world_matrix(self):
        pass

    @property
    def get_local_matrix(self):
        pass

    @property
    def get_position(self):
        return capi.transform_get_position(self._handle)

    def set_position(self, pos):
        capi.transform_set_position(self._handle, prvec3(pos))

    @property
    def get_rotation(self):
        pass

    def set_rotation(self, rot):
        pass

    @property
    def get_scale(self):
        return capi.transform_get_scale(self._handle)

    def set_scale(self, scl):
        capi.transform_set_scale(self._handle, prvec3(scl))

    @property
    def get_local_euler_angles(self):
        return capi.transform_get_local_euler_angles(self._handle)

    def set_local_euler_angles(self, eul):
        capi.transform_set_local_euler_angles(self._handle, prvec3(eul))

    #def from_euler(eul):

    @property
    def has_changed(self):
        return capi.transform_has_changed(self._handle)

    def translate(self, dirc, space = coordinate_space.world):
        capi.transform_translate(self._handle, prvec3(dirc), space.value)

    def rotate_around(self, cent, axis, angle, look = False):
        capi.transform_rotate_around(self._handle, prvec3(cent),
                                    prvec3(axis), angle, look)

    def rotate(self, eul, space = coordinate_space.world):
        capi.transform_rotate(self._handle, prvec3(eul), space.value)

    def look_at(self, at, up):
        capi.transform_look_at(self._handle, self._handle, prvec3(up))

    def inverse_transform_position(self, pos):
        return capi.transform_inverse_transform_position(self._handle, prvec3(pos))

    def inverse_transform_direction(self, dirc):
        return capi.transform_inverse_transform_direction(self._handle, prvec3(dirc))

    def transform_position(self, pos):
        return capi.transform_transform_position(self._handle, prvec3(pos))

    def transform_direction(self, dirc):
        return capi.transform_transform_direction(self._handle, prvec3(dirc))

    def set_up(self, up):
        capi.transform_set_up(self._handle, prvec3(up))

    @property
    def get_up(self):
        return capi.transform_get_up(self._handle)
