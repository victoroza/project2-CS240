#include "Graph.h"

using namespace std;

Graph::Graph(){
    numVerticies = 0;
    numEdges = 0;
    directed = true;
}

Graph::~Graph(){
    
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
    map<int, double> startVec;
    for(int i = 1; i < (numVerticies+1); i++){
        directed_matrix[i] = startVec;
    }
    while(!myfile.eof()){
        int v1;
        int v2;
        double weight;
        myfile >> v1;
        cout << v1 << endl;
        myfile >> v2;
        cout << v2 << endl;
        myfile >> weight;
        cout << weight << endl;
        (directed_matrix[v1])[v2] = weight;
    }
    for(int i = 0; i < (numVerticies+1); i++){
        for(int f = 0; f < (numVerticies+1); f++){
            cout << directed_matrix[i][f] << " ";
        }
        cout << endl;
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