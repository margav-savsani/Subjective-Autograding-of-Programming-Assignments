#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

using namespace std;



// ************* RECEIVE INPUT *************
int main(int argc, char** argv)
{//freopen("sample-input.txt", "r", stdin);
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(pivot_chooser==1||pivot_chooser==2||pivot_chooser==3);
    
    
    cout<<"Enter your entries Journey Code followed by price"<<endl;;
    
    
    // Tree of sorting
    SorterTree S(pivot_chooser, num_entries);
    
    // This tree keeps track of all elements entered so far
    // It is used to prevent repetition of Journey Code entries
    // and the validity of a pivot. 
    BST* checking_tree = new BST;
    
    
    // taking input from user
    int i=0;
    while(i<num_entries){
        
        cout<<"Next entry is: "<<endl;
        int JourneyCode, price;
        cin >> JourneyCode >> price ;
        
        //checks if JourneyCode is repeated
        if(checking_tree->journeyCheck(checking_tree->root, JourneyCode)){
        checking_tree->insert(JourneyCode, price, checking_tree->root, nullptr);}
        else {cout<<"Journey Code already exists, try again:" <<endl;       
        num_entries--;continue;}
        
        
        Journey J(JourneyCode, price);
        S.array[i] = J;
	i++;
    }
    S.l = num_entries;
    
    cout<< endl;
    cout<<"Behold the sorted array: "<<endl;
    
//***** UNCOMMENT BELOW CODE FOR PLAIN QUICKSORT *********    
    
    //S.Quicksort(0,num_entries-1);
    
    
//***** BY DEFAULT RUNS QUICKSORT WITH BST INSERT ********
    //performs Quicksort with Insert
    S.QuicksortWithBSTInsert(0,num_entries-1, checking_tree);
    
//***** CODE HEREAFTER IS SAME FOR SORT WITH/WITHOUT INSERT**********    
    S.tree->printBST("");
    cout<<endl<<flush;
    S.printArray();
    
    
    

    cout<<"Number of comparisons is:"<< S.comparisons << endl;
    cout << "Imbalance is: "<<S.tree->getImbalance()<<endl;
    
    
    
   /* while(true){
    
    	cout<<endl;
    	cout<< "Welcome to Delete Mode: Press DEL and enter JourneyCode to delete."
    	break;} */
    
    
    
    
    
    
    
   
    
}
