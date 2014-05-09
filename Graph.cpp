#include "Graph.h"

using namespace std;

Graph::Graph(Type T){
    graphType = T;
    numVertices = 0;
    numEdges = 0;
    numConnectedComps = -1;
}

Graph::~Graph(){
    
}

void Graph::readFromFile(string file){
    directed_matrix.clear();
    always_udm.clear();
    numConnectedComps = -1;
    string line;
    ifstream myfile;
    myfile.open(file);
    stepAwayMap.clear();
    connectedComps.clear();
    //numConnectedComps = -1;
    if(myfile.is_open()){
        getline(myfile, line);
        if(line == "directed" || line == "DIRECTED"){
            graphType = DIRECTED;
        }
        else{
            graphType = UNDIRECTED;
        }
        getline(myfile, line);
        int buffer;
        stringstream ss(line);
        ss >> buffer;
        numVertices = buffer;
        getline(myfile, line);
        stringstream ss1(line);
        ss1 >> buffer;
        numEdges = buffer;
        if(numVertices > 0){
            numConnectedComps = 1;
        }
    }
    else{
        return;
    }
    map<int, double> startVec;
    for(int i = 1; i < (numVertices+1); i++){
        directed_matrix[i] = startVec;
        always_udm[i] = startVec;
    }
    while(!myfile.eof()){
        int v1;
        int v2;
        double weight;
        myfile >> v1;
        myfile >> v2;
        myfile >> weight;
        (directed_matrix[v1])[v2] = weight;
        (always_udm[v1])[v2] = weight;
        if(graphType == UNDIRECTED){
            (directed_matrix[v2])[v1] = weight;
            (directed_matrix[v2])[0]++;
        }
        (always_udm[v2])[v1] = weight;
        (always_udm[v2])[0]++;
        (always_udm[v1])[0]++;
        (directed_matrix[v1])[0]++;
    }
    myfile.close();
    stepAwayMap.clear();
    map<int, int> tempStep;
    for(int i = 1; i <= numVertices; i++){
        tempStep.clear();
        for(int n = 1; n <= numVertices; n++){
            tempStep[n] = closeness(i, n);
        }
        stepAwayMap[i] = tempStep;
    }
    int NCC = numConnectedComponents();
}

void Graph::printOutMatrix(){
    for(int i = 1; i < (numVertices+1); i++){
        for(int f = 1; f < (numVertices+1); f++){
            cout << directed_matrix[i][f] << "\t";
        }
        cout << endl;
    }
}


void Graph::writeToFile(string file){
    map<int, map<int, bool>> checked;
    ofstream myfile;
    myfile.open(file);
    if(myfile.is_open()){
        if(graphType == DIRECTED){
            myfile << "directed" << endl;
        }
        else{
            myfile << "undirected" << endl;
        }
        myfile << numVertices << endl;
        myfile << numEdges << endl;
        for(int i = 1; i <= numVertices; i++){
            for(int n = 1; n <= numVertices; n++){
                if(graphType == UNDIRECTED){
                    if((checked[n])[i] != true && (directed_matrix[i])[n] != 0){
                        (checked[i])[n] = true;
                        (checked[n])[i] = true;
                        myfile << i << " " << n << " ";
                        double dtof = (directed_matrix[i])[n];
                        myfile << dtof << endl;
                    }
                }
                else if((directed_matrix[i])[n] != 0){
                    myfile << i << " " << n << " ";
                    double dtof = (directed_matrix[i])[n];
                    myfile << dtof << endl;
                }
            }
        }
    }
    myfile.close();
}

bool Graph::empty(){
    if(numVertices > 0){
        return false;
    }
    else{
        return true;
    }
}

void Graph::addEdge(int v1, int v2, double weight){
    numConnectedComps = -1;
    if(v1 <= numVertices && v2 <= numVertices){
        (directed_matrix[v1])[v2] = weight;
        (directed_matrix[v1])[0]++;
        (always_udm[v1])[v2] = weight;
        (always_udm[v1])[0]++;
        (always_udm[v2])[v1] = weight;
        (always_udm[v2])[0]++;
        numEdges++;
        if(graphType == UNDIRECTED){
            (directed_matrix[v2])[v1] = weight;
            (directed_matrix[v2])[0]++;
        }
        stepAwayMap.clear();
        map<int, int> tempStep;
        for(int i = 1; i <= numVertices; i++){
            tempStep.clear();
            for(int n = 1; n <= numVertices; n++){
                tempStep[n] = closeness(i, n);
            }
            stepAwayMap[i] = tempStep;
        }
    }
    else{
        throw out_of_range("No such vertex");
    }
    int NCC = numConnectedComponents();
}

void Graph::addVertex(){
    numConnectedComps = -1;
    numVertices++;
    map<int, double> mapToAdd;
    directed_matrix[numVertices] = mapToAdd;
    always_udm[numVertices] = mapToAdd;
    stepAwayMap.clear();
    map<int, int> tempStep;
    for(int i = 1; i <= numVertices; i++){
        tempStep.clear();
        for(int n = 1; n <= numVertices; n++){
            tempStep[n] = closeness(i, n);
        }
        stepAwayMap[i] = tempStep;
    }
    int NCC = numConnectedComponents();
}

int Graph::numConnectedComponents(){
    //WORKING ON THIS
    /*
    
    int countConnected = 0;
    multimap<double,pair<int, int>> sortedList;
    for(int i = 1; i <= numVertices; i++){
        if((directed_matrix[i])[0] != 0){
            for(int n = 1; n <= numVertices; n++){
                bool found = false;
                int count = sortedList.count(((directed_matrix[i])[n]));
                if(count > 0){
                    multimap<double,pair<int, int>>::iterator it;
                    for (it=sortedList.equal_range(((directed_matrix[i])[n])).first; it!=sortedList.equal_range(((directed_matrix[i])[n])).second; it++){
                        if((*it).second == make_pair(n, i)){
                            found = true;
                        }
                    }
                }
                if(!found && (directed_matrix[i])[n] != 0){
                    sortedList.insert(make_pair((directed_matrix[i])[n], make_pair(i, n)));
                    cout << i << "   " << n << endl;
                }
            }
        }
    }
    multimap<double, pair<int, int>>::iterator it;
    for(it= sortedList.begin(); it != sortedList.end(); it++){
        cout << (*it).first << "   (" << get<0>((*it).second) << ", " << get<1>((*it).second) << ")" << endl;
    }
    */
    
    int countConnected = 0;
    int currentNode;
    map<int, bool> checked;
    for(int i = 1; i <= numVertices; i++){
        checked[i] = false;
    }
    queue<int> toTraverse;
    int source;
    if(numVertices > 0){
        source = 1;
    }
    else{
        cerr << "Graph is empty!" << endl;
        return -1;
    }
    if(numVertices < 2){
        return 1;
    }
    bool keepChecking = true;
    while(keepChecking){
        countConnected++;
        if((always_udm[source])[0] != 0){
            (connectedComps[countConnected])[source] = false;
            for(int i = 1; i <= numVertices; i++){
                if((always_udm[source])[i] != 0){
                    toTraverse.push(i);
                    checked[i] = true;
                    //cout << i << endl;
                    (connectedComps[countConnected])[i] = false;
                }
            }
            checked[source] = true;
            if(!toTraverse.empty()){
                currentNode = toTraverse.front();
                toTraverse.pop();
                while(currentNode != 0){
                    for(int i = 1; i <= numVertices; i++){
                        if((always_udm[currentNode])[i] != 0 && checked[i] != true){
                            toTraverse.push(i);
                            checked[i] = true;
                            //cout << i << endl;
                            (connectedComps[countConnected])[i] = false;
                        }
                    }
                    currentNode = toTraverse.front();
                    toTraverse.pop();
                    
                }
            }
        }
        else{
            checked[source] = true;
            (connectedComps[countConnected])[source] = false;
        }
        int i = 1;
        bool findI = true;
        while(findI && i <= numVertices){
            if(checked[i] == false){
                source = i;
                findI = false;
            }
            i++;
        }
        if(findI == true){
            keepChecking = false;
        }
    }
    numConnectedComps = countConnected;
    return countConnected;
}

bool Graph::tree(){
    if(numConnectedComponents() == 1 && (numEdges == (numVertices - 1))){
        return true;
    }
    return false;
}

void Graph::DFT(int source, string file){
    //map<int, bool> checked; //MOVED THESE TO PRIVATE VARIABLES
    //map<int, bool> done; //MOVED TO PRIVATE
    checked_DFT[source] = true;
    for(int i = 1; i <= numVertices; i++){
        if((directed_matrix[source])[i] > 0){
            DFT_helper(i);
            done_DFT[source] = true;
        }
    }
    
    //Print to file before clear
    
    //Just clear them once the function is over
    checked_DFT.clear();
    done_DFT.clear();
}

void Graph::DFT_helper(int source){
    checked_DFT[source] = true;
    for(int i = 1; i <= numVertices; i++){
        if((directed_matrix[source])[i] > 0){
            if(checked_DFT[i] != true){
                DFT_helper(i);
                done_DFT[source] = true;
            }
        }
    }
}

void Graph::BFT(int source, string file){
    ofstream myfile;
    myfile.open (file);
    map<int, bool> checked;
    queue<int> toTraverse;
    int currentNode = source;
    if(source > numVertices || source < 1){
        myfile.close();
        return;
    }
    myfile << source << endl;
    if((directed_matrix[source])[0] != 0){
        for(int i = 1; i <= numVertices; i++){
            if((directed_matrix[source])[i] != 0){
                myfile << i << endl;
                toTraverse.push(i);
                checked[i] = true;
            }
            else{
                checked[i] = false;
            }
        }
        checked[source] = true;
        if(toTraverse.empty()){
            myfile.close();
            return;
        }
        currentNode = toTraverse.front();
        toTraverse.pop();
        while(currentNode != 0){
            for(int i = 1; i <= numVertices; i++){
                if((directed_matrix[currentNode])[i] != 0 && checked[i] != true){
                    myfile << i << endl;
                    toTraverse.push(i);
                    checked[i] = true;
                }
            }
            currentNode = toTraverse.front();
            toTraverse.pop();
            
        }
    }
    myfile.close();
}

int Graph::closeness(int v1, int v2){
    map<int, int> distFromV1;
    map<int, bool> checked;
    stack<int> distStack;
    int currentDistance = 1;
    int currentNode = v1;
    if(v1 > numVertices || v1 < 1 || v2 > numVertices || v2 < 1){
        return -1;
    }
    if(v1 == v2){
        return 0;
    }
    if((directed_matrix[v1])[0] == 0 && (directed_matrix[v2])[0] == 0 ){
        return -1;
    }
    else if((directed_matrix[v1])[0] == 0 && (directed_matrix[v2])[0] != 0 ){
        int tempv1 = v1;
        int tempv2 = v2;
        v2 = tempv1;
        v1 = tempv2;
        currentNode = v2;
    }
    for(int i = 1; i <= numVertices; i++){
        distFromV1[i] = INT_MAX;
        if((directed_matrix[v1])[i] != 0){
            if(v2 == i){
                return 1;
            }
            distFromV1[i] = currentDistance;
            distStack.push(i);
            checked[i] = false;
        }
    }
    checked[v1] == true;
    currentNode = distStack.top();
    bool addedNew = false;
    while(!distStack.empty()){
        addedNew = false;
        if((directed_matrix[currentNode])[0] != 0){
            currentDistance++;
            for(int i = 1; i <= numVertices; i++){
                if((directed_matrix[currentNode])[i] != 0 && currentDistance < distFromV1[i]){
                    addedNew = true;
                    distFromV1[i] = currentDistance;
                    distStack.push(i);
                }
                
            }
            checked[currentNode] = true;
            currentNode = distStack.top();
        }
        checked[currentNode] = true;
        if(!addedNew && checked[distStack.top()] == true){
            currentDistance = distFromV1[distStack.top()];
            distStack.pop();
            if(distStack.size() == 0){
                if(distFromV1[v2] == INT_MAX){
                    return -1;
                }
                return distFromV1[v2];
            }
            currentNode = distStack.top();
        }
    }
    return -1;
}

bool Graph::partitionable(){
    /*map<int, bool> reds;
    map<int, bool> blacks;
    if((directed_matrix[source])[0] != 0){
        for(int i = 1; i <= numVertices; i++){
            if((directed_matrix[source])[i] != 0){
                cout << i << endl;
                toTraverse.push(i);
                checked[i] = true;
            }
            else{
                checked[i] = false;
            }
        }
        checked[source] = true;
        if(toTraverse.empty()){
            return;
        }
        currentNode = toTraverse.front();
        toTraverse.pop();
        while(currentNode != 0){
            for(int i = 1; i <= numVertices; i++){
                if((directed_matrix[currentNode])[i] != 0 && checked[i] != true){
                    cout << i << endl;
                    toTraverse.push(i);
                    checked[i] = true;
                }
            }
            currentNode = toTraverse.front();
            toTraverse.pop();
            
        }
    }*/
    map<int, bool> checked;
    map<int, bool> reds;
    map<int, bool> blues;
    bool isRed = true;
    for(int i = 1; i <= numVertices; i++){
        reds[i] = false;
        blues[i] = false;
    }
    queue<int> toTraverse;
    int source = 1;
    int currentNode = source;
    if(source > numVertices || source < 1){
        //myfile.close();
        return false;
    }
    cout << source << endl;
    blues[source] = true;
    cout << "BLUE: " << source << endl;
    if((always_udm[source])[0] != 0){
        for(int i = 1; i <= numVertices; i++){
            if((always_udm[source])[i] != 0){
                cout << i << endl;
                
                toTraverse.push(i);
                checked[i] = true;
                if(isRed){
                    reds[i] = true;
                    isRed = false;
                    cout << "RED: " << i; << endl;
                }
                else{
                    blues[i] = true;
                    isRed = true;
                }
            }
            else{
                checked[i] = false;
            }
        }
        checked[source] = true;
        if(!toTraverse.empty()){
            currentNode = toTraverse.front();
            toTraverse.pop();
            while(currentNode != 0){
                for(int i = 1; i <= numVertices; i++){
                    if((always_udm[currentNode])[i] != 0){
                        cout << i << endl;
                        toTraverse.push(i);
                        checked[i] = true;
                        if(isRed){
                            if(reds[i] == true){
                                return false;
                            }
                            reds[i] = true;
                            isRed = false;
                        }
                        else{
                            if(blues[i] == true){
                                return false;
                            }
                            blues[i] = true;
                            isRed = true;
                        }
                    }
                }
                currentNode = toTraverse.front();
                toTraverse.pop();
                
            }
        }
    }
    return true;
}

bool Graph::MST(string file){
    ofstream myfile;
    myfile.open (file);
    map<int, bool>::iterator imm;
    //cout << "Num of connected: " << numConnectedComps << endl;
    //for(int i = 1; i <= numConnectedComps; i++){
    //    cout << i << ": ";
    //    for(imm = (connectedComps[i]).begin(); imm != (connectedComps[i]).end(); imm++){
    //        cout << imm -> first << " ";
    //    }
    //    cout << endl;
    //}
    int countConnected = 0;
    multimap<double,pair<int, int>> sortedList;
    for(int i = 1; i <= numVertices; i++){
        if((directed_matrix[i])[0] != 0){
            for(int n = 1; n <= numVertices; n++){
                bool found = false;
                int count = sortedList.count(((directed_matrix[i])[n]));
                if(count > 0){
                    multimap<double,pair<int, int>>::iterator it;
                    for (it=sortedList.equal_range(((directed_matrix[i])[n])).first; it!=sortedList.equal_range(((directed_matrix[i])[n])).second; it++){
                        if((*it).second == make_pair(n, i)){
                            found = true;
                        }
                    }
                }
                if(!found && (directed_matrix[i])[n] != 0){
                    sortedList.insert(make_pair((directed_matrix[i])[n], make_pair(i, n)));
                    //cout << i << "   " << n << endl;
                }
            }
        }
    }
    multimap<double, pair<int, int>>::iterator it;
   // for(it= sortedList.begin(); it != sortedList.end(); it++){
    //    cout << (*it).first << "   (" << get<0>((*it).second) << ", " << get<1>((*it).second) << ")" << endl;
    //}
    if(numConnectedComps == 1){
        myfile << "{ {";
        for(int i = 1; i <= numVertices; i++){
            if((i+1) <= numVertices){
                myfile << i << ", ";
            }
            else{
                myfile << i << "}";
            }
        }
        myfile << ", { ";
        bool checking = true;
        map<int, bool> inMST;
        for(int i = 1; i <= numVertices; i++){
            inMST[i] = false;
        }
        if(numVertices == 1){
            myfile << "}" << endl;
        }
        it = sortedList.begin();
        while(checking && it != sortedList.end()){
            //cout << (*it).first << "   (" << get<0>((*it).second) << ", " << get<1>((*it).second) << ")" << endl;
            if(!(inMST[get<0>((*it).second)] == true && inMST[get<1>((*it).second)])){
                myfile << "(" << get<0>((*it).second) << "," << get<1>((*it).second) << "," << (*it).first << ")";
                inMST[get<0>((*it).second)] = true;
                inMST[get<1>((*it).second)] = true;
            }
            int tC = 0;
            for(int i = 1; i <= numVertices; i++){
                if(inMST[i] == false){
                    tC++;
                }
            }
            if(tC == 0){
                checking = false;
                myfile << " } }" << endl;
                return true;
            }
            else{
                myfile << ", ";
            }
            
            it++;
        }
        
    }
    else if(numConnectedComps > 1){
        for(int l = 1; l <= numConnectedComps; l++){
            myfile << "{ {";
            map<int, bool>::iterator lib;
            for(lib = (connectedComps[l]).begin(); lib != (connectedComps[l]).end(); lib++){
                lib++;
                if((lib) != (connectedComps[l]).end()){
                    lib--;
                    myfile << lib ->first << ", ";
                }
                else{
                    lib--;
                    myfile << lib->first << "}";
                }
            }
            myfile << ", { ";
            bool checking = true;
            map<int, bool> inMST = connectedComps[l];
            it = sortedList.begin();
            while(checking && it != sortedList.end()){
                //cout << (*it).first << "   (" << get<0>((*it).second) << ", " << get<1>((*it).second) << ")" << endl;
                string line;
                if((inMST.find(get<0>((*it).second)) != inMST.end() && inMST.find(get<1>((*it).second)) != inMST.end()) && !(inMST[get<0>((*it).second)] == true && inMST[get<1>((*it).second)])){
                    //cout << "(" << get<0>((*it).second) << "," << get<1>((*it).second) << "," << (*it).first << ")";
                    line =  "(";
                    stringstream convert;
                    string temp;
                    convert << get<0>((*it).second);
                    temp = convert.str();
                    line += temp + ",";
                    stringstream convert1;
                    string temp1;
                    convert1 << get<1>((*it).second);
                    temp1 = convert1.str();
                    line += temp1 + ",";
                    stringstream convert2;
                    string temp2;
                    convert2 << (*it).first;
                    temp2 = convert2.str();
                    line += temp2 + ")";
                    myfile << line;
                    inMST[get<0>((*it).second)] = true;
                    inMST[get<1>((*it).second)] = true;
                }
                int tC = 0;
                
                for(lib = inMST.begin(); lib != inMST.end(); lib++){
                    if(lib->second == false){
                        tC++;
                    }
                }
                if(tC == 0 || inMST.size() == 1){
                    checking = false;
                    myfile << " } }" << endl;
                    //return true;
                }
                else{
                    if(line.size() > 0){
                        myfile << ", ";
                    }
                }
                
                it++;
            }
        }
    }
    myfile.close();
    if(numConnectedComps < 1){
        return false;
    }
    return true;
}

void Graph::stepAway(int source, int closeness, string file){
    int count = 0;
    cout << "STEP AWAY" << endl;
    for(int i = 1; i <= numVertices; i++){
        if((stepAwayMap[source])[i] == closeness){
            cout << i << endl;
        }
    }
}