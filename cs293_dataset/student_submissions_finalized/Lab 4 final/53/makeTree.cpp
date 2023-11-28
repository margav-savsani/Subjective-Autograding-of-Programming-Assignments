#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include<chrono>
using namespace std;
using namespace std::chrono;

//just compile this file and run to get the output

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

    SorterTree* sorter = new SorterTree(pivot_chooser,num_entries); //creating a new sortertree instance

    // srand(time(0));

    for (int i=0; i<num_entries; i++){
    int journeycode,price;
    // journeycode = rand()%100000; //used if many inputs are to be used
    // price = rand()%100000;
    cin >> journeycode >> price; //input the journey
    Journey* j = new Journey(journeycode,price);
    sorter->array[i] = *j; 
    } 

    // sorter->Quicksort(0,num_entries-1);
    

    auto t = chrono::high_resolution_clock::now(); // checking the journey
    sorter->QuicksortWithBSTInsert(0,num_entries-1);
    sorter->printArray();
    auto t1 = chrono::high_resolution_clock::now();
    cout << "Time in micro seconds: " << chrono::duration_cast<chrono::microseconds>(t1-t).count()<<endl;


    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
