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

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    
    SorterTree st(pivot_chooser, num_entries);
    for(int i=0; i<num_entries; i++)
    {
        int code, price;
        cin >> code >> price;
        st.addJourney(code, price, i);
        cout << "READ " << code << " " <<price << endl;
    }

    cout << endl << "Before quicksort" << endl;
    st.printArray();
    if(!st.QuicksortWithBSTInsert(0, num_entries-1))
    {
        cout << "Incorrect choose function" << endl;
        return 0;
    }
    cout << endl << "After quicksort" << endl;
    st.printArray();
    cout << endl << "Number of comparisons done: " << st.comparisons << endl;

    cout << endl << "BST formed:" << endl;
    st.insElem();
    st.tree->printBST("");
    cout << endl << "The imbalance in the tree is: " << st.tree->getImbalance() << endl;
}
