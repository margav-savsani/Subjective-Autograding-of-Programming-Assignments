#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>

using namespace std;

int main(int argc, char** argv)
{

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

    Journey* fake_arr = new Journey[num_entries];


    for (int i = 0; i < num_entries; i++){
        int journeyCode, price;
        
        cin >> journeyCode >> price;
        
        // To assign random elements instead of entering each values
        // journeyCode = 1 + (rand() % 100);
        // price = journeyCode;


        fake_arr[i] = Journey(journeyCode, price);
        
    }

    SorterTree* sorterTree = new SorterTree(pivot_chooser, num_entries, fake_arr);

    // sorterTree->printArray();

    // sorterTree->Quicksort(0, num_entries-1);

    // sorterTree->printArray();

    auto t1 = high_resolution_clock::now();

    sorterTree->QuicksortWithBSTInsert(0, num_entries-1);

    auto t2 = high_resolution_clock::now();

    // sorterTree->printArray();

    // sorterTree->printTree();

    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << ms_double.count() << "ms\n";

}
