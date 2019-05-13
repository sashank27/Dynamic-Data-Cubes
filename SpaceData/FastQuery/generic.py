from SpaceData.wsgi import star_info, cube_info, neighbour_info
from FastQuery.datatype import Star, Cube, StarInfo

dimensions = [-1, 256, 1024, 4096]

def get_cube_id(X, Y, Z):
    for i in range(1, 4):
        new_x = int(X / dimensions[i])
        new_y = int(Y / dimensions[i])
        new_z = int(Z / dimensions[i])
        new_x = new_x * dimensions[i]
        new_y = new_y * dimensions[i]
        new_z = new_z * dimensions[i]
        cube = Cube(new_x, new_y, new_z, dimensions[i])
        if cube in neighbour_info:
            return cube

    return Cube(-1, -1, -1, -1)
