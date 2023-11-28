#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>

using namespace std;

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function

    SorterTree *a=new SorterTree(pivot_chooser, num_entries);
    for(int i=0; i<num_entries; i++){
        int c, b;
        cin>>c>>b;
        Journey x(c, b);
        a->array[i]=x;
    }
    cout<<"Enter 1 for quicksort and 2 for quicksort with bst"<<endl;
    int enter;
    cin>>enter;
    int comp1=0;
    int comp2=0;
    if(enter==1){
        auto start =chrono::steady_clock::now();
        a->Quicksort(0, num_entries-1, comp1);
        auto end =chrono::steady_clock::now();
        cout<<"Number of comparisons: "<<comp1<<endl;
        cout<<"Time: "<< chrono::duration_cast<chrono::nanoseconds>(end-start).count()<<endl;
        a->printArray();
    }
    else if(enter==2){
        auto start1 =chrono::steady_clock::now();
        bool quickSort;
        quickSort=a->QuicksortWithBSTInsert(0, num_entries-1, comp2);
        auto end1 =chrono::steady_clock::now();
        cout<<"Number of comparisons: "<<comp2<<endl;
        cout<<"Time: "<<chrono::duration_cast<chrono::nanoseconds>(end1-start1).count() <<endl;
        if(quickSort)
            cout<<"Imbalance: "<<a->imbalance()<<endl;
            a->tree->printBST("", false);
        a->printArray();
    }
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
