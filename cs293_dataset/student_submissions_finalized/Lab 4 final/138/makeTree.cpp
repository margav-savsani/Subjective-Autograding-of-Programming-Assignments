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
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    
    //initialising the sorter_tree
    SorterTree sort_tree (pivot_chooser,num_entries);

    //inserting all entries in the tree
    sort_tree.insert();

    //printing the array before comparison
    cout<<endl<<"Array before comparison"<<endl<<endl;

    //sorting the array
    sort_tree.printArray();
    
    //if the tree becomes sorted
    if(sort_tree.QuicksortWithBSTInsert(0,num_entries-1)){
        cout<<endl<<"Array after sorting"<<endl<<endl;
        //printing the sorted tree
        sort_tree.printArray();

        //printing the number of comparisons done
        cout<<"The number of comparisons are "<<sort_tree.get_comparisons()<<endl;

        //getting the pointer to the tree
        BST* tre=sort_tree.get_tree();

        //printing the tree
        tre->printBST("");
        
        //printing the imbalance
        cout<<"The imbalance in the tree is: "<<tre->getImbalance()<<endl;
    }
}
