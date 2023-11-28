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

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function

    if(num_entries<1) // no journey
      exit(0);
    int i=0;
    SorterTree *st=new SorterTree(pivot_chooser, num_entries);
    while(i<num_entries)
    {
      // Take input from user
      unsigned int jc;
      unsigned int pc;
      cin >> jc >> pc;
      st->insertJourney(jc, pc);
      i++;
    }
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    if(st->QuicksortWithBSTInsert(0, num_entries-1))  // If valid pivots are chosen
    {
      end = std::chrono::system_clock::now();
      std::chrono::duration<double> elapsed_seconds = (end - start);
      cout<<"Total time elapsed: "<<elapsed_seconds.count()<<endl;
      cout<<"Total number of comparisions: "<<st->getComparisions()<<endl;
      st->printArray();
      cout<<"Imbalance: "<<(st->getTree())->getImbalance()<<endl;
      (st->getTree())->printBST("");
    }
    else
    {
      end = std::chrono::system_clock::now();
      cout<<"Couldn't complete partitioning due to bad pivot"<<endl;
    }
}
