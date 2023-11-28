#include <cassert>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <chrono>
#include "sort.cpp"

//chrono for depicting time of computation.
using namespace std::chrono;
using namespace std;

/* 
    **************Code to Run****************
        g++ -g -c choose.cpp
        g++ -g -c journey.cpp
        g++ -g -c makeTree.cpp
        g++ -g -o makeTree choose.o journey.o makeTree.o
        ./makeTree $1 $2 
    ****************xxxxxxxxx**************
    Followed by $1 entries of JourneyCode, Price Pairs.
*/

//This function checks if the journeycode-price input given
//is already present in the array or not. If journey code is
//present then the input is not accepted.
bool different(Journey* array, unsigned int a, int l){
    for(int i=0;i<l;i++){
        if(array[i].getJourneyCode() == a) return false;
    }
    return true;
}

//Main function
int main(int argc, char** argv){
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function

    //Initialising Sorter tree with pivot_chooser function code, number of entries
    SorterTree sorterTree(pivot_chooser,num_entries);

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question

    // allocating dynamic array of Size num_entries using malloc()
    Journey* array = (Journey*)malloc(sizeof(Journey) * num_entries);
 
    cout << "Please enter " << num_entries << " number of entries below\n";
    // calling constructor for each index of array
    for (int i = 0; i < num_entries; i++) {
        unsigned int a,b;
        do{
            cin >> a >> b;
        }
        while(!different(array,a,i));
        array[i] = Journey(a,b);
    }

    cout << "Thankyou for entering " << num_entries << " entries!\n";

    //Setting array variable of Sorter Tree
    sorterTree.setArray(array);

    //Printing the unsorted array
    cout << "Init array==>\n";
    sorterTree.printArray();

     // Add functionality to time your code (chrono may be helpful here)
    auto start = std::chrono::high_resolution_clock::now();
    //Sorting using QuickSort and also inserting in tree.
    sorterTree.QuicksortWithBSTInsert(0,num_entries-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start); //Time in milliseconds
    cout << "Total time taken for Quick Sort Computation: " << duration.count() << " microseconds" << endl;
    
    //Printing finally sorted array
    cout << "Final array==>\n";
    sorterTree.printArray();

    //Printing the final tree
    cout << "BST==>\n";
    sorterTree.printTree();

    //Printing the imbalance of the tree, that is the imbalance at the root node.
    cout << "Imbalance at root node is: " << sorterTree.getTree()->getImbalance() << endl;
}
