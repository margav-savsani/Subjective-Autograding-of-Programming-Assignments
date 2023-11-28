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
    SorterTree *s = new SorterTree(pivot_chooser,num_entries);

    for(int i =0 ; i < num_entries ;i++){                     //inserting all the elements
        int jc,price;
        cin >> jc >>price;
        s->insertelem(jc,price,i);
    }
    //s->printArray();
    std::chrono::time_point<std::chrono::system_clock> start, end;          //to check time elapsed during sorting
    start = std::chrono::system_clock::now(); 
    s->QuicksortWithBSTInsert(0,num_entries-1);     
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time Taken: " << elapsed_seconds.count() << "s\n";
    s->printArray();
    cout << s->get_comparisons() << endl;                                  //number of comparisons
    cout <<"\n";
    s->getTree()->printBST("");
    cout << s->getTree()->getImbalance() << endl;                          //imbalance in tree
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
