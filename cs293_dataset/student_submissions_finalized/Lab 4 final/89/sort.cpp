#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

SorterTree :: SorterTree(int choice, int l){
   this->choice=choice;                        // constructor
   this->l=l;
   array=new Journey[l];                  
   tree=new BST();                          
   comparisons=0;
 }  
 
int SorterTree :: getcomparisons(){
    return comparisons;               //function that returns the variable comparisons
    }                                 // we need this function since we cannot access a private variable
 
 
void SorterTree :: InsertInArray(int n, Journey* A){      // function to insert the given input into array
   array[n]=*A;
    return;
   }   
 
int SorterTree :: Partition(Journey* A, int start, int finish){

     Journey* pivot;
     if(choice==1) pivot = choose_one(A, start, finish);
     else if(choice==2) pivot = choose_two(A, start, finish);
     else if(choice==3) pivot = choose_three(A, start, finish);
     
     int x=pivot->getJourneyCode();
     int y=pivot->getPrice();
     Journey Pivot(x,y);
     
   int i = start;
   int j = finish;
   
   while(true)
    {
    
      while(Pivot < A[j])
         {
            j--;
            comparisons++;
           }
         
      while(A[i] < Pivot)
         {
           i++;
           comparisons++;
          }
         
      if(i<j)
        {
           Journey J=A[i];	
           A[i]=A[j];
           A[j]=J;
        }
      else if(j==finish) return j-1;  
      else return j;
    }  
}	             

bool SorterTree :: Quicksort(int start, int finish){
 
   if(finish<=start) return true;
   int i = Partition(array,start,finish);  // i is the index of the partition
   Quicksort(start,i);
   Quicksort(i+1,finish);
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
     
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish){
 
  if(finish<start) return true;
  
     Journey* pivot;
     if(choice==1) pivot = choose_one(array, start, finish);
     else if(choice==2) pivot = choose_two(array, start, finish);
     else if(choice==3) pivot = choose_three(array, start, finish);   
	
     insertPivot(pivot->getJourneyCode(),pivot->getPrice());   //inserting pivot into the BST 
 
     if(finish == start) return true;  
  
     int i = Partition(array,start,finish);   // i is the index of the partition
     QuicksortWithBSTInsert(start,i);
     QuicksortWithBSTInsert(i+1,finish);
       
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
  
}

 bool SorterTree :: insertPivot(int JourneyCode, int price){
   tree->insert(JourneyCode,price);     // calling insert function of class BST    
   return true;
}    

void SorterTree :: printNodePath(){

      // function that prints difference between length of shortest and longest path from root to leaf     
      
    cout<<"root to leaf path difference (max-min) : "<< tree->getImbalance() <<endl;
    return;
 } 

void SorterTree :: printTree(){
   tree->printBST(" ");          //function that calls printBST function 
   return;
 }  

bool SorterTree::printArray(){
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}
