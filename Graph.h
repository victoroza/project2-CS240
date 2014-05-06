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

//This class will be used to create a graph library.
enum Type {DIRECTED,UNDIRECTED};

class Graph{
	private:
		//Put your private data members here
		bool directed;
		int numVerticies;
	    int numEdges;
	    std::map<int, std::map<int, double>> directed_matrix;
		//Put your private methods here
	/*public:
		//Construct
		Graph();
		//Delete
		~Graph();
		//Read A Graph From A File
		void readFromFile(std::string file);
		//Write A Graph To A File
		void writeToFile(std::string file);
		//Empty
		bool empty();
		//Add Edge
		void addEdge(int v1, int v2, double weight);
		//Add Vertex
		void addVertex();
		//Count Connected Components
		int numConnectedComponents();
		//Tree Check
		bool tree();
		//Depth First Traverse
		void DFT(int source);
		//Breadth First Traverse
		void BFT(int source);
		//Closeness
		int closeness(std::string v1, std::string v2);
		// Partition
		bool partitionable();
		// MST
		bool MST(const Graph& g, std::string file);
		// Step Away
		void stepAway(int value, std::string file);
	*/
	public:
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
