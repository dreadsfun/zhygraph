from cppapi_object import *
from transform import *
import sys

class scene_node(cppapi_object):
    def __init__(self, name = 'default_name'):
        # internal create node with name
        pass

    @classmethod
    def find(cls, name):
        n = cls()
        n._set_handle(lib.scene_node_find(name.encode()))
        return n

    @property
    def transform(self):
        t = transform()
        t._set_handle(lib.scene_node_get_transform(self._handle))
        return t

    @property
    def name(self):
        return lib.scene_node_get_name(self._handle).decode()

    @name.setter
    def name(self,name):
        lib.scene_node_set_name(self._handle, name.encode())

    @property
    def parent(self):
        h = lib.scene_node_get_parent(self._handle)
        cl = getattr(sys.modules[__name__], lib.scene_node_get_class_string(h).decode())
        p = cl()
        p._set_handle(h)
        return p

    @parent.setter
    def parent(self, parent):
        lib.scene_node_set_parent(self._handle, parent._handle)

    def get_children(self):
        pass

    def get_root(self):
        h = lib.scene_node_get_root(self._handle)
        cl = getattr(sys.modules[__name__],lib.scene_node_get_class_string(h).decode())
        p = cl()
        p._set_handle(h)
        return p

    def add_child(self, child):
        lib.scene_node_add_child(self._handle, child._handle)

    def remove_child(self, child):
        lib.scene_node_remove_child(selr._handle, child._handle)

    def traverse_depth(self, visit):
        lib.scene_node_traverse_depth(self._handle, visit._handle)

    def traverse_breadth(self, visit):
        lib.scene_node_traverse_breadth(self._handle, visit._handle)

    def is_root(self):
        return lib.scene_node_is_root(self._handle)

class mesh_renderer_node(scene_node):
    def __init__(self, name = 'default_name'):
        super(mesh_renderer_node, self).__init__(name)

    @property
    def mesh(self):
        return lib.mesh_renderer_node_get_mesh(self._handle).decode()

    @mesh.setter
    def mesh(self, mesh):
        self.set_mesh(mesh, False)

    def set_mesh(self, mesh, async = False):
        lib.mesh_renderer_node_set_mesh(self._handle, mesh.encode(), async)
