#include <stdlib.h>
#include <iostream>
#include <string>
#include <cassert>
#include "sort.cpp"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Incorrect number of arguments" << endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]);   // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1 <= pivot_chooser && pivot_chooser <= 4); // Valid choice of pivot chooser function

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

    // Initialising the tree
    SorterTree sorter(pivot_chooser, num_entries);

    // Loading the data from the input file
    string filename;
    cout << "Write the filename storing the data: ";
    cin >> filename;
    sorter.make_array(filename);

    // Sorting and inserting the array into BST simultaneously
    cout << "Array before sorting was : " << endl;
    sorter.printArray();
    bool sorted = sorter.QuicksortWithBSTInsert(0, num_entries - 1);
    if (sorted)
    {
        // Only if sorting was done correctly, that is true was returned we print the sorted array \
        and the tree obtained.
        cout << "\n Array after sorting is : " << endl;
        sorter.printArray();
        cout << "\nTotal comparisons were: " << sorter.get_comparisons() << endl;

        (sorter.get_BST_Tree())->printBST("");

        cout << "\nThe Imbalance in tree is: " << (sorter.get_BST_Tree())->getImbalance() << endl;
    }
    else
    {
        cout << "SORRY, your pivot index generator is faulty, please correct it. :(" << endl;
    }
}