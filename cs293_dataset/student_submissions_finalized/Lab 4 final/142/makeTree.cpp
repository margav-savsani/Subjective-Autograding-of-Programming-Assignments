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
    
    SorterTree s;
    s(pivot_chooser,num_entries);//construct
    int i = 0;Journey*j;  //j= array of journeys in input
    while(i<num_entries){
        cin>>j[i]->JourneyCode>>j[i]->price;
        i++;
    }
 //   s->array = j;
 //   getSorterTree(s);
    int k=1;
    
    while(k){
        
        string input;
        cin>>input;
        if(!strcmp(input,'qsort')){
            sortquick(s,j,0,num_entries);
        }
        if(!strcmp(input,'BSTqsort')){
            QuicksortWithBSTInsert(0,num_entries);
        }
        cout << "enter '1' to continue, '0'to exit:";
        cin >> k;
    }
    
    

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
