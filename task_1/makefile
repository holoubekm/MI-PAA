CF=-Ofast -flto -Wno-sign-compare -std=c++11 -Wall -pedantic 
CF+=-fopenmp -fstrict-aliasing -mfpmath=sse -mavx 
CF+=-mpc32 -funsafe-math-optimizations -ffast-math 
CF+=-ftree-vectorize -fopt-info-vec -g
CF+=-falign-functions=1 -falign-jumps=1 -falign-loops=1 -falign-labels=1
CF+=-fassociative-math -freciprocal-math -fno-trapping-math  -funroll-loops -ftree-loop-im


all: task_1 graphs

task_1:
	g++ $(CF) -march=native main.cpp -o task_1

files:
	./files.sh

graphs: files
	gnuplot gnuplot.plot
