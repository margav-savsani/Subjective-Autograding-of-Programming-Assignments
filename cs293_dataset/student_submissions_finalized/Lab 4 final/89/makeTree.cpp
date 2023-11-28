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
    
    SorterTree s(pivot_chooser,num_entries);  //creating an instance of SorterTree
    
    int i=0;
    while(i<num_entries){
 
      int JourneyCode;
      int price;
      cin>>JourneyCode;
      cin>>price;
      Journey* A=new Journey(JourneyCode,price);
      s.InsertInArray(i,A);     // insertng the input into the array 
      i++;
      
     }
     
    s.QuicksortWithBSTInsert(0,num_entries-1);
    cout<<"NO Of Comparisons : "<<s.getcomparisons()<<endl;
    s.Quicksort(0,num_entries-1);   
    s.printNodePath();
    s.printTree();       //prints the BST 
    s.printArray();      //prints the array
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
