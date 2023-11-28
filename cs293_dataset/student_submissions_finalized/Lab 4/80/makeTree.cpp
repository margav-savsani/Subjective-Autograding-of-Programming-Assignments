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
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair

    SorterTree my_tree(pivot_chooser, num_entries);

    Journey* j_arr= new Journey[num_entries];

    int j_code=0, j_price=0;

    for (int i = 0; i < num_entries; i++){
        cin >> j_code >> j_price;
        Journey j(j_code, j_price);
        j_arr[i] = j;
    }
    my_tree.insertToQueue(j_arr);
    my_tree.Quicksort(0, num_entries-1);
    my_tree.printArray();




    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
