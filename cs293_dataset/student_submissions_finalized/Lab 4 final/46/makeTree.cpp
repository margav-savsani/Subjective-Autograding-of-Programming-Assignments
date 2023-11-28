#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <chrono>
#include <ctime>
#include "sort.cpp"

using namespace std;

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    std::chrono::time_point<std::chrono::system_clock> start, end;
    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    
    SorterTree* st;
    st=new SorterTree(pivot_chooser,num_entries);

    cout << "Enter the (code,price) pair one per line: " << endl; // to make this program interactive
    for(int i=0; i<num_entries; i++) {
        unsigned int code,price;
        cin >> code >> price;  // taking input from the user
        Journey* tmp = st->getArray();
        (tmp[i])=Journey(code,price); // storing the pair in the array
    }
    while(true) {
        string s;
        cout << ">>> ";
        cin >> s;
        if(s == "Q_SORT") {
            start = std::chrono::system_clock::now(); // adding time functionality to the code
            st->Quicksort(0,num_entries-1);
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;
            std::cout << "elapsed time: " << elapsed_seconds.count() << endl;
        }
        else if (s == "BST_SORT") {
            start = std::chrono::system_clock::now(); // adding time functionality to the code
            st->QuicksortWithBSTInsert(0,num_entries-1);
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;
            std::cout << "elapsed time: " << elapsed_seconds.count() << endl;
        }
        else if (s == "PRINT") {
            st->printArray(); // printing the array
        }
        else if (s == "TREE") {
            st->printTree(); // printing the tree of pivots
        }
        else if (s == "COMP") {
           cout << st->get_comparisions() << endl; // number of comparisions done while sorting
        }
        else if(s == "EXIT") {
            break;  // to exit the program
        }
        else {
            cout << "INVALID COMMAND :/" << endl;
        }
    }
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
