#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
#include "sort.cpp"

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
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    Journey* jour=new Journey[num_entries];
    for(int i=0; i<num_entries;i++){
        unsigned int price, Journeycode;
        cin>>Journeycode>>price;        
        jour[i]=Journey(Journeycode,price);
    }

    // Also write code here to obtain different inputs as in the various parts of the question
    SorterTree S(pivot_chooser,num_entries,jour); 
    
    auto start = std::chrono::high_resolution_clock::now(); 

    S.QuicksortWithBSTInsert(0,num_entries-1);    
    S.printArray();
    S.getTree()->printBST("");  
    //S.getTree()->remove(4,4);
    //cout<<"After deleting (4,4)"<<endl;
    // S.getTree()->printBST("");
    cout<<endl;
    cout<<"Imbalance: "<<S.getTree()->getImbalance()<<endl; 
    cout<<endl;

    auto stop = high_resolution_clock::now();    
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time: "<<duration.count() << endl;
    // Add functionality to time your code (chrono may be helpful here)
}
