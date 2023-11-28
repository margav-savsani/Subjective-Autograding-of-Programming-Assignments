#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

using namespace std;

int main(int argc, char** argv){
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    SorterTree T(pivot_chooser, num_entries);
    cout<<"Enter the journeyCode and Price of each Journey as <JourneyCode:Price>"<<endl;
    for(int i=0; i<num_entries; i++){
        int journeycode,price;
        cout<<">>>";
        cin>>journeycode>>price;
        if(journeycode<0 || price<0) cout<<"invalid entry";
        T.addJourney(i,journeycode,price);
    }
    T.calling_QuickSort();
    T.printArray();
    T.QuicksortWithBSTInsert(0,num_entries-1);
    cout<<"Imbalance of root:"<<T.getTree()->getImbalance()<<endl;
}
