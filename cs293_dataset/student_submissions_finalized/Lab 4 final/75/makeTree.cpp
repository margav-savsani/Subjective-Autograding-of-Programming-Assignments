#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.h"
#include "tree.h"
#include "journey.h"
#include "choose.h"
#include <chrono>
#include <algorithm>
#include<vector>
#include <bits/stdc++.h>
#include <fstream>


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
    bool flag = false;// to decide whether to quicksort and insert into the BST

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Making a Sorter Tree
    SorterTree sorttree(pivot_chooser, num_entries);


    Journey* array = sorttree.getArray(); // getting the pointer to the sorttree array to insert elemets
    Journey journeyentry; // initializing an empty journey to take input from the user 
    
    unsigned int JourneyCode = 0;
    unsigned int price = 0;
    // accepting the user's input (journeys)
    for(int i = 0; i<num_entries;i++){
        cin>> JourneyCode;
        cin>> price;

        // putting in the entered values of journey code and price
        journeyentry.setJourneyCode(JourneyCode);
        journeyentry.setPrice(price);

        // Inserting the journey objects in the Journeys array
        array[i] = journeyentry; 
    }

        // Start counting the time from now  
        auto start = std::chrono::high_resolution_clock::now();
        // Taking user input to decide whether to do quicksort or do quicksort+BST
        cout<<"TYPE 0. TO SORT USING QUICKSORT ONLY"<<endl;
        cout<<"TYPE 1. TO SORT USING QUICKSORT AND INSERT THE PIVOTS INTO THE BST"<<endl;
        cin>> flag;
        cout<<"------------------------------------------------------------------------------"<<endl;
        if (!flag){
            // Implementing quicksort (normal)
            cout<<"BEFORE QUICKSORT"<<endl;
            sorttree.printArray(); // printing the Array of journeys for debugging
            cout<<"------------------------------------------------------------------------------"<<endl;
            cout<<"QuickSort successful? "<<sorttree.Quicksort(0,num_entries-1)<<endl;
            cout<<"------------------------------------------------------------------------------"<<endl;
            cout<<"AFTER QUICKSORT"<<endl;
            sorttree.printArray(); 
            cout<<"------------------------------------------------------------------------------"<<endl;
        // -----------------------------------------------------------------------------------------
        }
        else{
            sorttree.getTree()->printBST("",false);
            // Implementing Quicksort with insertion into the tree
            cout<<"BEFORE QUICKSORT"<<endl;
            sorttree.printArray(); // printing the Array of journeys for debugging
            cout<<"------------------------------------------------------------------------------"<<endl;
            cout<<"QuickSort successful? "<<sorttree.QuicksortWithBSTInsert(0,num_entries-1)<<endl;
            cout<<"------------------------------------------------------------------------------"<<endl;
            cout<<"AFTER QUICKSORT"<<endl;
            sorttree.printArray(); 
        
            // printing the BST
            cout<<"------------------------------------------------------------------------------"<<endl;
            sorttree.getTree()->printBST("",false);
            cout<<"------------------------------------------------------------------------------"<<endl;
        
            cout<<"IMBALANCE IN THE TREE IS: "<<sorttree.getTree()->getImbalance()<<endl;
            cout<<"------------------------------------------------------------------------------"<<endl;

        //---------------------------------------------------------------------------------------------
        }
        // Stop counting the time
        auto stop = high_resolution_clock::now();

        cout<<"------------------------------------------------------------------------------"<<endl;
        cout<<"NO. OF COMPARISIONS: "<<(sorttree.getComparisons())<<endl;
        cout<<"------------------------------------------------------------------------------"<<endl;

        cout<<"CALLING THE FUNCTION FOR TIMING THE QUICKSORT...."<<endl;
        
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "COMPARISIONS: "<<(sorttree.getComparisons()) << " " << "DURATION: " <<duration.count() <<" MILLISECONDS "<< endl;

}




