#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int choice, int l){
            this->choice=choice;
            this->l=l;
            comparisons=o;
            array=new Journey array[l];
               for(int i=0; i<=l;i++){
                array[i]=NULL;}
               }// Define valid constructor
void SorterTree::swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
    int SorterTree ::partition(Journey*array, int start,int finish){
        //choosing pivot
        if(pivot_chooser==1) {Journey* pivot =choose_one(array,start,finish);}
        if(pivot_chooser==2) {Journey* pivot =choose_two(array,start,finish);}
        if(pivot_chooser==3) {Journey* pivot =choose_three(array,start,finish);}
        
           Journey pivot= *pivot;
          int JourneyCode=pivot.getJourneyCode();
    
    int i = (start ); // Index of smaller element and indicates the right position of pivot found so far
  
    int j=(finish);
    while (true){
        // If current element is smaller than the pivot 
        
           while(JourneyCode<array[j]){
              j--;
            comparisons++;
           }
        while(array[i]<=JourneyCode){
            i++; // increment index of smaller element 
            comparisons++;
        } 
    if(i<j){
    swap(&arr[i ], &arr[j]); }
    return (i + 1); 
} 
         
                                                                  }
  bool SorterTree:: Quicksort(int start, int finish){
      if (start<finish)
       int index=partition(array,start,finish);
         if Quicksort(start,index-1,) 
         if Quicksort(index+1,finish)
              return true;

          else 
          return false;

       };

  }; // Sort the array according to the stored values
  bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{    if (start<finish)
       int index=partition(array,start,finish);
       
       Journey pivot;
       pivot=array[index];
       int JourneyCode=pivot.getJourneyCode();
       int price=pivot.getPrice();
       if(insertPivot(JourneyCode,price))
       return true;
       else 
       return false;
          Quicksort(start,index-1,) 
          Quicksort(index+1,finish)
              

}       


    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

  


  bool SorterTree:: insertPivot(int JourneyCode, int price){
        {   BST* tree;
        tree=getTree();
          if ( tree->root ==NULL){
           root=new TreeNode(JourneyCode, price);
           return true;}
            struct TreeNode* node=currNode;
      else {
         
      
    
          
          
  }; // insert node corresponding to chosen pivot in BST
  BST* SorterTree::getTree(){
    return tree;}
   // returns pointer to the tree of pivots
  SorterTree::~SorterTree(){
    delete[] array;
  } // Destructor




bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
