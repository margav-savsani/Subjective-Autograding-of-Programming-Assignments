#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.h"
#include "journey.h"
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

//Conclusions
//As the number of comparisons increase, the time also increase

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
    int ans;
    cout<<"Choose if you want to do QuickSort(0) or Quicksort(1) with BSTInsert?"<<endl;
    cin>>ans;

    SorterTree* st = new SorterTree(pivot_chooser,num_entries);
    Journey* arr = new Journey[num_entries];
    int i = 0;
    while(num_entries)
    {   
 
        int JourneyCode,price;
        // cout<<;
        cin>>JourneyCode>>price;
        Journey j(JourneyCode,price);
        arr[i] = j;
        num_entries--;
        i++;
    }
    st->insert(arr);
    if(!ans)
    {
   
    auto start = std::chrono::high_resolution_clock::now();
    cout<<"Sort Sucessful? "<<st->Quicksort(0,i-1)<<endl;
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    st->printArray();
    cout<<"Time Taken:" <<duration.count() << endl;
    cout<<"Comparisons: "<<st->totalComparisons()<<endl;
    }
    else
    {
        auto start = std::chrono::high_resolution_clock::now();
        cout<<"Sort Sucessful? "<<st->QuicksortWithBSTInsert(0,i-1)<<endl;
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
    
        st->printArray();
        cout <<"Time Taken:" <<duration.count() << endl;
        cout<<"Imbalance: "<<st->getTree()->getImbalance()<<endl;
        cout<<"Comparisons: "<<st->totalComparisons()<<endl;

        cout<<"Do you want to print the tree? press 0 for No"<<endl;
        cin>>ans;
        if(ans)
        {
            st->getTree()->printBST("",false);

        }
    }
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
