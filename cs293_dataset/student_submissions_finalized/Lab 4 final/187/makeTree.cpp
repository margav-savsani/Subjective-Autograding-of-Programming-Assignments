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

    assert(1<=pivot_chooser && pivot_chooser<= 4);
    cout << "1" << endl;
    cout << "Enter JourneyCode and price:" << endl;
     // Valid choice of pivot chooser function
    SorterTree S(pivot_chooser,num_entries);
    for(int i=0;i<num_entries;i++){
        int a,b;
        cin >> a;
        cin >> b;
        S.insertarr(i,a,b);
    }
    string input;
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    while(true){
    cin >> input;
    if(input == "QUICK_SORT"){
        S.Quicksort(0,num_entries-1);
    }
    else if(input == "BST_SORT"){
        S.QuicksortWithBSTInsert(0,num_entries-1);
    }
    else if(input == "PRINT"){
        S.printArray();
        cout << S.comp() << endl;
    }
    else if(input == "BST_PRINT"){
        S.getTree();
    }
    else if(input == "QUIT"){
        break;
    }
    }
    // Also rite code here to obtain different inputs as in the various parts of the question  
}
