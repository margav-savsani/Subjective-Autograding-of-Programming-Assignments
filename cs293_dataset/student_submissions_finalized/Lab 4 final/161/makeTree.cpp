#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

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
    // int d;
    // cout<<"to test for part one press 0 else press 1 ";
    // cin>>d;
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // if(!d){
        SorterTree* ST = new SorterTree(pivot_chooser, num_entries);  
        ST->Quicksort(0,num_entries-1);
        ST->printArray();
    // }
    // else{
        // Also write code here to obtain different inputs as in the various parts of the question
        SorterTree* ST2 = new SorterTree(pivot_chooser, num_entries);
        ST2->QuicksortWithBSTInsert(0, num_entries-1);
        int total_cost = ST2->getComparisons();
        cout<<"The number of comparisons made are - "<<total_cost<<endl;

        
        int imb = ST2->getImbalanceOfRoot();
        cout<<"The imbalance is "<<imb<<endl;
        ST2->getTree();
    // }
    
    
    // Add functionality to time your code (chrono may be helpful here)

}
