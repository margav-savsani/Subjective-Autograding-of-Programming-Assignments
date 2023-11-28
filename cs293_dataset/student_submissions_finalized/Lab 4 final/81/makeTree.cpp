#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>

using namespace std;
using namespace std::chrono;



int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    SorterTree* S = new SorterTree(pivot_chooser,num_entries);
	SorterTree* S1 = new SorterTree(pivot_chooser,num_entries);
    for(int i=0;i<num_entries;i++){
		unsigned int a,b;
		cin>>a>>b;
		S->array[i]=Journey(a,b);
		S1->array[i]=Journey(a,b);
	}
	cout<<"PART I "<<endl;
	auto start = high_resolution_clock::now();
    S->Quicksort(0,num_entries-1);
	auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
	cout<<"Elapsed time in microseconds: "<<duration.count()<<"us"<<endl;
	cout<<"Number of comparisions: "<<S->getComparisions()<<endl;
	S->printArray();
    cout<<"PART II"<<endl;
	S1->QuicksortWithBSTInsert(0,num_entries-1);
	S1->getTree()->setroot();
    S1->getTree()->printBST("");
	cout<<"Imbalance in tree :"<<S1->getTree()->getImbalance()<<endl;
	
}

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)


