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
#include <cstdlib>
typedef listOfObjects<TrainInfoPerStation *>*  ll ;   
int k = 4 ;

void recQuickSort(ll list , ll* arr , int l , int r , ll head , ll tail ) { 
    int pivot_index = l +  (rand()%(r-l+1)) ; 
    ll pivot = arr[pivot_index/k] ;  
    for ( int i = 0 ; pivot->next == nullptr && i < rand()%k ; i++) { 
      pivot = pivot->next ; 
    }
    while () { 
       while ( head > pivot ) 
    }  
}


void Quicksort(ll stnInfoList)
{ 
   int n = 0 ; 
   ll temp = stnInfoList ; 
   while ( temp != nullptr ) { 
      temp = temp->next ; 
      n++ ; 
   }

   ll* arr = new ll[ n/k + 1 ] ;   
   int i = 0 ; 
   temp = stnInfoList ; 
   while ( temp != nullptr ) { 
       if ( i %k == 0 )  arr[i/k] = temp ; 
       i++ ; 
   }
   recQuickSort( stnInfoList,arr,0,n-1);
   
}
