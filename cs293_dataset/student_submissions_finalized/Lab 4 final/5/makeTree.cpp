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

    Journey arr[num_entries];

    // Input from user and store it in arr[]
    for(int i=0; i<num_entries ; i++)
    {
        int JourneyCode , price;
        cin >> JourneyCode >> price;
        Journey jrny(JourneyCode , price);

        arr[i] = jrny;
    }

    //make a sorter tree(A) on which we will use quicksort() and then print resulting array and total comparisons made in sorting.
    cout<<"\n\n\n--------------------------------------------------------------\n";
    cout<<"Quicksort on array of Journeys ==>\n\n";
    SorterTree A(arr, pivot_chooser , num_entries);
    bool sort = A.Quicksort(0, num_entries-1);
    bool printA = A.printArray();
    cout << "**Total comparisions: " << A.totalComparisons() << endl;
    cout<<"\n\n";


    // Make a sorter tree(B) where we will insert pivots into BST . Then get the tree using getTree() and print the resulting sorted array. Then print the BST tree and imbalance of BST.
    cout<<"Inserting pivots into BST\n";
    SorterTree B(arr, pivot_chooser , num_entries);
    bool BSTsort = B.QuicksortWithBSTInsert(0, num_entries-1);
    BST *BSTTree = B.getTree();
    TreeNode *rootOfBST = BSTTree->giveRoot();
    BSTTree->printBST("");
    cout << "\n**Imbalance: " << BSTTree->getImbalance() << endl;

    return 0;
}
