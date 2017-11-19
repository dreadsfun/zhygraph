from vector import vec4

class quat(vec4):
    def __init__(self, x=0.0, y=0.0, z=0.0, w=1.0):
        super(quat, self).__init__(x, y, z, w)
        
