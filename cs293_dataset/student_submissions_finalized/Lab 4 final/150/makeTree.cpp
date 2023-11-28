#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>

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

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    SorterTree*s = new SorterTree(pivot_chooser,num_entries);
    for (int i=0 ; i< num_entries;i++){
        int JourneyCode,price;
        cin >> JourneyCode >> price;
        s->insertJourney(JourneyCode,price);
    }
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    s->QuicksortWithBSTInsert(0,num_entries-1);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    s->getTree()->printBST("");
    s->printArray();
    cout << "IMBALANCE:"<<s->getTree()->getImbalance()<<endl;
    cout << "NO OF COMPARISON " << s->getcomparison()<<endl;
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
