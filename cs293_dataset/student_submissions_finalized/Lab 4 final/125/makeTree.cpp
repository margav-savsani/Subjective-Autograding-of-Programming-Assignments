#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <chrono>
#include "sort.cpp"
using namespace std;

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }
    //freopen("sample-input.txt","r",stdin);
    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    SorterTree* list = new SorterTree(pivot_chooser,num_entries);
    for(int i = 0; i<num_entries; i++){
        int code, price;
        cin >> code >> price;
        list->insertPivot(code,price);
    }
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    list->QuicksortWithBSTInsert(0,num_entries-1);
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    list->getTree()->printBST("",false);
    list->printArray();
    cout << "Cost: ";
    list->printCost();
    cout << "Imbalance: ";
    cout << list->getTree()->getImbalance() << '\n';
    cout << "Time Taken to Sort: ";
    std::chrono::duration<double>time_taken = end - start;
    std::cout << time_taken.count()*1000 << endl;
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
