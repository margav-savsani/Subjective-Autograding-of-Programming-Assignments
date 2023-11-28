#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <string>

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
    
    SorterTree s(pivot_chooser, num_entries);
    for(int i=0; i>=0; i++){
        char input[32];
        cout << ">>> ";
        cin >> input;
        if(strcmp(input,"QUIT")==0){
            break;
        }
        if(strcmp(input,"INS")==0){
            int j, p;
            cin >> j >> p;
            Journey q(j,p);
            s.insertJourney(j,p);
        }
        if(strcmp(input,"printArr")==0){
            s.printArray();
        }
        if(strcmp(input,"sort")==0){
            s.Quicksort(0,s.getTail()-1);
        }
        if(strcmp(input,"sortBST")==0){
            s.QuicksortWithBSTInsert(0,s.getTail()-1);
        }
        if(strcmp(input,"printBST")==0){
            s.getTree()->printBST("");
        }
        if(strcmp(input,"Imbalance")==0){
            cout << "TreeImbalance: " << s.getTree()->getImbalance() << endl; 
        }

    }

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
