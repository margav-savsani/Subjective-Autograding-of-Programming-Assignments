#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>  
#include <ctime>  

using namespace std;
int main(int argc, char** argv)
{   
    using namespace std::chrono;

    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
   
    SorterTree s = SorterTree(pivot_chooser,num_entries) ;
    BST* tree = s.getTree() ; 
    cout<<"Enter JourneyCode and Price below : "<<endl ; 
     for(int i=0; i<num_entries; i++){
        int x ,y ;
        cin>>x>>y ; 
         //x = rand() % 100 ; //for random checking
         //y = rand() % 100;  
        s.insert_element(x,y);
    }   
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    s.Quicksort(0,num_entries-1);
    cout<<"The tree Imbalance : "<<tree->getImbalance()<<endl  ; 
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    cout << "Elapsed time: " << elapsed_seconds.count()*1000 << " milli seconds\n";

    cout<<"The sorted array : "<<endl ; 
    s.printArray();
    cout<<"The Bst Tree : "<<endl ;
    s.getTree()->printBST(""); 
}
