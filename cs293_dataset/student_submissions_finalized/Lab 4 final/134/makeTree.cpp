#include <bits/stdc++.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

using namespace std;

void SorterTree::setarray(Journey *a){
    array = a;
    return;
}

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
    SorterTree* a;
    a = new SorterTree(pivot_chooser, num_entries);
    Journey arr[num_entries];
    cout << "give your entries (journeyCode, price):\n";
    for(int i=0; i<num_entries; i++){
        int x,y;
        cin >> x >> y;
        arr[i] = Journey (x,y);
    }
    a->setarray(arr);
    cout << "enough entries\n";
    cout << "This is the original array of JourneyCodes:\n";
    a->printArray();
    cout << endl << endl;
    cout<<"This is the sorted array of JourneyCodes:\n";
    a->QuicksortWithBSTInsert(0,num_entries-1);
    BST* bst=a->getTree();
    bst->printBST("");
    cout << "Imbalance" << bst->getImbalance() << endl;
    a->printArray();
    cout <<"\nThis is the number of comparitions occured:  " << a->returnComparisions() << endl; 
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
