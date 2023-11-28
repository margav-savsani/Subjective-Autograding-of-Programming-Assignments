#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp



int SorterTree::Partition ( int start,int finish)     // Call appropriate pivot function based on choice
{ 
  int p = Pivot.getJourneyCode();
  int part;
   int a = (array[finish].getJourneyCode());
 int i = start-1;     
 int j = finish+1;
 int x=1;
 int t = p;
 p = a;
 a = t;
 while(x=1){
 int ai = array[i].getJourneyCode();
 int aj = array[j].getJourneyCode();
 if(aj<=p){
 j=j-1;}
 if(aj>=p){
 i=i+1;}
 if(i<j){
 int q = ai;
 ai=aj;
 aj=q;
 x=1;}
 else{
 part=j;
 x=2;}
 }  
return part;
}
bool SorterTree::Quicksort(int start, int finish)
{Journey* Pivot;
  if(choice == 1)
  Pivot = choose_one(array,start,finish);
  if(choice == 2)
  Pivot = choose_two(array,start,finish);
  if(choice == 3)
  Pivot = choose_three(array,start,finish);
  if(choice == 4)
  Pivot = choose_four(array,start,finish);
 int ai = array[start].getJourneyCode();
 int aj = array[start].getJourneyCode();
 int p;
 if(start<finish){
    p = Partition(start,finish);  
    Quicksort( start, p);      // Split into 2 parts based on pivot choice
     Quicksort(p , finish);    // Recursively keep sorting
}
return true;
}
bool insertPivot(int JourneyCode, int Price){
   tree->insert(JourneyCode, price);
 
}
bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{Journey* Pivot
if(choice == 1)
  Pivot = choose_one(array,start,finish);
  if(choice == 2)
  Pivot = choose_two(array,start,finish);
  if(choice == 3)
  Pivot = choose_three(array,start,finish);
  if(choice == 4)
  Pivot = choose_four(array,start,finish);
  insertPivot(Pivot->JourneyCode,Pivot->price);
 int ai = array[start].getJourneyCode();
 int aj = array[start].getJourneyCode();
 int p;
 if(start<finish){
    p = Partition(start,finish);  
    Quicksort( start, p);      // Split into 2 parts based on pivot choice
     Quicksort(p , finish); 
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
