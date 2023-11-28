#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <chrono>
#include "sort.h"

using namespace std;

int main(int argc, char** argv)
{
    if(argc != 4)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    
    SorterTree* the_thing = new SorterTree(pivot_chooser,num_entries);   

    bool qs = atoi(argv[3]);
    
    if (qs){
        //time quicksot with BST
        start = std::chrono::system_clock::now();
        the_thing->QuicksortWithBSTInsert(0,num_entries-1);
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        
        cout << "elapsed time: " << elapsed_seconds.count() << '\n';
        cout<< "Imbalance: "<< the_thing->getTree()->getImbalance()<<'\n';
        cout<< "Comparisons: "<<the_thing->getComparisons()<<endl;
        the_thing->getTree()->printBST("",0);
        the_thing->printArray();
    }
    else{
        start = std::chrono::system_clock::now();
        the_thing->QuicksortWithBSTInsert(0,num_entries-1);
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        cout << "elapsed time: " << elapsed_seconds.count() << '\n';
        cout<< "Comparisons: "<<the_thing->getComparisons()<<endl;
        the_thing->printArray();
    }
    

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair - dealt in the constructor
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    delete the_thing;
}
