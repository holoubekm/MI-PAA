CF=-Ofast -flto -Wno-sign-compare -std=c++11 -Wall -pedantic 
CF+=-fopenmp -fstrict-aliasing -mfpmath=sse -mavx 

all: knapgen

knapgen: makefile knapgen.c knapcore.h knapcore.c
	g++ -O0 -Wall -pedantic -fopenmp -g -march=native knapgen.c knapcore.c -lm -o knapgen

generate: knapgen
	./generate.sh
