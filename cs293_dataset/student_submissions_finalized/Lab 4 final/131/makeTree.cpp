#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <chrono>

using namespace std;

int main(int argc, char** argv)
{ auto start = chrono :: steady_clock::now();

    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    Journey * arr=new Journey[64];
    cout<<"Starting"<<endl;
    for (int k=0; k<num_entries;k++)
    {    int journeycode,price;
        cin>>journeycode >>price;
        arr[k]=Journey(journeycode,price);
            
    }
    cout<<"entry done"<<endl;
    
    SorterTree *s= new SorterTree(pivot_chooser,num_entries,arr);
    cout<< "Enter 1 for q1 and 2 for q2";

     int n;
     cin>> n;
     if (n==1){
       s->Quicksort(0,num_entries-1);
       cout<<endl<<"Comparisons = " <<s->get_comp()<<endl;
       s->printArray();
    
     }

     if (n==2){
      s->QuicksortWithBSTInsert(0,num_entries-1);
      cout<<endl<<"Comparisons = "<< s->get_comp()<<endl;
      s->get_tree();
      cout<<endl<<"Imbalance = "<<b1->getImbalance()<<endl;
     }

    // sleep (3);
     auto end= chrono ::steady_clock::now();
     cout<<"Elapsed time in microseconds : "<<chrono::duration_cast<chrono::microseconds>(end-start).count()<<endl;

    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
