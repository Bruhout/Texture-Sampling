CC = g++
CPP_VERSION = c++11

main: src/main.cpp build/vec3d.o build/geometry.o
	$(CC) -o main src/main.cpp build/vec3d.o build/geometry.o -g -std=$(CPP_VERSION)

lerp: src/lerp.cpp build/vec3d.o build/geometry.o
	$(CC) -o lerp src/lerp.cpp build/vec3d.o build/geometry.o -g -std=$(CPP_VERSION)

build/vec3d.o: src/vec3d.cpp
	$(CC) -o build/vec3d.o src/vec3d.cpp -c -g -std=$(CPP_VERSION)

build/geometry.o: src/geometry.cpp
	$(CC) -o build/geometry.o src/geometry.cpp -c -g -std=$(CPP_VERSION)

