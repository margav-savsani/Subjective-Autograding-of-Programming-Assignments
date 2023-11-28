#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.h"
#include <bits/stdc++.h>
#include <chrono>    

using namespace std;
// #include "journey.cpp"


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


    SorterTree* st = new SorterTree(pivot_chooser, num_entries);

    // st->initWithRandomVals();
 
    //Write your code here to accept input of journeys, input one per line as a (code, price) pair
    for (int i = 0; i < num_entries; i++){
        int JC, price;
       
        cin >> JC >> price;
        st->insert(JC, price, i);
    }
    
    st->QuicksortWithBSTInsert(0, num_entries-1);
    st->printTreeData();

    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    std::chrono::time_point<std::chrono::system_clock> start, end;  
    start = std::chrono::system_clock::now();

    st->Quicksort(0, num_entries-1);
    st->printArray();

    end = std::chrono::system_clock::now();
  
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
