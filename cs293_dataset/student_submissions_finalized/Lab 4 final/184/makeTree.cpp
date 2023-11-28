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

     SorterTree *s=new SorterTree(pivot_chooser,num_entries);
    
    // s->insert(2,20);
    // s->insert(3,30);
    // s->insert(1,10);
    // s->insert(7,70);
    // s->insert(6,60);
    // s->insert(5,50);
    s->insert(1,10);
    s->insert(2,20);
    s->insert(3,30);
    s->insert(5,50);
    s->insert(7,70);
    s->insert(6,60);
    // //cout<<"harshith thop"<<endl;
    s->printArray();
    //cout<<"harshith thop"<<endl;
    //cout<<s->ind<<endl;
    s->Quicksort(0,s->ind-1);
    s->printArray();
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
