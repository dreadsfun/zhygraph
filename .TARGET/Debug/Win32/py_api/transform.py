from cppapi_object import *
from vector import *
from enum import Enum

class coordinate_space(Enum):
    world = 0
    local = 1

class transform(cppapi_object):
    @property
    def local_position(self):
        pr = lib.transform_get_local_position(self._handle)
        r = vec3(pr.x, pr.y, pr.z)
        return r

    @local_position.setter
    def local_position(self, pos):
        lib.transform_set_local_position(self._handle, prvec3(pos))

    @property
    def local_rotation(self):
        pr = lib.transform_get_local_rotation(self._handle)
        r = quat(pr.x, pr.y, pr.z, pr.w)
        return r

    @local_rotation.setter
    def local_rotation(self, rot):
        lib.transform_set_local_rotation(self._handle, prvec4(rot))

    @property
    def local_scale(self):
        pr = lib.transform_get_local_scale(self._handle)
        r = vec3(pr.x, pr.y, pr.z)
        return r

    @local_scale.setter
    def local_scale(self, scl):
        lib.transform_set_local_scale(self._handle, prvec3(scl))

    @property
    def get_world_matrix(self):
        pass

    @property
    def get_local_matrix(self):
        pass

    @property
    def get_position(self):
        pass

    def set_position(self, pos):
        pass

    @property
    def get_rotation(self):
        pass

    def set_rotation(self, rot):
        pass

    @property
    def get_scale(self):
        pass

    def set_scale(self, scl):
        pass

    @property
    def get_local_euler_angles(self):
        pass

    def set_local_euler_angles(self, eul):
        pass

    #def from_euler(eul):

    @property
    def has_changed(self):
        return lib.transform_has_changed(self._handle)

    def translate(self, dirc, space = coordinate_space.world):
        lib.transform_translate( self._handle, prvec3(dirc), space.value)

    def rotate_around(self, cent, axis, angle, look = False):
        lib.transform_rotate_around(self._handle, prvec3(cent),
                                    prvec3(axis), angle, look)

    def rotate(self, eul, space):
        e = prvec3(eul.x, eul.y, eul.z)

    def look_at(self, at, up):
        pass

    def inverse_transform_position(self, pos):
        pass

    def inverse_transform_direction(self, dirc):
        pass

    def transform_position(self, pos):
        pass

    def transform_direction(self, dirc):
        pass

    def set_up(self, up):
        pass

    @property
    def get_up(self):
        pass
