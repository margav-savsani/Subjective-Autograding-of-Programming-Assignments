#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>

using namespace std;

int main(int argc, char** argv){
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    SorterTree* A=new SorterTree(pivot_chooser,num_entries);
    SorterTree* B=new SorterTree(pivot_chooser,num_entries);
    int i =0;
    while(i<num_entries){
        int a,b;
        cin>>a>>b;
        A->arr()[i]=Journey(a,b);
        B->arr()[i]=Journey(a,b);
        i++;
        }
    cout<<"sorting without inserting"<<endl;
    auto start = chrono::steady_clock::now();
    A->Quicksort(0,num_entries-1);
    auto end = chrono::steady_clock::now();
    cout<<chrono::duration_cast<chrono::milliseconds>(end-start).count()<<"ms"<<endl;
    cout<<"comparisons: "<<A->comp()<<endl;
    A->printArray();
    cout<<"sorting with inserting"<<endl;
    B->QuicksortWithBSTInsert(1,num_entries-2);
    B->getTree();
    B->getTree()->printBST("");
	cout<<"Imbalance ="<<B->getTree()->getImbalance()<<endl;
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
