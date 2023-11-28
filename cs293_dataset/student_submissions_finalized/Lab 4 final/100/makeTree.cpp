#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <stdexcept>
#include <cstdlib>
#include <chrono>


using namespace std;
using namespace std::chrono;
bool isPresent(Journey* X,int j,unsigned int code){
    if(j==0)return false;
    for(int i=0;i<j;i++){
        if(X[i].getJourneyCode()==code)return true;
    }
    return false;
}

int main(int argc, char** argv)
{
    auto start = std::chrono::high_resolution_clock::now();
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }
    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<4); // Valid choice of pivot chooser function
    cout<<"Welcome"<<endl;
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    unsigned int jcode,price,i=0;
    Journey* A;
    A=new Journey[num_entries];
    cout<<"Enter "<<num_entries<<" different journey entries"<<endl;
    while(i<num_entries){
        cin>>jcode>>price;
        if(isPresent(A,i,jcode))continue;
        A[i]=Journey(jcode,price);
        i++;
    }
    SorterTree *sorttree=new SorterTree(A,pivot_chooser,num_entries);
    cout<<"Here is your original array:"<<endl;
    sorttree->printArray();
    cout<<"\n";
    sorttree->QuicksortWithBSTInsert(0,num_entries-1);
    cout<<"\nHere is your sorted array: "<<endl;
    sorttree->printArray();
    cout<<"\nHere is corresponding tree:"<<endl;
    sorttree->printTree();
    cout<<"\nImbalance at root is: "<<sorttree->getTree()->getImbalance()<<endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"\nTotal time: " <<duration.count()<<endl;
    // Add functionality to time your code (chrono may be helpful here)

}
