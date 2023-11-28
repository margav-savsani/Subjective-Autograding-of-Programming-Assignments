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
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    int a,b;
    cin>>a>>b;
   SorterTree *s1=new SorterTree(a,b);
   int c,d;
   cin>>c>>d;
   s1->Insertjour(c,d);
   int e,f;
   cin>>e>>f;
   s1->Insertjour(e,f);
   int g,h;
   cin>>g>>h;
   s1->Insertjour(g,h);
   int i,j;
   cin>>i>>j;
   s1->Insertjour(i,j);
   int k,l;
   cin>>k>>l;
   s1->Quicksort(k,l);
   s1->printArray();
}
