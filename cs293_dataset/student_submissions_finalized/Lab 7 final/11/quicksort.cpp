#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

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
#include <stdlib.h>

//type traininfo is defined as listOfObjects<TrainInfoPerStation *> *
typedef listOfObjects<TrainInfoPerStation *> *  traininfo ;  


bool compareTime( TrainInfoPerStation * A , TrainInfoPerStation * B) { 
    for( int i = 0 ; i < 7 ; i++ ) { 
        if ( A->daysOfWeek[i] == true && B->daysOfWeek[i] == false) return true ; 
        else if ( A->daysOfWeek[i] == true && B->daysOfWeek[i] == true ) {
             if ( A->arrTime == B->arrTime ) return (A->depTime  < B->depTime) ;
             else return ( A->arrTime < B->arrTime ) ;  
        } 
        else if (  A->daysOfWeek[i] == false && B->daysOfWeek[i] == true  ) return false ; 
        else {}
    }
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList){ 
  //Note ::
  //type traininfo is defined as listOfObjects<TrainInfoPerStation *> *
  
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1;  //depth of recurssion stack 
  //the array which stores the pointers of the list with index as multiples of k (0,k,2k,3k..)
  static traininfo* arr ; 
  int n = 1 ; 
  static int start ; // the static variable which indicates the start index . 
  static int end ; // the static variable which indicates the end index . 
  int start1 ; //the variable which indicates the start index ( copy of start , which wont change due to recurssion depth) 
  int end1 ; //the variable which indicates the end index ( copy of end , which wont change due to recurssion depth) 
  
  if ( recursionLevel != -1 && start >= end ) return ; //base case  
  
  recursionLevel++;
  
  if (recursionLevel == 0) {
    traininfo curr = stnInfoList ;  
    while  ( curr->next != nullptr )  { curr = curr->next ; n++ ; }  //find size of the list .
    curr = stnInfoList ; 
    arr = new traininfo[n/K] ; 
    for ( int i = 0 ; i  < n ; i++ ) {  //intialize the array of size n/ k . 
         if ( i%K == 0 ) arr[i/K] = curr ; 
         curr = curr->next ; 
    }
    end = n-1 ; 
    start = 0 ;    
  }

  start1 = start ; //copy start to start1 . (because start changes during the recurssive call , but not start1 )
  end1 = end ; //copy end to end1 . (because end changes during the recurssive call , but not end1 )
  
  int pivot_index =  start1 + (rand() % (end1-start1+1)) ;  //get a random pivot index between start and end . 
  traininfo pivot_ptr = arr[pivot_index/K] ;  //use the intialized static array to get the pivot in Order of K .
  for ( int i = 0 ; i < pivot_index%K ; i ++ ) pivot_ptr = pivot_ptr->next ; 
  
  TrainInfoPerStation* pivot = pivot_ptr->object ;//the object stored in pivot . 

  traininfo pj = arr[end1/K] ;
  for ( int i = 0 ; i < end1%K ; i ++ ) pj = pj->next ; //the last element of the linked list .
  
  traininfo pi = stnInfoList ; 
  int i = start1 ;  //temp variables 
  int j = end1 ;  //temp variables 

  //Partition function :::
  while( j>=i ){ //move pi to right side and pj to left similar to array quicksort . 
        while( end1>=i && compareTime(pi->object,pivot) ) { 
            pi = pi->next ; 
            i++;
        }
        while( start1<=j && compareTime(pivot,pj->object) ){
            pj = pj->prev ; 
            j--;
        } 
        if( j>= i){
            swap(pi->object,pj->object); 
            i++;
            j--;
            pi = pi->next ;
            pj = pj->prev ; 
       }
  } 
  
 
  if ( start1 < j ) { //left side quicksort 
     start =  start1 ; 
     end =  j ;
     Quicksort(stnInfoList); 
  } 
  if ( end1 > i ) { //right side quicksort .
     start = i ;
     end = end1 ;
     Quicksort(pi);
  }


  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; 
  static traininfo* arr ;//depth of recurssion stack 
  int n = 1 ; 

  //base case 
  if ( recursionLevel != -1 && start >= end ) return ; 
  
  recursionLevel++;
  
  if (recursionLevel == 0) {
    traininfo curr = stnInfoList ;  
    while  ( curr->next != nullptr )  { curr = curr->next ; n++ ; } //find size of the list 
    curr = stnInfoList ; 
    arr = new traininfo[n/K] ;
    for ( int i = 0 ; i  < n ; i++ ) { //intialize the array of size n/ k . 
         if ( i%K == 0 ) arr[i/K] = curr ; 
         curr = curr->next ; 
    }
    end = n-1 ;  
    start = 0 ; 
  }

  
  int pivot_index =  start + (rand() % (end-start+1)) ;  //get a random pivot index between start and end . 
  traininfo pivot_ptr = arr[pivot_index/K] ; //use the intialized static array to get the pivot in Order of K .
  for ( int i = 0 ; i < pivot_index%K ; i ++ ) pivot_ptr = pivot_ptr->next ; 
  
  TrainInfoPerStation* pivot = pivot_ptr->object ;//the object stored in pivot . 

  traininfo pj = arr[end/K] ; //the last element of the linked list .
  for ( int i = 0 ; i < end%K ; i ++ ) pj = pj->next ; 
  
  traininfo pi = stnInfoList ;
  int i = start ; //temp variables
  int j = end ; //temp variables
  
  //Partition function :::
  while( j>=i ){ //move pi to right side and pj to left similar to array quicksort . 
        while( compareTime(pi->object,pivot) ) {
            pi = pi->next ; 
            i++;
        }
        while( compareTime(pivot,pj->object) ){
            pj = pj->prev ; 
            j--;
        } 
        if( j>= i){
            swap(pi->object,pj->object);
            i++;
            j--;
            pi = pi->next ;
            pj = pj->prev ; 
       }
  } 
  
 
  if ( start < j ) { //left side quicksort
     QuicksortSimple(stnInfoList,start,j);
  }
  if ( end > i ) {  //right side quicksort .
     QuicksortSimple(pi,i,end);
  }

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
