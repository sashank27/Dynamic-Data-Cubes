from SpaceData.wsgi import star_info, cube_info, neighbour_info
from FastQuery.datatype import Star, Cube, StarInfo
from FastQuery import generic
import math

def keyfunction(star):
    return star.distance

def count(cube):
    D = {}
    ans1 = 0
    ans2 = 0
    neighbours = neighbour_info.get(cube)
    for C in neighbours:
        try:
            if C not in D:
                D[C] = 1
                cube_count = len(cube_info[C])
                ans2 = ans2 + cube_count
        except:
            continue

    if cube not in D:
        ans1 = len(cube_info[cube])

    return ans1, ans2

def list_stars(cube, X, Y, Z):
    D = {}
    L = []
    ans1 = 0
    ans2 = 0
    neighbours = neighbour_info.get(cube)
    for C in neighbours:
        try:
            if C not in D:
                D[C] = 1
                info = cube_info[C]
                for star in info:
                    ans2 += 1
                    star.location = 'Neighbour'
                    A = star.X
                    B = star.Y
                    C = star.Z
                    dist = ((X - A) * (X - A)) + ((Y - B) * (Y - B)) + ((Z - C) * (Z - C))
                    star.distance = math.sqrt(dist)
                    L.append(star)
        except:
            continue

    if cube not in D:
        info = cube_info[cube]
        for star in info:
            ans1 += 1
            star.location = 'Self'
            A = star.X
            B = star.Y
            C = star.Z
            dist = ((X - A) * (X - A)) + ((Y - B) * (Y - B)) + ((Z - C) * (Z - C))
            star.distance = math.sqrt(dist)
            L.append(star)

    L = sorted(L, key = keyfunction)

    return ans1, ans2, L
