class Star:

    def __init__(self, X, Y, Z):
        self.X = X
        self.Y = Y
        self.Z = Z

    def __hash__(self):
        return hash((self.X, self.Y, self.Z))

    def __eq__(self, other):
        return (self.X, self.Y, self.Z) == (other.X, other.Y, other.Z)

    def __ne__(self, other):
        return not(self == other)

class Cube:

    def __init__(self, X, Y, Z, dim):
        self.X = X
        self.Y = Y
        self.Z = Z
        self.dim = dim

    def __hash__(self):
        return hash((self.X, self.Y, self.Z, self.dim))

    def __eq__(self, other):
        return (self.X, self.Y, self.Z, self.dim) == (other.X, other.Y, other.Z, other.dim)

    def __ne__(self, other):
        return not(self == other)

class StarInfo:

    def __init__(self, T, X, Y, Z):
        self.type = T
        self.IDX = X
        self.IDY = Y
        self.IDZ = Z
