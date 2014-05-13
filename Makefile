COMPILER = g++
FLAGS = -g -Wall -std=c++0x -O3
EXE = GraphLab

all: Graph.a driver.o
	$(COMPILER) $(FLAGS) -o $(EXE) driver.o -L. Graph.a 
	
driver.o: driver.cpp
	$(COMPILER) $(FLAGS) -c driver.cpp
	
Graph.o: Graph.cpp
	$(COMPILER) $(FLAGS) -c Graph.cpp

Graph.a: Graph.o
	ar -rcs Graph.a Graph.o
	rm Graph.o
	
clean:
	rm -f *.o $(EXE) Graph.a