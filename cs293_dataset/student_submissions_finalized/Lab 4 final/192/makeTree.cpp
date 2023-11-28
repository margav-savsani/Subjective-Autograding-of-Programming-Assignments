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

    SorterTree * sorterTree = new SorterTree(pivot_chooser, num_entries);

    
    int JourneyCode;
    int price;
    bool put = false;

    cout << "Enter the Journeys to be inserted in the array" << endl;
    
    for (int i = 0; i < num_entries; i++){

        cin >> JourneyCode >> price;
        put = sorterTree->insertArray(JourneyCode, price);
        

    }

    cout << " Array Before Sorting---> " << endl;
    sorterTree->printArray();

    cout << endl;

    

    sorterTree->QuicksortWithBSTInsert(0, num_entries-1);

    cout << "Array after sorting--->" << endl;
    sorterTree->printArray();


    cout << endl;
    cout << "Number of comparisons: " << sorterTree->getComparisons() << endl;
    cout << endl;


    cout << endl;
    sorterTree->getTree()->printBST("");
    cout << "Imbalance of the tree: " << sorterTree->getTree()->getImbalance() << endl;




    
    
   return 0;

}
