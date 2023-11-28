#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

using namespace std;

int main(int argc, char** argv)
{
    //if(argc != 3)
    //{
      //cout<<"Incorrect number of arguments"<<endl;
     // exit(0);
    //}

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    //assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    SorterTree* results = new SorterTree(pivot_chooser,0) ;
    
    for( int i=0; i<num_entries; i++){// Takes in the input 
    
        int a, b;
        cin>>a>>b;
    	results->insertPivot(a,b);
    } 
 
    cout<<"👉️ After Sorting"<<endl;
 
    results->print();// prints the BinaryTree using quicksort
    results->printArray();// prints the array after sorting
    cout<<"comparison: "<<results->compare()<<endl; // prints the comparision length after sorting
    cout<<"Longest Path :"<<results->longest()<<endl;// prints the longest path of BST tree
    cout<<"Shortest Path :"<<results->shortest()<<endl;// prints the longest path of BST tree
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
