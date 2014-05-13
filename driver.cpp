#include "Graph.h"
#include <chrono>


using namespace std;

int main(int argc, char* argv[]){
    //declare a couple of time points
	chrono::monotonic_clock::time_point start, finish;

	//declare a nanosecond holder
	chrono::nanoseconds elapsed;
	
    Graph g1(Type::UNDIRECTED);
    std::string arg1(argv[1]);
    if(arg1 == "g1.txt"){
        cout << "G1: " << endl;
        g1.readFromFile(argv[1]);
        g1.printOutMatrix();
        g1.DFT(1, "dft.g1.1.txt");
        g1.BFT(2, "bft.g1.2.txt");
        
        cout << endl;
        cout << "1,4: " << g1.closeness(1,4) << endl;
        cout << "2,6: " << g1.closeness(2,6) << endl;
        cout << "4,5: " << g1.closeness(4,5) << endl;
        cout << "2,2: " << g1.closeness(2,2) << endl;
        cout << endl;
        cout << "num connected: " << g1.numConnectedComponents() << endl;
        cout << "is tree: " << g1.tree() << endl;
   
        //get the current time (starts the timer)
    	start = chrono::monotonic_clock::now();
    	
        
        g1.stepAway(2,-1,"sa.g1.2.-1.txt");
        
        //get the current time again (ends the timer)
    	finish = chrono::monotonic_clock::now();
    	
    	//computes the difference in time in nanoseconds
    	elapsed = chrono::duration_cast<chrono::nanoseconds>(finish-start);
    	//prints out the number of elapsed nanoseconds
    	cout << elapsed.count() << " us - step away" << endl;
    	
    	
    	
    	//get the current time (starts the timer)
    	start = chrono::monotonic_clock::now();
    	
        
        g1.MST("mst.g1.txt");
        
        //get the current time again (ends the timer)
    	finish = chrono::monotonic_clock::now();
    	
    	//computes the difference in time in nanoseconds
    	elapsed = chrono::duration_cast<chrono::nanoseconds>(finish-start);
    	//prints out the number of elapsed nanoseconds
    	cout << elapsed.count() << " us - mst" << endl;
    	
    	
    	
    	//get the current time (starts the timer)
    	start = chrono::monotonic_clock::now();
    	
        
        cout << "partionable: " << g1.partitionable() << endl;
        
        //get the current time again (ends the timer)
    	finish = chrono::monotonic_clock::now();
    	
    	//computes the difference in time in nanoseconds
    	elapsed = chrono::duration_cast<chrono::nanoseconds>(finish-start);
    	//prints out the number of elapsed nanoseconds
    	cout << elapsed.count() << " us - partition" << endl;
    	
        g1.stepAway(1,2,"sa.g1.1.2.txt");
        g1.stepAway(2,1,"sa.g1.2.1.txt");
    	
    	
    
    	
    }
    
    
    
    else{
        cout << "G2: " << endl;
        g1.readFromFile(argv[1]);
        g1.printOutMatrix();
        g1.BFT(7,"bft.g2.7.txt");
        g1.DFT(2,"dft.g2.2.txt");
        g1.DFT(4,"dft.g2.4.txt");
        
        cout << endl;
        cout << "4,2: " << g1.closeness(4,2) << endl;
        cout << "6,4: " << g1.closeness(6,4) << endl;
        cout << endl;
        cout << "num connected: " << g1.numConnectedComponents() << endl;
        cout << "is tree: " << g1.tree() << endl;
   
        //get the current time (starts the timer)
    	start = chrono::monotonic_clock::now();
    	
        
        g1.stepAway(4,-1,"sa.g2.4.-1.txt");
        
        //get the current time again (ends the timer)
    	finish = chrono::monotonic_clock::now();
    	
    	//computes the difference in time in nanoseconds
    	elapsed = chrono::duration_cast<chrono::nanoseconds>(finish-start);
    	//prints out the number of elapsed nanoseconds
    	cout << elapsed.count() << " us - step away" << endl;
    	
    	
    	
    	//get the current time (starts the timer)
    	start = chrono::monotonic_clock::now();
    	
        
        g1.MST("mst.g2.txt");
        
        //get the current time again (ends the timer)
    	finish = chrono::monotonic_clock::now();
    	
    	//computes the difference in time in nanoseconds
    	elapsed = chrono::duration_cast<chrono::nanoseconds>(finish-start);
    	//prints out the number of elapsed nanoseconds
    	cout << elapsed.count() << " us - mst" << endl;
    	
    	
    	
    	//get the current time (starts the timer)
    	start = chrono::monotonic_clock::now();
    	
        
        cout << "partionable: " << g1.partitionable() << endl;
        
        //get the current time again (ends the timer)
    	finish = chrono::monotonic_clock::now();
    	
    	//computes the difference in time in nanoseconds
    	elapsed = chrono::duration_cast<chrono::nanoseconds>(finish-start);
    	//prints out the number of elapsed nanoseconds
    	cout << elapsed.count() << " us - partition" << endl;
    	
        g1.stepAway(1,2,"sa.g1.1.2.txt");
        g1.stepAway(2,1,"sa.g1.2.1.txt");
    	
    	
    
    	
    }
    
        //
    return 0;
}