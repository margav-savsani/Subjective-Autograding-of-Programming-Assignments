#include "sort.h"
#include <iostream>
using namespace std;
// Code up the functions defined in sort.cpp
int SorterTree::Partition(Journey* s,int a,int b,Journey d){
         Journey x;
         x=d;
       int i=a;
            int j=b;
            while(true){
                while(x<s[j]){
                      j=j-1;
                     comparisons=comparisons+1;
                      }
                   comparisons=comparisons+1;
                while(s[i]<x){
                     i=i+1;
                     comparisons=comparisons+1;
                     }
                   comparisons=comparisons+1;
                if(i<j){
                   Journey c;
                   c=s[j];
                   s[j]=s[i];
                   s[i]=c;
                 }
                else{
                  return j;
                  }
              }
           }
bool SorterTree::Quicksort(int start, int finish)
{       
        if(choice==1){
           Journey* y;
         y=choose_one(array,start,finish);
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
       else if(choice==2){
          Journey* y;
       y=choose_two(array,start,finish);
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
     else if(choice==3){
        Journey* y;
       y=choose_three(array,start,finish);
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
   }
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{   
     if(choice==1){
            Journey* y;
            y=choose_one(array,start,finish);
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
     else if(choice==2){
          Journey* y;
       y=choose_two(array,start,finish);
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
     else if(choice==3){
        Journey* y;
       y=choose_three(array,start,finish);
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
    return true;
}
