COMPILER = g++
FLAGS = -g -Wall -std=c++0x
EXE = project2

all: Graph.o driver.o
	$(COMPILER) $(FLAGS) -o $(EXE) Graph.o driver.o
	
driver.o: driver.cpp
	$(COMPILER) $(FLAGS) -c driver.cpp
	
Graph.o: Graph.cpp
	$(COMPILER) $(FLAGS) -c Graph.cpp
	
clean:
	rm -f *.o $(EXE) 