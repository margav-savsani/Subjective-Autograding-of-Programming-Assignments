#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"



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
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    int place=0;
    SorterTree s(pivot_chooser,num_entries);
    while(true){
        if(place==num_entries) break;
        int JourneyCode;
        int price;
        cin>>JourneyCode>>price;
        Journey j (JourneyCode,price);
        
        s.insertt(place,j);
        //cout<<"inside while loop"<<endl;
        place=place+1;
    }
    //cout<<"break"<<endl;
	//s.Quicksort(1,num_entries);
   
   //cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
    //cout<<endl;
    s.QuicksortWithBSTInsert(0, place-1);
    cout<<"........................................"<<endl;
    cout<<"After QuicksortWithBSTInsert:"<<endl;
    s.printArray();
    cout<<endl;
    
    cout<<"Total Cost of Comparisons:";
    cout<<s.getcomparisons();
    cout<<endl;
  
  cout<<"Imbalance:";
    cout<<s.imb();
    cout<<endl;

     s.Quicksort(0, place-1);
    cout<<"........................................"<<endl;
    cout<<"After Quicksort:"<<endl;
    s.printArray();
    cout<<endl;
    
    
   // cout<<"Total Cost of Comparisons:";
    //cout<<s.getcomparisons();
    //cout<<endl;
    

}



