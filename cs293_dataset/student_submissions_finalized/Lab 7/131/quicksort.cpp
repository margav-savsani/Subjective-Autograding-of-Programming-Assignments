#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    listOfObjects<TrainInfoPerStation *> *tail=getTail(stnInfoList);
    if (start<finish)
     { listOfObjects<TrainInfoPerStation *> *q=partition (stnInfoList,stnInfoList,tail);
      Quicksort (stnInfoList,stnInfoList,q->prev);
      Quicksort(stnInfoList,q,tail);}
     // else{cout<< comparisons<<endl;}
      return true;
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
  // Put your code here.
};

void partition(listOfObjects<TrainInfoPerStation *> *stnInfoList,listOfObjects<TrainInfoPerStation *> *start){  // partition function
  listOfObjects<TrainInfoPerStation *> *pivot;
  

   
   int limit=r;
   int x=pivot.gettime();
   listOfObjects<TrainInfoPerStation *> *y=A[r];
    int i=p-1;
    int j=r+1; 
   
    while(1){
        while(1){
            
            
            if ( A[j].operator<(y) || A[j].getJourneyCode()==x ){
                break;
            }
        }
        while(1){
            start=start->next;
          
            if ( y.operator<(A[i]) || A[i].getJourneyCode()==x ||i>limit){
                break;
            }
        }
       
        if( i<=j){
        Journey temp =A[i];
        A[i]=A[j];
        A[j]= temp;}
         else{return j;}
         
   }
}

