#include "Graph.h"

using namespace std;

int main(){
    Graph g1;
    Graph g2; // empty
    g1.readFromFile("test.txt");
    g1.printOutMatrix();
    cout << "empty Matrix: " << endl;
    g2.printOutMatrix();
    cout << g1.empty() << endl;
    cout << g2.empty() << endl;
    try{
        g1.addEdge(8,5, 0.9);
        g1.printOutMatrix();
        g2.addEdge(1,1, 8.3);
        g2.printOutMatrix();
    }
    catch(exception e){
        cout << e.what() << endl;
    }
    g1.addVertex();
    cout << "New: " << endl;
    //g1.addVertex();
    g1.addEdge(11, 10, 8.3);
    //g1.printOutMatrix();
    g1.printOutMatrix();
    return 0;
}