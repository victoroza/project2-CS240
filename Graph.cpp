#include "Graph.h"

using namespace std;

Graph::Graph(){
    numVerticies = 0;
    numEdges = 0;
    directed = true;
}

void Graph::readFromFile(string file){
    string line;
    ifstream myfile;
    myfile.open(file);
    if(myfile.is_open()){
        getline(myfile, line);
        if(line != "directed"){
            directed = false;
        }
        getline(myfile, line);
        int buffer;
        stringstream ss(line);
        ss >> buffer;
        numVerticies = buffer;
        getline(myfile, line);
        stringstream ss1(line);
        ss1 >> buffer;
        numEdges = buffer;
    }
    vector<double> startVec(numVerticies*2, -1);
    for(int i = 0; i < numVerticies; i++){
        directed_matrix.push_back(startVec);
    }
}


void Graph::writeToFile(string file){
    
}

bool Graph::empty(){
    
}

void Graph::addEdge(int v1, int v2, double weight){
    
}

void Graph::addVertex(){
    
}

int Graph::numConnectedComponents(){
    
}

bool Graph::tree(){
    
}

void Graph::DFT(int source){
    
}

void Graph::BFT(int source){
    
}

int Graph::closeness(string v1, string v2){
    
}

bool Graph::partitionable(){
    
}

bool Graph::MST(const Graph& g, string file){
    
}

void Graph::stepAway(int value, string file){
    
}