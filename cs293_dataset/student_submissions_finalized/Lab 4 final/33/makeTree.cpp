#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "updated_sort.cpp" 
#include<vector>

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

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function

    BST *k ;
    class SorterTree x(pivot_chooser,num_entries) ;
    for(int m=0;m<num_entries;m++){
        cin>>(x.array)[m].JourneyCode>>(x.array)[m].price ;
    }
    k = x.tree ;

    cout<<endl ; 
    cout<<"The given unsorted array is : "<<endl ;
    x.printArray();
    cout<<endl ;

    cout<<"Sorting starts along with insertion into BST :) "<<endl;
    x.QuicksortWithBSTInsert(0,num_entries-1,x.array);
    cout<<endl;
    cout<<"The sorted array will be : "<<endl;
    x.printArray();
    cout<<endl ;
    x.printComparisons();
    cout<<endl;
    cout<<endl;

   // x.QuicksortWithBSTInsert(0,num_entries-1);

    k->printBST("") ;
    // k->getLong(k->root);
   // k->getShort(k->root);
    cout<<endl;
    cout<<endl;
    cout<<"The imbalance of the BST is : ";
    k->getImbalance();
    cout<<endl ;
   
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
