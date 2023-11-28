#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>
//to compile just do g++ makeTree.cpp ./a.out num_entries pivot < inputfile
using namespace std;

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    SorterTree S(pivot_chooser,num_entries);

    //For only testing quicksort

    // SorterTree S1=S;
    // cout<<"USING QUICK SORT"<<endl<<"UNSORTED"<<endl;
    // S1.printArray();
    // S1.Quicksort(0,S1.getLength()-1);
    // cout<<"SORTED"<<endl;
    // S1.printArray();


    cout<<"STORING PIVOTS IN TREES AND SORTING USING QUICKSORT"<<endl;
    S.printArray();
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    S.QuicksortWithBSTInsert(0,S.getLength()-1);
    cout<<endl<<"TREE OF PIVOTS"<<endl;
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    S.printBST();
    cout<<endl<<"SORTED ARRAY"<<endl;
    S.printArray();
    cout<<endl<<"TIME DURATION = "<<elapsed_seconds.count()*1000<<endl;
    cout<<"COMPARISONS = "<<S.getComparisons()<<endl;
    cout<<"IMBALANCE = "<<S.get_imbalance()<<endl;
    //more the imbalance more the time and number of comparisons needed
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
