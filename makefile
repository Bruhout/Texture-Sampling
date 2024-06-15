CC = g++

main: src/main.cpp build/vec3d.o build/geometry.o
	$(CC) -o main src/main.cpp build/vec3d.o build/geometry.o -g -std=c++11

build/vec3d.o: src/vec3d.cpp
	$(CC) -o build/vec3d.o src/vec3d.cpp -c -g -std=c++11

build/geometry.o: src/geometry.cpp
	$(CC) -o build/geometry.o src/geometry.cpp -c -g -std=c++11

scanline: scanline.cpp
	g++ -o scanline scanline.cpp -g