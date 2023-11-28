#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include "journey.cpp"
#include <chrono>

using namespace std;

int main(int argc, char** argv)
{
    if(argc != 4)
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
    
    SorterTree sorter(pivot_chooser, num_entries);

    ifstream infile(argv[3]); // argv[3] = filename to take input from.
    sorter.load(infile);
    infile.close();

    bool withTree = true;
    std::cout << "Do you want the corresponding binary search tree as well?(0/1)\n";
    std::cin >> withTree;
    auto start = chrono::high_resolution_clock::now();    
    if (!withTree) {
        if (!sorter.Quicksort()){
            std::cout << "Runtime error: Invalid pivot passed to quicksort function." << std::endl;
            return 1;
        }
    }
    else{
        if (!sorter.QuicksortWithBSTInsert()){
            std::cout << "Runtime error: Invalid pivot passed to quicksort function." << std::endl;
            return 1;
        }
    }
    auto duration = chrono::high_resolution_clock::now() - start;
    std::cout << "\nSorted Array:\n\n";
    sorter.printArray();
    if (withTree){
        std::cout << "\nCorresponding tree:\n\n";
        sorter.printBST();
    }
    std::cout << "\nNumber of comparisons required: " << sorter.getNumComparisons() << std::endl;
    if (withTree) std::cout << "Imbalance of the tree: " << sorter.getTreeImbalance() << std::endl;
    std::cout << "Time taken: " << chrono::duration_cast<chrono::microseconds>(duration).count() << "us" << std::endl;
}
