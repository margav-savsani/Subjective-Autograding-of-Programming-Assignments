#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp
SorterTree::SorterTree(int ch,int n,Journey arr[]){//constructor for sortertree
    choice=ch;
    l=n;
    array=arr;
}
int SorterTree::Partition(Journey* s,int a,int b,Journey d){
         Journey x;
         x=d;
       int i=a;
            int j=b;
            while(true){
                while(x<s[j]){//refer to naveen garg slides
                      j=j-1;
                     comparisons=comparisons+1;
                      }
                   comparisons=comparisons+1;
                while(s[i]<x){//refer to naveen garg slides
                     i=i+1;
                     comparisons=comparisons+1;
                     }
                   comparisons=comparisons+1;
                if(i<j){//refer to naveen garg slides
                   Journey c;
                   c=s[j];
                   s[j]=s[i];
                   s[i]=c;
                 }
                else{//refer to naveen garg slides
                  return j;
                  }
              }
           }
bool SorterTree::Quicksort(int start, int finish)
{       Journey* y;
        if(choice==1){y=choose_one(array,start,finish);}
        else if(choice==2){y=choose_two(array,start,finish);}
        else if(choice==3){y=choose_three(array,start,finish);}
         int q;
         if(start<finish){
          q=Partition(array,start,finish,*y);
          if(q!=finish){
           Quicksort(start,q);
           Quicksort(q+1,finish);
          }
          else{
           q=finish-1;
           Quicksort(start,q);
          Quicksort(q+1,finish);
          }
         }
       return true;
       }
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{   Journey* y;
     if(choice==1){y=choose_one(array,start,finish);}
     else if(choice==2){y=choose_two(array,start,finish);}
        else if(choice==3){y=choose_three(array,start,finish);}
            Journey z=*y;
            int q;
            insertPivot(z.getJourneyCode(),z.getPrice());
        if(start<finish){
          q=Partition(array,start,finish,*y);
         if(q!=finish){
          QuicksortWithBSTInsert(start,q);
          QuicksortWithBSTInsert(q+1,finish);
         }
        else{
         q=finish-1;
         QuicksortWithBSTInsert(start,q);
          QuicksortWithBSTInsert(q+1,finish);
         }
        }
       return true;
}
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return 1;
}

bool SorterTree::insertPivot(int JourneyCode,int price){
   return tree->insert(JourneyCode,price);}