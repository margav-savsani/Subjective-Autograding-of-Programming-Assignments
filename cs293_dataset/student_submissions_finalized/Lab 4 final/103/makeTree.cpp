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
    Journey array[num_entries];
    for(int i = 0; i < num_entries; i++){
        int code, price;
        cin >> code >> price;
        Journey newJourney(code, price);
        array[i] = newJourney;
    }

    SorterTree st(pivot_chooser, num_entries);
    st.array = array;
    cout << "-----Original Array-----" << endl;
    st.printArray();
    st.QuicksortWithBSTInsert(0, num_entries-1);
    cout << "-----Sorted Array-----" << endl;
    st.printArray();
    cout << "-----The Binary Search Tree-----" << endl;
    st.getTree()->printBST("");
    st.getTree()->calculatePathLengths();
    cout << "-----Other Details-----" << endl;
    cout << "Number of Comparions Required: " << Journey::numComparisonsTotal << endl;
    cout << "Imbalance Of The BST: " << st.getTree()->getImbalance() << endl;


    return 0;
}
