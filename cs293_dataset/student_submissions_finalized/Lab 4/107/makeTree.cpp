#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <string>
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

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    int i=0;
    SorterTree *st= new SorterTree(num_entries, pivot_chooser);
    while(i<num_entries)
    {
      string nextInLine;
      getline(cin, nextInLine);
      split(s, ' ');
      unsigned int jc= stoi(parse[1]);
      unsigned int pc=stoi(parse[2]);
      i++;
    }
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
