class Vec2:
    def __init__(self, x : float = 0, y : float = 0):
        self.x = x
        self.y = y

    def getX(self):
        return self.x

    def getY(self):
        return self.y

    def setX(self, x):
        self.x = x

    def setY(self, y):
        self.y = y

    def __add__(self, v):
        return Vec2(self.x + v.x, self.y + v.x)

    def __radd__(self, v):
        return Vec2(self.x + v.x, self.y + v.x)

    def __sub__(self, v):
        return Vec2(self.x - v.x, self.y - v.y)

    def __rsub__(self, v):
        return Vec2(self.x - v.x, self.y - v.y)

    def __mul__(self, a):
        return Vec2(self.x * a, self.y * a)

    def __rmul__(self, a):
        return Vec2(self.x * a, self.y * a)

    def __str__(self):
        return "({},{})".format(self.x, self.y)

    def __eq__(self, v):
        return (self.x == v.x and self.y == v.y)
    
    def __truediv__(self, a):
        return Vec2(self.x, self.y) * (1/a)

    def __rtruediv__(self, a):
        return Vec2(self.x, self.y) * (1/a)

    def norm(self):
        return self.x ** 2 + self.y ** 2

    def dot(self, v):
        return self.x * v.x + self.y * v.y
