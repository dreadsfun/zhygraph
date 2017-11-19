from lib import *

class cppapi_object(object):
    def _set_handle(self, handle):
        self._handle = handle

    def get_handle(self):
        return self._handle
