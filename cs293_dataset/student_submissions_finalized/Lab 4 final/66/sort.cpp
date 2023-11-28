#include "sort.h"
#include <iostream>


 SorterTree::SorterTree(int choice,int l){
 
      array=new Journey[l];  tree=new BST;                           // Creating new array for storing journeys and new BST for storing pivots
      
      this->choice=choice; this->l=l;                                // intialising data members in SorterTree 
      comparisons=0;
 }  

 bool SorterTree::add(Journey j,int i){
  
     array[i]=j;                                                     // For adding given journey into array
     return true;
 }

int SorterTree::partition(int s,int e){
         
    Journey x;                                                      // for storing journey at pivot index
     
    if(choice==1) {  x=*(choose_one(array,s,e));}                   // getting pivot journey from one of the four choose functions            
    else if(choice==2) {  x=*(choose_two(array,s,e));}
    else if(choice==3) {  x=*(choose_three(array,s,e));}

    int  i = s, j = e;
     
    while(true){
    
        while(x<array[j]){ j=j-1; comparisons++; }          
        while(array[i]<x){ i=i+1; comparisons++; }
        
        if(i<j){
        
            Journey a = array[i];
            array[i] = array[j];
            array[j] = a;  
        }
        
        else { return j;}
    }  
         
  }
 
  
 int SorterTree::partition1(int s,int e){
         
    Journey x;
    
    if(choice==1) {  x=*choose_one(array,s,e);} 
    else if(choice==2) {  x=*choose_two(array,s,e);}
    else if(choice==3) {  x=*choose_three(array,s,e);}
    
    insertPivot(x.getJourneyCode(),x.getPrice());
     
    int i = s, j = e; 
     
    while(true){
    
        while(x<array[j]){ j=j-1;comparisons++; }
        while(array[i]<x){ i=i+1;comparisons++; }
        
        if(i<j){
            Journey a = array[i];
            array[i] = array[j];
            array[j] = a;  
        }
        
        else { return j;}
    }  
         
  } 
  
 bool SorterTree::insertPivot(int JourneyCode,int price){
 
      tree->insert(JourneyCode,price);
      return true;
  }

bool SorterTree::Quicksort(int start, int finish){
     
      if(start<finish){
          int cut = partition(start,finish);
          
          
          if(cut==finish){Quicksort(start,cut-1);
                          Quicksort(cut,finish);}
          else { 
                   Quicksort(start,cut);
                   Quicksort(cut+1,finish);
           }
      }  
      
      return true;
  }



bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{       
    if(start<finish){
          int cut = partition1(start,finish);
          
          
          if(cut==finish){QuicksortWithBSTInsert(start,cut-1);
                         QuicksortWithBSTInsert(cut,finish);}
          else { 
                QuicksortWithBSTInsert(start,cut);
                QuicksortWithBSTInsert(cut+1,finish);
           }
      }  
      
      return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl ;
    }
    
    cout << comparisons<<endl;
    
    return true;
}

BST*  SorterTree::getTree(){return tree;}

SorterTree::~SorterTree(){}
