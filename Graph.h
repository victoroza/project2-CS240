//Put any include statements here
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <stdexcept>
#include <climits>
#include <stack>
#include <queue>
#include <utility>

//This class will be used to create a graph library.
enum Type {DIRECTED,UNDIRECTED};

class Graph{
	private:
		//Put your private data members here
		int numVertices;
	    int numEdges;
	    std::map<int, std::map<int, double>> directed_matrix; //using for everything
	    std::map<int, std::map<int, double>> always_udm;
	    std::map<int, std::map<int, int>> stepAwayMap;
	    Type graphType;
	    std::map<int, bool> checked_DFT;
        std::map<int, bool> done_DFT;
	    void DFT_helper(int source);
	    int numConnectedComps;
	    std::map<int, std::map<int, bool>> connectedComps;
	    std::multimap<double,std::pair<int, int>> sortedList;
	public:
	    
	    //Put your private methods here
		//Construct an empty graph of the specified type
		Graph(Type t);
		//Delete a graph
		~Graph();
		//Read a graph from a file
		void readFromFile(std::string file);
		//Write a graph to a file
		void writeToFile(std::string file);
		//Empty
		bool empty();
		//Add edge
		void addEdge(int v1, int v2, double weight);
		//Add vertex
		void addVertex();
		//Count connected components
		int numConnectedComponents();
		//Tree check
		bool tree();
		//Depth First Traverse - proceed from source
		void DFT(int source, std::string file);
		//Breadth First Traverse - proceed from source
		void BFT(int source, std::string file);
		//Closeness - determine minimum number of edges to get
		// from one node to the other
		int closeness(int v1, int v2);
		//* Partition - determine if you can partition the graph
		bool partitionable();
		//* MST - print the minimum spanning tree of the graph
		//to a file with the passed name (return whether or not
        //this operation was successful)
		bool MST(std::string file);
		//* Step Away - print the nodes who are a degree of
		//closeness from the source to a file with the passed name
		void stepAway(int source, int closeness, std::string file);
		//Print out matrix
		void printOutMatrix();
};
