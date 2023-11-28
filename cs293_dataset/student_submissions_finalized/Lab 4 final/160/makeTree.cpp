#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <chrono>
#include "sort.cpp"

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

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    Journey arr[num_entries];
    int a,b;
    auto start = high_resolution_clock::now();
    for(int i=0;i<num_entries;i++){
    cin>>a>>b;
    Journey temp(a,b);arr[i]=temp;
    }
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    BST *tr;
    SorterTree st(pivot_chooser,num_entries);
    st.QuicksortWithBSTInsert(0,num_entries-1,arr);
    cout<<"Yes"<<endl;
    tr=st.getTree();
    tr->printBST("");
    cout<<(tr->getImbalance())<<endl;
    cout<<st.comp()<<endl;
    // Add functionality to time your code (chrono may be helpful here)
auto stop = high_resolution_clock::now();
auto duration = duration_cast<milliseconds>(stop - start);
cout << "Time taken by function: "<< duration.count() << " milliseconds" << endl;
}
