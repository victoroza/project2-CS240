#include "Graph.h"
#include <chrono>


using namespace std;

int main(int argc, char* argv[]){
    //declare a couple of time points
	chrono::monotonic_clock::time_point start, finish;

	//declare a nanosecond holder
	chrono::nanoseconds elapsed;
	
	
    Graph g1(Type::UNDIRECTED);
    g1.readFromFile(argv[1]);
    //g1.stepAway(4,-1,"sa.g2.4.-1.txt");
    //Graph g2(Type::DIRECTED); // empty
    //g1.readFromFile("testlarge.txt");
    g1.printOutMatrix();
    //cout << "Connected: " << g1.numConnectedComponents() << endl;
    //cout << "PART: " << g1.partitionable();
    g1.MST("MST.txt");
    cout << endl;
    //cout << g1.tree() << endl;
    
    //get the current time (starts the timer)
	start = chrono::monotonic_clock::now();
	
	g1.stepAway(2,1,"sa.g1.2.1.txt");
	
	//get the current time again (ends the timer)
	finish = chrono::monotonic_clock::now();
	
	//computes the difference in time in nanoseconds
	elapsed = chrono::duration_cast<chrono::nanoseconds>(finish-start);

	//prints out the number of elapsed nanoseconds
	cout << elapsed.count() << " us" << endl;
	g1.writeToFile("NEW.txt");
    /*int v1 = 1;
    int v2;
    while(v1 != 0){
        cout << "Enter v1: ";
        cin >> v1;
        cout << "Enter v2: ";
        cin >> v2;
        cout << "Closeness: " << g1.closeness(v1, v2) << endl;
    }
    g1.stepAway(4, -1, "test");
    g1.stepAway(6, 2, "test");
    g1.stepAway(4, 2, "test");
    g1.addVertex();
    g1.addEdge(11, 12, 1);
    g1.printOutMatrix();
    v1 = 1;
    v2 = 1;
    while(v1 != 0){
        cout << "Enter v1: ";
        cin >> v1;
        cout << "Enter v2: ";
        cin >> v2;
        cout << "Closeness: " << g1.closeness(v1, v2) << endl;
    }
    g1.readFromFile(argv[1]);
    g1.printOutMatrix();
    istringstream ss(argv[2]);
    int source;
    ss >> source;
    g1.BFT(source, argv[3]);
    /*v1 = 1;
    v2 = 1;
    while(v1 != 0){
        cout << "Enter v1: ";
        cin >> v1;
        cout << "Enter v2: ";
        cin >> v2;
        cout << "Closeness: " << g2.closeness(v1, v2) << endl;
    }*/
    //cout << "empty Matrix: " << endl;
    //g2.printOutMatrix();
    /*cout << g1.empty() << endl;
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
    g1.printOutMatrix();*/
    return 0;
}