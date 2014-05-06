#include "Graph.h"

using namespace std;

Graph::Graph(Type T){
    Type graphType = T;
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
        //cout << v1 << endl;
        myfile >> v2;
        //cout << v2 << endl;
        myfile >> weight;
        //cout << weight << endl;
        (directed_matrix[v1])[v2] = weight;
        (directed_matrix[v1])[0]++;
    }
    
}

void Graph::printOutMatrix(){
    for(int i = 1; i < (numVerticies+1); i++){
        for(int f = 1; f < (numVerticies+1); f++){
            cout << directed_matrix[i][f] << "\t";
        }
        cout << endl;
    }
}


void Graph::writeToFile(string file){
    ofstream myfile;
    myfile.open(file);
    if(myfile.is_open()){
        
    }
}

bool Graph::empty(){
    if(numVerticies > 0){
        return false;
    }
    else{
        return true;
    }
}

void Graph::addEdge(int v1, int v2, double weight){
    if(v1 <= numVerticies && v2 <= numVerticies){
        (directed_matrix[v1])[v2] = weight;
        (directed_matrix[v1])[0]++;
        numEdges++;
    }
    else{
        throw out_of_range("No such vertex");
    }
}

void Graph::addVertex(){
    numVerticies++;
    map<int, double> mapToAdd;
    directed_matrix[numVerticies] = mapToAdd;
}

int Graph::numConnectedComponents(){
    return 0;
}

bool Graph::tree(){
    return false;
}

void Graph::DFT(int source, string file){
    
}

void Graph::BFT(int source, string file){
    
}

int Graph::closeness(int v1, int v2){
    map<int, int> distFromV1;
    map<int, bool> checked;
    stack<int> distStack;
    int currentDistance = 1;
    int currentNode = v1;
    if(v1 == v2 && (directed_matrix[v1])[0] == 0 ){
        return 0;
    }
    for(int i = 1; i <= numVerticies; i++){
        distFromV1[i] = INT_MAX;
        if((directed_matrix[v1])[i] != 0){
            if(v2 == i){
                return 1;
            }
            distFromV1[i] = currentDistance;
            distStack.push(i);
            cout << distStack.size() << endl;
            checked[i] = false;
        }
    }
    checked[v1] == true;
    currentNode = distStack.top();
    cout << currentNode << endl;
    cout << (directed_matrix[currentNode])[0] << endl;
    bool addedNew = false;
    while(!distStack.empty()){
        addedNew = false;
        if((directed_matrix[currentNode])[0] != 0){
            currentDistance++;
            cout << "step 1" << endl;
            
            for(int i = 1; i <= numVerticies; i++){
                if((directed_matrix[currentNode])[i] != 0 && currentDistance < distFromV1[i]){
                    addedNew = true;
                    distFromV1[i] = currentDistance;
                    distStack.push(i);
                    cout << "i: " << i << " dist: " << distFromV1[i] << " dist size: " << distStack.size() << " top : " << distStack.top() << endl;
                }
                
            }
            checked[currentNode] = true;
            currentNode = distStack.top();
        }
        checked[currentNode] = true;
        if(!addedNew && checked[distStack.top()] == true){
            cout << "Top: " << distStack.top() << endl;
            currentDistance = distFromV1[distStack.top()];
            cout << "final Distance: " << currentDistance << endl;
            distStack.pop();
            if(distStack.size() == 0){
                cout << "what:";
                if(distFromV1[v2] == INT_MAX){
                    return -1;
                }
                return distFromV1[v2];
            }
            currentNode = distStack.top();
        }
    }
    return 0;
}

bool Graph::partitionable(){
    return false;
}

bool Graph::MST(string file){
    return false;
}

void Graph::stepAway(int value, int closeness, string file){
    
}