CC = g++
LFLAGS = -lGL -lX11 -lpthread -lpng

build: src/main.cpp build/vec3d.o
	$(CC) -o main src/main.cpp build/vec3d.o -g $(LFLAGS)

build/vec3d.o: src/vec3d.cpp
	$(CC) -o build/vec3d.o src/vec3d.cpp -c -g

scanline: scanline.cpp
	g++ -o scanline scanline.cpp -g