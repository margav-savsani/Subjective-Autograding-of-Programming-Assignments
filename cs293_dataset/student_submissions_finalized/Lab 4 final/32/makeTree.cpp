#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

using namespace std;

int main(int argc, char** argv)
{//freopen("sample-input.txt", "r", stdin);
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); 
    
    cout<<"Enter Journey Code and Price."<<endl;;
        
    SorterTree ST(pivot_chooser, num_entries);
    int j = 0;
    
    while(j < num_entries)
    {
        int JourneyCode, price;
        cin >> JourneyCode >> price ;        
        Journey J(JourneyCode, price);
        ST.array[j] = J;
	j++;
    }
    //swapJourneys(&S.array[2],&S.array[1]);
    //S.Quicksort(0,num_entries-1);
    
    cout<<"Array after sorting : "<<endl;
    
    ST.QuicksortWithBSTInsert(0,num_entries-1);
    ST.printArray();
    cout<<endl<<flush;
    ST.tree->printBST("");
    

    cout<<"No. of Comparisons = "<< ST.counter << endl;
    cout << "Imbalance = "<<ST.tree->getImbalance()<<endl;
    
   
    // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
