#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

using namespace std;

int main(int argc, char** argv){
    if(argc != 3){
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    Journey *a = new Journey[num_entries];
    Journey *b = new Journey[num_entries];
    for (int i = 0; i < num_entries; i++){
        unsigned int j, p;
        cin >> j >> p;
        a[i] = Journey(j, p);
        b[i] = Journey(j, p);
    }
    SorterTree S = SorterTree(pivot_chooser, num_entries, a); //Creating a sorter tree function
    // S.Quicksort(0, num_entries - 1); //Quicksort the array
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> start2, end2;
    start2 = std::chrono::system_clock::now();
    S.Quicksort(0, num_entries -1);
    S.printArray(); // Valid choice of pivot chooser function
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout <<"TIME ELAPSED FOR SORT = "<<elapsed_seconds.count()*1000000<< " ms" << endl;

    S.QuicksortWithBSTInsert(0,num_entries-1);
    S.getTree()->printBST(" ");
    end2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end2 - start2;
    cout <<"TIME ELAPSED FOR BST = "<<elapsed_seconds2.count()*1000000<< " ms" << endl;

    cout <<"IMBALANCE OF THE TREE IS: " <<S.getTree()->getImbalance() <<endl;
    cout <<"THE NUMBER OF COMPARISONS: "<<S.getcomp() << endl;
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
}
