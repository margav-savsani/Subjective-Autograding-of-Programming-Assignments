#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <cstdlib>
#include <chrono>
#include <ctime>

using namespace std;

int main(int argc, char** argv)
{
    chrono::time_point<chrono::high_resolution_clock> start, end;
  
    start = chrono::high_resolution_clock::now();
  
   
  
    chrono::duration<double> elapsed_seconds = (end - start)*1000;
    time_t end_time = chrono::high_resolution_clock::to_time_t(end);
  

    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot
    SorterTree sort_b(pivot_chooser,num_entries);
    TreeNode array_[num_entries];
    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    for(int i=0 ; i <num_entries ; i++){
        cin >> array_[i].JourneyCode >> array_[i].price;
        
        sort_b.array[i].JourneyCode=array_[i].JourneyCode ;
        sort_b.array[i].price=array_[i].price ;
    }

    sort_b.QuicksortWithBSTInsert(0,num_entries-1);
    sort_b.printArray();
    cout << "Number of Comparisons : " << sort_b.getcomp() << endl;

    (sort_b.getTree())->printBST("");
    cout<< "Imbalance in the BST of pivots is : " << (sort_b.getTree())->getImbalance() << endl;
    end = chrono::high_resolution_clock::now();
      
    cout << "Time elapsed is: " << elapsed_seconds.count() << "ms\n";

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
