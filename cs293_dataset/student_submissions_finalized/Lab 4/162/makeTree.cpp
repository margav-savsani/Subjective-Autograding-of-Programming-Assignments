#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.h"

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

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    
    // SorterTree* st = new SorterTree(pivot_chooser,num_entries);
    // Journey* arr = new Journey[num_entries];
    // int i = 0;
    // while(num_entries)
    // {
    //     int JourneyCode,price;
    //     cout<<">>";
    //     cin>>JourneyCode>>price;
    //     Journey j(JourneyCode,price);
    //     arr[i] = j;
    //     num_entries--;
    // }

    // st->insert(arr);
    // st->Quicksort(0,num_entries-1);
    // st->printArray();

    // Journey* j = choose_one(arr,0,num_entries-1);
    // cout<<j->getJourneyCode()<<endl;
    


    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
