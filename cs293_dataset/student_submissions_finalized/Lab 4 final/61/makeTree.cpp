#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
 #include <fstream>
#include<vector>
#include<chrono>
using namespace std;
using namespace std::chrono;

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }
    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4);
   // Valid choice of pivot chooser function
      auto start = std::chrono::high_resolution_clock::now();    
    SorterTree *st= new SorterTree(pivot_chooser,num_entries);
    int c,p;
    ifstream infile;
    infile.open("sample-input.txt");
    while(infile >> c >> p ){
        struct Journey entry(c,p); 
        st->insert(entry);         
    }
    //st->Quicksort(0,num_entries-1);
    st->QuicksortWithBSTInsert(0,num_entries-1);
    st->printArray();
    st->printTree();
    cout<<"Comparisons:"<<st->getcomp()<<endl;
    cout<<"Imabalance:"<<st->getTree()->get_imbalance()<<endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"Time:" << duration.count() << endl;
        // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
