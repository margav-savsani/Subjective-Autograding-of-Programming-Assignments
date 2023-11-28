#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
using namespace std;

// Name        : Atishay Jain
// Roll Number : 210050026
// Instruction for compiling and running the code:
//          g++ makeTree.cpp
//          ./a.out <number of journeys>  <choice for choose function>
// My codes were giving errors of redefinition if I was using 
// linking of object modules, but they are running absolutely perfect
// in the above way. So, kindly please run the code in this way.


int main(int argc, char** argv) {

    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]);                // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]);              // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4);   // Valid choice of pivot chooser function

    SorterTree data(pivot_chooser,num_entries);     
    int code, price, choiceOfUSer;

    cout << "Input (0) for QuickSort or (1) for QuickSort with BST : " << endl;     // Ask User for only Quicksort
    cin >> choiceOfUSer;                                                            // Or Quicksort with BST
    assert(choiceOfUSer<=1 && choiceOfUSer >= 0);   // Check for valid choice given by user

    for(int i = 0; i < num_entries; i++){           // Taking input of Journey Data
        cout << "Provide Journey Code of Journey " << i+1 << ": ";
        cin >> code;
        cout << "Provide Price of Journey " << i+1 << "       : ";
        cin >> price;
        Journey input(code,price);
        data.insertNewJourney(input,i);
    }
    cout << "------------------------------------------\n";
    cout << "Journey Data Provided : " << endl;
    data.printArray();                               // Displaying the data provided

    if(choiceOfUSer == 0){
        data.Quicksort(0,num_entries-1);
        cout << "------------------------------------------\n";
        cout << "Journey Data (after QuickSort) : " << endl;
        data.printArray();
    }

    else if(choiceOfUSer == 1){
        data.QuicksortWithBSTInsert(0,num_entries-1);
        cout << "------------------------------------------\n";
        cout << "Journey Data (after QuickSort) : " << endl;
        data.printArray();
        cout << "Comparisons performed : " << data.comparisonsDone() << endl;
        data.getTree()->printBST("",false);
        cout << "Imbalance in the tree : " << data.getTree()->getImbalance() << endl;
    }
}
