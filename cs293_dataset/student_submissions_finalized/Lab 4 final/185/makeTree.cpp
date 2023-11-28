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

    
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    int code, price;

    Journey *J;
    
    for(int i=0; i<num_entries; i++){
        cin >> code >> price;
        //Journey J(code, price);
       //Sortree->array[i] = J;
       //Sortree->insertJ(code,price,i);
        J[i] = Journey(code, price);
        //Sortree->array[i].JourneyCode = code;
        //Sortree->array[i].price = price;

    }
    SorterTree* Sortree = new SorterTree(pivot_chooser, num_entries,J);

    //ifstream file("sample-input.txt");


    Sortree->Quicksort(0,num_entries-1);
    Sortree->printArray();
    cout<<"Cost of comparisons = "<< Sortree->comparisons << endl;
    //Sortree->QuicksortWithBSTInsert(0,num_entries-1);
    // Sortree->getTree();
    //cout<<"Imbalance = "<< Sortree->getTree()->getImbalance()<<endl;

    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
}
