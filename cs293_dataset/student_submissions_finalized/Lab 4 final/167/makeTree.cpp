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

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    
       int t,i=0;
       t=num_entries;
       SorterTree p(pivot_chooser,num_entries);
	while(t!=0){
		int JourneyCode;
		int price;
		cin >> JourneyCode;
		cin >>price;
		Journey k(JourneyCode,price);
		p.arrinsert(i,k);
		i++;	
		t--;	
		
     }
     p.QuicksortWithBSTInsert(0,num_entries-1);
     cout<<"Quicksortwithbst :: Total no.of comparisions: "<<p.getcomp()<<endl;
     cout<<"getImbalance of BST tree(longestPathLength - shortestPathLength) ="<< p.getimb()<<endl;  
     p.Quicksort(0,num_entries-1);
     p.drawbst();
     p.printArray();
     
     
    
     
   
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
