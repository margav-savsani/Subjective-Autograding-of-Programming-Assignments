#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>

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
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    chrono::time_point<chrono::system_clock> start, end;  // for timming the entire code.
    

    SorterTree st(num_entries,pivot_chooser);
    start = chrono::system_clock::now();// start.
    if ( st.QuicksortWithBSTInsert(0,num_entries-1) ) { // for successful search 
        cout << "Quicksort has been successful"<<endl;// quicksort done with BST.
        st.printArray();
    }
    else cout << "Quicksort has been unsuccessful as pivot chosen was not in the array and does not partition the array" <<endl;
    // for unsuccessful search.
    
    end = chrono::system_clock::now();//end.
  
    chrono::duration<double> time_taken = end - start;  
    cout << "time taken: " << time_taken.count() << " seconds\n";
}
