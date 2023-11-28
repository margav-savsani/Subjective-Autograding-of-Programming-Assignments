/*

                To check the code, use the following command:

                        g++ makeTree.cpp && ./a.out <no_of_entries> <pivot_choice>

                 
*/


#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <chrono>

#include "sort.cpp"

using namespace std;

int main(int argc, char** argv)
{
    srand(3);


    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    
    SorterTree st(pivot_chooser, num_entries);

    cout << "no of entries: " << num_entries << endl;
    cout << "pivot_choice: " << pivot_chooser << "\n\n";

    for(int i=0; i<num_entries; i++){
        cout << "Please enter Journey Code and Price for " << i+1 << "th entry: ";
        int jc, p;
        cin >> jc >> p;

        // jc = p = num_entries-i;
        // jc = p = rand()%num_entries;

        st.insertPair(jc, p);
        cout << endl;
    }


    auto start = chrono::steady_clock::now();

    cout << endl;
    cout << "INITIALLY ----------------\n";
    st.printArray();


    st.QuicksortWithBSTInsert(0, num_entries-1);
    cout << endl;
    cout << "AFTER QUICKSORT----------- \n";
    st.printArray();
    cout << "\nTREE \n\n";
    st.tree->printBST("");
    cout << "\nImbalance : " << st.tree->getImbalance() << endl;

    auto end = chrono::steady_clock::now();
    cout << "Time elasped: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds"<<endl;

}
