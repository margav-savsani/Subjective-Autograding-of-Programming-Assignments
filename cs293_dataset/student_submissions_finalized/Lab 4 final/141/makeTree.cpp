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

    int num_entries = atoi(argv[1]); // Number of journeys to enter -- useless for now (input taken from file)
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

    auto start = std::chrono::system_clock::now();

    // taking input from sample input
    ifstream infile;
    infile.open("sample-input.txt");

    Journey* journeys = new Journey[num_entries];
    int jc, price;
    int idx=0;
    while (infile >> jc >> price){
        journeys[idx].inputJourney(jc, price);
        idx++;
    }
    // cout << "Before sortertree construction" << endl;
    // sortertree constructed with array of journeys as user input. 
    SorterTree tree(journeys, idx, pivot_chooser);

    //tree.printArray();
   
    //tree.quickSort(0, idx-1);

    tree.QuicksortWithBSTInsert(0, idx-1);

    // cout << "QUICK SORT ENDS" << endl;

    //tree.printArray();
    tree.getTree()->printBST("");
    // printing the output

    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start;
    std::cout << "Imbalance : " << tree.getTree()->getImbalance() << std::endl;
    //std::cout << "Comparisons : " << tree.getComparisons() << std::endl;
    std::cout << "Running time : " << elapsed.count() << '\n';
}
