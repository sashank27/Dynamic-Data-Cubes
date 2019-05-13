####################### THIS FILE IMPLEMENTS ALL THE HELPER FUNCTIONS USED IN THIS APP #####################

import os

PATH = '../Data/'

star_files = 20
neighbour_files = 3

class FileObject:

    def __init__(self, filename, filesize):
        self.filename = filename
        self.filesize = filesize

def list_files():

    L = []

    star_data = 'star_'
    neighbour_data = 'neighbour_'

    for i in range(star_files + 1):
        file_name = star_data + str(i) + '.csv'
        file_path = PATH + file_name
        info = os.stat(file_path)
        L.append(FileObject(file_name, info.st_size / 1000000))

    for i in range(1, neighbour_files + 1):
        file_name = neighbour_data + str(i) + '.csv'
        file_path = PATH + file_name
        info = os.stat(file_path)
        L.append(FileObject(file_name, info.st_size / 1000000))

    file_path = PATH + 'DataCubes.cpp'
    file_name = 'DataCubes.cpp'
    info = os.stat(file_path)
    L.append(FileObject(file_name, info.st_size / 1000000))

    file_path = PATH + 'compressed.zip'
    file_name = 'compressed.zip'
    info = os.stat(file_path)
    L.append(FileObject(file_name, info.st_size / 1000000))

    return L

def get_file(filename):
    filepath = PATH + filename
    return open(filepath, 'rb')
