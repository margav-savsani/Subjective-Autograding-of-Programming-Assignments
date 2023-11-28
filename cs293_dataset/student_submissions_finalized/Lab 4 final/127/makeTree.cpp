#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

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
    
    SorterTree* sorter_tree=new SorterTree(pivot_chooser, num_entries);
    
    int journey_code, price, part_choice;
    Journey temp_journey[num_entries];

    cout<<"Which part do you want to test?\n";
    cin>>part_choice;

    cout<<"Give the list of journeys as a (journey code, price) pair\n";

    if(part_choice==1) {
        for(int i=0; i<num_entries; i++) {
            cin>>journey_code>>price;
            temp_journey[i]=Journey(journey_code, price, true);
        }

        sorter_tree->array=temp_journey;

    
        cout<<"Array before sorting:\n";
        sorter_tree->printArray();
        sorter_tree->Quicksort_new();
        cout<<"\nArray after sorting\n";
        sorter_tree->printArray();
    }

    else {
        for(int i=0; i<num_entries; i++) {
            cin>>journey_code>>price;
            temp_journey[i]=Journey(journey_code, price, true);
            (sorter_tree->tree)->insert(journey_code, price);
        }

        sorter_tree->array=temp_journey;

        cout<<"Array before sorting:\n";
        sorter_tree->printArray();
        sorter_tree->QuicksortWithBSTInsert_new();
        cout<<"\nArray after sorting\n";
        sorter_tree->printArray();
        cout<<"\nNumber of comparisons: "<<sorter_tree->getComparisons()<<"\n";
        cout<<"Imbalance: "<<sorter_tree->getImbalance()<<"\n";
    }

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
