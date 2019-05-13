import os
from FastQuery.datatype import Star, Cube, StarInfo

PATH = '../Data/'

star_file = 'star_'
neighbour_file = 'neighbour_'

star_details = 20
neighbour_details = 3

dimensions = [-1, 256, 1024, 4096]

########################## INPUT ############################

def star_input():

    star_info = {}
    cube_info = {}

    for i in range(0, star_details + 1):
        filename = PATH + star_file + str(i) + '.csv'
        file = open(filename, 'r')
        lines = file.readlines()
        for line in lines:
            line = line.split('\n')[0].split(',')
            new_star = Star(float(line[0]), float(line[1]), float(line[2]))
            type = int(line[3])
            new_star_info = StarInfo(int(line[3]), float(line[4]), float(line[5]), float(line[6]))
            star_info[new_star] = new_star_info

            cube = Cube(float(line[4]), float(line[5]), float(line[6]), dimensions[type])
            if cube not in cube_info:
                cube_info[cube] = []

            cube_info[cube].append(new_star)

    return star_info, cube_info

def neighbour_input():

    neighbour_info = {}

    for i in range(1, neighbour_details + 1):
        filename = PATH + neighbour_file + str(i) + '.csv'
        file = open(filename, 'r')
        lines = file.readlines()
        for line in lines:
            line = line.split('\n')[0].split(',')

            cube1 = Cube(float(line[0]), float(line[1]), float(line[2]), dimensions[int(line[3])])
            cube2 = Cube(float(line[4]), float(line[5]), float(line[6]), dimensions[int(line[7])])

            if cube1 not in neighbour_info:
                neighbour_info[cube1] = []

            neighbour_info[cube1].append(cube2)

    return neighbour_info
