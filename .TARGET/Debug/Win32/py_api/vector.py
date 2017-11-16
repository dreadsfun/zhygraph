class _vector_base(object):
    _tyerr = TypeError("vector operations' arguments must be of same type")

    def _check_type(rhv, lhv):
        if rhv.__class__ != lhv.__class__:
            raise _tyerr
    
    def __add__(self, other):
        _vector_base._check_type(self, other)
        n = self.__class__()
        for c in range(0, len(n.components)):
            n.components[c] = self.components[c] + other.components[c]
        return n

    def __sub__(self, other):
        _vector_base._check_type(self, other)
        n = self.__class__()
        for c in range(0, len(n.components)):
            n.components[c] = self.components[c] - other.components[c]
        return n

    def __mul__(self, other):
        n = self.__class__()
        for c in range(0, len(n.components)):
            n.components[c] *= other
        return n

    def __div__(self, other):
        n = self.__class__()
        for c in range(0, len(n.components)):
            n.components[c] /= other
        return n

class vec2(_vector_base):
    def __init__(self, x=0.0, y=0.0):
        self.components = [x, y]

    @property
    def x(self):
        return self.components[0]

    @x.setter
    def x(self, v):
        self.components[0] = v

    @property
    def y(self):
        return self.components[1]

    @y.setter
    def y(self, v):
        self.components[1] = v

class vec3(vec2):
    def __init__(self, x=0.0, y=0.0, z=0.0):
        self.components = [x, y, z]

    @property
    def z(self):
        return self.components[2]

    @z.setter
    def z(self, v):
        self.components[2] = v

class vec4(vec3):
    def __init__(self, x=0.0, y=0.0, z=0.0, w=0.0):
        self.components = [x, y, z, w]

    @property
    def w(self):
        return self.components[3]

    @w.setter
    def w(self, v):
        self.components[3] = v

