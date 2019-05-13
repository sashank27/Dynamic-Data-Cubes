# Dynamic-Data-Cubes

Dynamic Data Cubes is a hybrid data structure capable of storing Gaia Tycho data. You can read more about Gaia Tycho data here - https://en.wikipedia.org/wiki/Tycho-2_Catalogue. Gaia archive is available for download here - https://gea.esac.esa.int/archive/

# Data Cleaning

The raw data available at Gaia Archive was processed to obtain 3 dmensional coordinates of every star (using galactic latitude, longitude and parallax), with the Sun as centre (Galactic Coordinate System). The folder `dataset` contains the processed files. For every star, we have stored the parameters HIP, Tycho2_ID, X_Coordinate, Y_Coordinate and Z_Coordinate in the processed files. You may read more about the parameters here - https://gaia.esac.esa.int/documentation/GDR1/datamodel

# Data Structure

It is observed from the 3D coordinates, that about 50% of stars are nearer to the Sun, within 2000 light year radius. About 90% of the total stars are within 8000 light year radius and the rest are scattered. Using uniform cubes would result is varying star density per cube, hence this gives the motivation to design a large matrix with cubes inside, but not of uniform sides. The matrix is of size 65536 * 65536 * 65536 (all units in light years) with the sun as centre. There are 3 types of cubes that constitute the entire matrix.
Type 1 - Cube side - 256 light years - present uptill 2048 light years from the centre on all sides. 
Type 2 - Cube side - 1024 light years - present uptill 8192 light years from the centre on all sides.
Type 3 - Cube side - 4096 light years - present uptill 32768 light years from the centre on all sides.

The average density of stars in a cube (stars / cube) comes down to a little over 100 with this design. The highest number of stars present in any cube is a little over 10000. 

The data structure can be visualized as a graph with cubes being its nodes. As a result, there are edges from a cube to its neighbours. We store, for every cube, its neighbours (may be greater than 26 too due to non uniform cubes). The implementation can be found in the C++ file - `DataCube.cpp`. Running this file outputs the datastructure in a file. star_0.csv, star_1.csv, ....., star_20.csv contain star information - their location (3 dimensional coordinates) and the information about which cube they belong to (We recognize each cube by its bottom-leftmost point).

# Queries

We support 2 types of queries currently. 

Query Type 1: Given any point in space in 3 dimensional form, the data structure is capable of determining efficiently the stars (and the star count) present in the corresponding cube and the neighbouring cubes. 

Query Type 2: Given any point in space in 3 dimensional form, the data structure is capable of determining efficiently the stars that lie within a radius 'k' from the queried point.

The naive method of traversing the entire dataset takes about 1.5 seconds on a average, whereas the Dynamic Data Cubes can answer the same query in less than 0.1 seconds. At worst cases, the times taken by both the methods in the same, but Dynamic Data Cubes return results faster on average cases.

# Screenshots

![scr1](https://github.com/dumbape/Dynamic-Data-Cubes/blob/master/Home.png?raw=true)
![scr2](https://github.com/dumbape/Dynamic-Data-Cubes/blob/master/DATASET.png?raw=true)
![scr3](https://github.com/dumbape/Dynamic-Data-Cubes/blob/master/Q1.png?raw=true)
![scr4](https://github.com/dumbape/Dynamic-Data-Cubes/blob/master/Q2.png?raw=true)



