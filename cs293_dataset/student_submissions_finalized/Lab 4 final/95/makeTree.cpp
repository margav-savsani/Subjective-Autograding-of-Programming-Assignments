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
    int code[num_entries],price[num_entries];
    for(int i=0;i<num_entries;i++){
        cin>>code[i]>>price[i];
    }
    Journey *r=new Journey[num_entries];
    
    for(int i=0;i<num_entries;i++){
       r[i].set_value(code[i],price[i]);
    }
    SorterTree *tr=new SorterTree(pivot_chooser,num_entries);
    tr->insert(r);
    tr->QuicksortWithBSTInsert(0,num_entries-1);
    tr->printArray();
    cout<<"comparsion: ";
   tr->print_comparsions();
   tr->print_bst();
  cout<<"imbalance: " <<tr->imbalance()<<endl;
   
   
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
