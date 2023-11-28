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

    assert(1<=pivot_chooser && pivot_chooser<4); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    SorterTree* s=new SorterTree(pivot_chooser,num_entries);
    int i=0;unsigned int code;unsigned int cost; 
    while(i<num_entries){cin>>code>>cost;Journey j(code,cost);s->array[i]=j;i=i+1;}
    s->QuicksortWithBSTInsert(0,num_entries-1);  //sorts array with inserting pivots in BST
    cout<<"SORTED ARRAY: "<<endl;
    s->printArray();               //printing sorted array
    cout<<"Total cost of comparisions: ";
    s->printComparisons();       //printing total no.of comparisions
    cout<<endl; 
    cout<<"BST : "<<endl; 
    s->printbst();               //print BST
    cout<<"Imbalance in BST:";
    s->printimbalance();         //print imbalance
    cout<<endl;
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
 return 0;
}
