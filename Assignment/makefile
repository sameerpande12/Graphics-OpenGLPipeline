OS := $(shell uname)
CFLAGS = -lglut -lglfw -Wall -lGL -ldl -lGLEW -fopenmp -O3  

exe: main.o 
	g++ main.o gwindowGLFW.o gWindow.o $(CFLAGS) -o exe

main.o: main.cpp gwindowGLFW.o 
	g++  $(CFLAGS) -c main.cpp 

gwindowGLFW.o: gwindowGLFW.cpp gwindowGLFW.h gWindow.o glConstants.h
	g++  $(CFLAGS) -c gwindowGLFW.cpp 

gWindow.o: gWindow.cpp gWindow.h glConstants.h
	g++ $(CFLAGS) -c gWindow.cpp

clean:
	rm *.o exe *.gch