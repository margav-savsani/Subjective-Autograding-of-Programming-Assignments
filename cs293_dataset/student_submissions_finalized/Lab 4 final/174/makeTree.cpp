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
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    
    SorterTree s(pivot_chooser,num_entries);
    cout<<"enter 0 to sort using part-1 and 1 to sort using part-2"<<endl;
    int c;
    cin>>c;
    cout<<"give input:"<<endl;
    for(int i=0; i<num_entries; i++){
        int jc, pr;
        cin>>jc>>pr;
        s.input(jc,pr,i);
    }
    cout<<"your array before sorting:"<<endl;
    s.printArray();
    cout<<endl;
    if(c==0){
        s.Quicksort(0,num_entries-1);
        cout<<"your array after sorting:"<<endl;
        s.printArray();
        cout<<endl;
    }
    if(c==1){
        s.QuicksortWithBSTInsert(0, num_entries-1);
        cout<<"your array after sorting:"<<endl;
        s.printArray();
        cout<<endl;
        cout<<"binary tree formed:"<<endl;
        s.print_tree();
        cout<<endl;
        cout<<"imbalance : "<<s.imbal()<<endl;
    }
    cout<<"no. of comparisons : "<<s.num_compar()<<endl;
}
