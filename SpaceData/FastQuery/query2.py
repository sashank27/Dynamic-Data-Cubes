import queue

from SpaceData.wsgi import star_info, cube_info, neighbour_info
from FastQuery.datatype import Star, Cube, StarInfo
from FastQuery import generic
import math

def keyfunction(star):
    return star.distance

def get_neighbours(cube):
    L = []
    if cube in neighbour_info:
        L = neighbour_info[cube]
    return L

def should_be_pushed(cube, X, Y, Z, d):
    D = float(cube.dim) / 2
    A = float(cube.X) + D
    B = float(cube.Y) + D
    C = float(cube.Z) + D
    dist = ((X - A) * (X - A)) + ((Y - B) * (Y - B)) + ((Z - C) * (Z - C))
    dist = math.sqrt(dist)
    if dist > d:
        return 0
    else:
        return 1

def process_cube(cube, X, Y, Z, d):
    L = []
    if cube in cube_info:
        info = cube_info[cube]
        for star in info:
            A = float(star.X)
            B = float(star.Y)
            C = float(star.Z)
            dist = ((X - A) * (X - A)) + ((Y - B) * (Y - B)) + ((Z - C) * (Z - C))
            dist = math.sqrt(dist)
            if dist <= d:
                star.distance = dist
                L.append(star)

    return L

def BFS(cube, X, Y, Z, d):
    visited = {}
    processed = {}
    Q = queue.Queue()

    Q.put(cube)
    visited[cube] = 1

    stars = []

    L = process_cube(cube, X, Y, Z, d)
    processed[cube] = 1
    stars.extend(L)

    while not Q.empty():
        C = Q.get()
        N = get_neighbours(C)
        for P in N:
            if P not in visited:

                if P not in processed:
                    L = process_cube(P, X, Y, Z, d)
                    processed[P] = 1
                    stars.extend(L)

                if should_be_pushed(P, X, Y, Z, d) == 1:
                    Q.put(P)
                    visited[P] = 1

    return stars

def naive(cube, X, Y, Z, d):

    L = []

    for star in star_info:
        A = float(star.X)
        B = float(star.Y)
        C = float(star.Z)
        dist = ((X - A) * (X - A)) + ((Y - B) * (Y - B)) + ((Z - C) * (Z - C))
        dist = math.sqrt(dist)
        if dist <=  d:
            star.distance = dist
            L.append(star)

    return L
