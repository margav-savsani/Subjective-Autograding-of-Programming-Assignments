#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include<chrono>

using namespace std::chrono;
using namespace std;

int main(int argc, char** argv)
{
    if(argc != 3)//checking that the number of arguments given are 3
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    //Here I have considered that the total chooser functions are three since in choose.cpp and choose.h we have been given only three chooser functions 

    SorterTree s(pivot_chooser, num_entries);//created an object of class SorterTree which is the main thing for sorting 
    for(int i=0;i<num_entries;i++){//loop for input of values in SorterTree using insert method in sorter Tree
        unsigned int j,p;
        cout<<"Enter the journeyCode and price : ";
        cin>>j>>p;
        s.insert(j,p);//insert function of SorterTree 
    }

    auto start= high_resolution_clock::now();//note the time before using QuickSort
    s.QuicksortWithBSTInsert(0, num_entries-1);//calling the QuickSortWithBSTInsert method that is responsible for both creating 
    //and sorting binary tree and array respectively, Hence not called QuickSort in main 
    auto stop=high_resolution_clock::now();//note the time after using QuickSort
    auto duration=duration_cast<microseconds>(stop-start);
    s.printArray();//print Array which also prints the bST
    cout<<"Imbalance: "<<s.getImbalance()<<endl;//output imbalance
    cout<<"Total number of comparisons are: "<<s.total_comparisons()<<endl;//output total number of comparison made
    cout<<"Total time taken by SorterTree: "<<duration.count()<<" microseconds"<<endl;//output time takenin quicksort
    //using the start and stop that we created 

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
