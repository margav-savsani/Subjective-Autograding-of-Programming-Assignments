// To compile this program, run "g++ makeTree.cpp choose.o journey.cpp"

#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

using namespace std;

int main(int argc, char* argv[])
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

    SorterTree st(pivot_chooser, num_entries);
    cout << "Choose how you want to sort? 0 for 'Quicksort', 1 for 'BST' ..." << endl;
    bool choice;
    cin >> choice;
    if (!choice){
        auto start = std::chrono::system_clock::now();
        st.Quicksort(0, num_entries - 1);
        cout << "Comparisons: ";
        st.getComparisons();
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        cout << "Time taken (in milliseconds): " << elapsed_seconds.count() * 1000 << endl;
        st.printArray();
    }
    else{
        BST *tree = new BST();
        auto start = std::chrono::system_clock::now();
        st.QuicksortWithBSTInsert(tree, 0, num_entries - 1);
        cout << "Imbalance: ";
        st.getImbalance(tree);
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        cout << "Time taken (in milliseconds): " << elapsed_seconds.count() * 1000 << endl;
        tree->printBST("");
    }
    exit(0);
}
