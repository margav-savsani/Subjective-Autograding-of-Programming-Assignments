#include "sort.h"
#include <iostream>
#include<fstream>
#include<string>

// Code up the functions defined in sort.cpp

// prints the journey code and price of each element of the array of journeys
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;//printing the elements
    }
    return true;
}

// Constructor initialising the choice and the size of array, BST and array are dynamically allocated memory and the number of comparisons are initialised  
SorterTree::SorterTree(int choice, int l){
    //initialising the private variables

    this->choice=choice;
    this->l=l;
    array=new Journey [l];
    tree=new BST;
    comparisons=0;
}


//reading from the file and inserting all elements in the array 
void SorterTree:: insert(){
    //asking for filename from user
    cout<<"Enter file name ";
    string filname;
    cin>>filname;
    //reading the file 
    ifstream f1(filname); 
    string line;
    string word; 
    //initialising line count var iable
    int  line_count=0;
    while (getline(f1, line)) {
        Journey*element =new Journey();//dynamically allocating memory
        stringstream words(line);
        words >> word;
        //initialising the element
        element->change_code(stoi(word));
        
        words >> word;
        element->change_price(stoi(word));
        // storing the element
        (array[line_count]) = *element;

        line_count++;
    }
}

//helper function to swap two pointers
void SorterTree::swap(Journey* a, Journey* b) 
{ 
    Journey t = *a; 
    *a = *b; 
    *b = t; 
} 



// partition function which stores the pivot at the correct position in the array
int SorterTree::part(int start, int finish){
    //as random_pat has already exchanged the pivot element with the last element the last element is now the pivot
    Journey pivot=array[finish];
    int i=start-1;
    for (int j=start;j<=finish-1;j++){
        // i in incremented till we encounter elements less than the pivot element
        if(array[j].getJourneyCode()<pivot.getJourneyCode()){
            i++;
            swap(&array[i],&array[j]);
        }
        comparisons++;
    }
    //placing the pivot element at its correct location
   swap(&array[i+1],&array[finish]);
   return i+1;
}



//randomised partition function which takes input from the random choose functions
int SorterTree::random_part(int start, int finish){
    //initialsing the starting and ending address
    Journey * starting_address=&array[start];
    Journey * last_address=&array[finish];
    Journey *pivot;

    int num=0;
    //the whle loop continues till a valid pivot element is found or the number of iterations exceed 1000, in the first case
    // the loop breaks and that element is set as the pivot
    //in the later case the the function returns the error value (-5) indicating that the choose function opted is repeatedly 
    // returning out of bounnd values and thus the function needs to be changed or corrected
    while(true){
        //depending upon choice, choose function is selected
        if(choice==1){
            pivot=choose_one(array,start,finish);
        }

        else if(choice==2){
            pivot=choose_two(array,start,finish);
        }

        else if(choice==3){
            pivot=choose_three(array,start,finish);
        }

        else {
            // pivot=choose_four(array,start,finish);
        }
        // num variable stores the number of iterations of the loop
        num++;
        // if pivot is a null pointer, continue search
        if(pivot==NULL){
            continue;
        }
        // if its a valid pointer, break the loop and set that as the pivot
        if(starting_address<=pivot && pivot<=last_address){
            break;
        }
        // if the choose function is repeatedly returning out of bound values
        if (num >1000){
            cout<<"Choose function is repeatedly giving out of bound values"<<endl;
            return -5; 
        }
    }

    // swapping the pivot and last element 
    swap(pivot,&array[finish]);
    //calling the partition function
    return part(start,finish);
}  


bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    if(start<finish){
        int part;
        //initialising the pivot
        part=random_part(start,finish);
        //handling error 
        if(part==-5){
            cout<<"Try with another choose function as this choose function is repeatedly giving out of bound values"<<endl;
            return false;
        }
        //quick soring sub-arrays
        //if any recurive call returns false
        // the full functioon returns false
        if(!Quicksort(start,part-1)){
        return false;
        }
        
        if (!Quicksort(part+1,finish)){
            return false;
        }
        }
    return true;      
}
//returns the vakue of comparisons private variable
int SorterTree::get_comparisons(){
    return comparisons;
}


//randomised partition function which takes input from the random choose functions

// same as the previous random_part function
// the only addition is that this function also inserts elements in the BST
int SorterTree::random_part_with_insert(int start, int finish){


    Journey * starting_address=&array[start];
    Journey * last_address=&array[finish];
    Journey *pivot;

    int num=0;
    //the whle loop continues till a valid pivot element is found or the number of iterations exceed 1000, in the first case
    // the loop breaks and that element is set as the pivot
    //in the later case the the function returns the error value (-5) indicating that the choose function opted is repeatedly 
    // returning out of bounnd values and thus the function needs to be changed or corrected

    while(true){
        //depending upon choice, choose function is selected
        if(choice==1){
            pivot=choose_one(array,start,finish);
        }

        else if(choice==2){
            pivot=choose_two(array,start,finish);
        }

        else if(choice==3){
            pivot=choose_three(array,start,finish);
        }

        else {
            // pivot=choose_four(array,start,finish);
        }
        // num variable stores the number of iterations of the loop
        num++;
        if (num >1000){
            cout<<"Choose function is repeatedly giving out of bound values"<<endl;
            return -5; 
        }
        // if pivot is a null pointer, continue search
        if(pivot==NULL){
            continue;
        }
        // if its a valid pointer, break the loop and set that as the pivot
        if(starting_address<=pivot && pivot<=last_address){
   
            break;
        }
        // if the choose function is repeatedly returning out of bound values                
    }

    // swapping the pivot and last element 
    tree->insert(pivot->getJourneyCode(),pivot->getPrice());
    swap(pivot,&array[finish]);
    //calling the partition function
    int partition= part(start,finish);

    return partition;

}  

// this function is same as the Quicksort function
// the only difference being that to initialise pivots, it calls the random function which also inserts elements in the BST
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    // Also in this implementation : <= is used as even the single element arrays need to be passed in order to be able to print them
    if(start<=finish){
        int part;
        //initialising the pivot
        part=random_part_with_insert(start,finish);
       
        if(part==-5){
            //handling error 
            cout<<"Try with another choose function as this choose function is repeatedly giving out of bound values"<<endl;
            return false;
        }

        //quick soring sub-arrays
        //if any recurive call returns false
        // the full functioon returns false
       if(!QuicksortWithBSTInsert(start,part-1)){
        return false;
       }
        
        if (!QuicksortWithBSTInsert(part+1,finish)){
            return false;
        }
        }
    return true;      
}

// returns an alias for the tree pointer
BST* SorterTree:: get_tree(){
    return tree;
}


