#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <fstream>
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
    
    SorterTree t1(pivot_chooser,num_entries);

    ifstream file;
    file.open("sample-input.txt");
    string input;
    while(file>>input){
        int jc = stoi(input);
        file>>input;
        int pr = stoi(input);
        t1.inser(jc,pr);
    }
    t1.printArray();
    t1.Quicksort(0,num_entries-1); 
    t1.printArray();
    t1.QuicksortWithBSTInsert(0,num_entries-1);
    t1.print();
    t1.change();
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
