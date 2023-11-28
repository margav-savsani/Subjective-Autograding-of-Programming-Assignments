#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>


using namespace std;

int main(int argc, char** argv)
{
    auto Start = chrono::steady_clock::now(); //timer starts
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl; //if we give more than 2 arguments
        exit(0);
    }

    int num_entries = atoi(argv[1]);   // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    int jc,pr; //journeycode and the corresponding price
    SorterTree a(pivot_chooser,num_entries);
    for(int i = 0;i<num_entries;i++){ //inserting into the array
        cin>>jc;
        cin>>pr;
        a.array[i].JourneyCode=jc;
        a.array[i].price=pr;
    }
    int start; 
    cin>>start;  //taking start as the input
    int finish;
    cin>>finish; //taking finish as the input
    cout<<"choose 1 to call QuickSort otherwise choose 2 to call QuicksortWithBSTInsert "<<endl;
    int choose;
    cin>>choose;    //enter 1 or 2
    if(choose==1){ //if we choose 1 array will be sorted and will be printed
        a.Quicksort(start,finish);
        a.printArray();
    }
    if(choose==2){  //if we choose 2 array will be sorted,pivots will be inserted into BST(not the repeated ones) and BST will be printed
        a.QuicksortWithBSTInsert(start,finish);
        a.print();
    }
    cout<<"cost of comparisions: "<<a.compare()<<endl; //prints the cost of comparisions
    cout<<"imbalance of the tree:"<<a.Imbalance()<<endl; //prints the difference between shortest path and the longest
    auto end = chrono::steady_clock::now();
    cout<<"time taken in milliseconds: "<<chrono::duration_cast<chrono::milliseconds>(end - Start).count()<<endl; //prints the time taken in milliseconds
    
//compile using g++ makeTree.cpp and run using ./a.out <num_entries> <pivot_chooser>
}
