from SpaceData.wsgi import star_info, cube_info, neighbour_info
from FastQuery.datatype import Star, Cube, StarInfo
from FastQuery import generic
from FastQuery.query1 import count
import math

def keyfunction(star):
    return star.distance

def get_neighbours(cube):
    L = []
    if cube in neighbour_info:
        L = neighbour_info[cube]
    return L

def process_cube(cube, X, Y, Z):
    L = []
    if cube in cube_info:
        info = cube_info[cube]
        for star in info:
            A = float(star.X)
            B = float(star.Y)
            C = float(star.Z)
            dist = ((X - A) * (X - A)) + ((Y - B) * (Y - B)) + ((Z - C) * (Z - C))
            dist = math.sqrt(dist)
            
            star.distance = dist
            L.append(star)

    return L

def find_spiral_arm(cube, X, Y, Z):
    previous_cube = None
    new_cube = cube
    arm = []

    L = process_cube(cube, X, Y, Z)
    arm.extend(L)
    
    m, _ = count(cube)
    for C in get_neighbours(cube):
        ans1, _ = count(C)
        if ans1 > m:
            new_cube = C
            m = ans1

    previous_cube = cube
    cube = new_cube

    while True:
        L = process_cube(cube, X, Y, Z)
        arm.extend(L)
    
        m, _ = count(cube)
        for C in get_neighbours(cube):
            ans1, _ = count(C)
            if ans1 > m:
                new_cube = C
                m = ans1

        if new_cube == previous_cube:
            break
        
        previous_cube = cube
        cube = new_cube
    
    # arm = sorted(arm, key = keyfunction)
    return arm