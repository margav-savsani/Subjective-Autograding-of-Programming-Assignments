#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>

using namespace std;
using namespace std::chrono;
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

    SorterTree* s;
    s = new SorterTree(pivot_chooser,num_entries);

    Journey* arr = s->getArray();
    cout << "Enter the Journeycode and price in 1 line for a Journey: " << endl; 
    for(int i=0; i<num_entries; i++) {
        unsigned int code,price;
        cin >> code >> price;
        (arr[i])=Journey(code,price);
    }
    while(true) {
        string input;
        cout << ">>> ";
        cin >> input;
        if(input == "Q_SORT") {
            auto start = std::chrono::high_resolution_clock::now();
            s->Quicksort(0,num_entries-1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout<<duration.count()<<endl;
        }
        else if (input == "Q_BST_SORT") {
            auto start = std::chrono::high_resolution_clock::now();
            s->QuicksortWithBSTInsert(0,num_entries-1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout<<duration.count()<<endl;
        }
        else if (input == "PRINT") {
            s->printArray();
        }
        else if(input == "EXIT") {
            break;
        }
        else if(input == "PRINT_TREE") {
            (s->getTree())->printBST("");
        }
        else {
            cout << "~INVALID COMMAND~" << endl;
        }
    }
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
