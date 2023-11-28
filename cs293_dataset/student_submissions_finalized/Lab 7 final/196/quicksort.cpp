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
#include <cstdlib>



//Operator less than overloaded to compare the times of departure of two trains
//Returns true if first arg arrives earlier than the second arg
//and false otherwise
bool operator<(TrainInfoPerStation  t1, TrainInfoPerStation  t2){
  int i,j;
  for(int k=0; k<7;k++){
    if(t1.daysOfWeek[k]){
      i=k;
    }
    if(t2.daysOfWeek[k]){
      j=k;
    }
  }
  if(i<j){
    return true;
  }
  else if(j<i){
    return false;
  }
  else{
    if(t1.depTime<t2.depTime){
      return true;
    }
    else if(t1.depTime>t2.depTime){
      return false;
    }
    else{
      if(t1.arrTime<t2.arrTime){
      return true;
      }
      else if(t1.arrTime>t2.arrTime){
        return false;
      }
      return false;
    }
  }
}

//Swaps the Infos of objects of the given linked lists
void swap(listOfObjects<TrainInfoPerStation *> *n1, listOfObjects<TrainInfoPerStation *> *n2){
  TrainInfoPerStation * temp = n2->object;
  n2->object = n1->object;
  n1->object=temp;
}

//Partitions the linked list between starting node-> stnInfoList
//and lastNode->lastNode
//and returns the pivot index 
//based on the pivotValue and start and end index
int partition(listOfObjects<TrainInfoPerStation *> *stnInfoList,listOfObjects<TrainInfoPerStation *> *lastNode,TrainInfoPerStation* pivotValue, int start, int end){
    int i=start-1;
    int j=end+1;
    while(true){
      do{
        if(i!=start-1){
          stnInfoList=stnInfoList->next;
        }
        i++;
      }
      while(*(stnInfoList->object)<*(pivotValue));
      do{
        if(j!=end+1){
          lastNode=lastNode->prev;
        }
        j--;
      }
      while(*(pivotValue)<*(lastNode->object));
      if(i<j){
        swap(stnInfoList,lastNode);
      }
      else{
        return j;
      }
    }
}



void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 3; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;
  
 
  
  if (recursionLevel == 0) {
    
  }
  
 

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  //Base Case
  if (end<=start){
    return;
  }
  //If the list has 0 and 1 elements
  if(stnInfoList==nullptr || stnInfoList->next==nullptr){
    return;
  }
  
  //Stores the last node
  listOfObjects<TrainInfoPerStation *>* lastNode = stnInfoList;
  int i=start;
  while(i<end){
    lastNode=lastNode->next;
    i++;
  }
  //Array to store pointers to linked list nodes 
  static listOfObjects<TrainInfoPerStation *>* *Array;
  
  // Increment recursion level on entering the function
  recursionLevel++;
  
  
  
  //In recursiveLevel 0
  if (recursionLevel == 0) {
    //Length of the list
    static int len=end-start+1;
    //Initializing the array
    srand(time(0));
    Array= new listOfObjects<TrainInfoPerStation *>*[(len/K)+1];
    //Adding elements at each K interval to the static array
    int i=start;
    listOfObjects<TrainInfoPerStation *>* currList= stnInfoList; 
    while(i<end){
      if(i%K==0){
        Array[i/K]=currList;
      }
      currList=currList->next;
      i++;
    }
   
  }
  //Choosing Pivot in O(K) time
  //Generating random pivot index between start and end
  int pivotIndex=start+(rand()%(end-start+1));
  //Going to pivot in O(K) time using the static pointer array
  int j=pivotIndex/K;
  listOfObjects<TrainInfoPerStation *>* pivot=Array[j];
  for(int z=0; z<pivotIndex%K;z++){
    pivot=pivot->next;
  }
  //Pivot Value
  TrainInfoPerStation* pivotValue=pivot->object;
  //Partitioning the list and returning the pivot index
  int p=partition(stnInfoList,lastNode,pivotValue,start,end);
  //newStart stores the linked list node after the pivot index 
  int b=p/K;
  listOfObjects<TrainInfoPerStation *>* newStart=Array[b];
  for(int z=0; z<p%K;z++){
    newStart=newStart->next;
  }
  newStart=newStart->next;
  //Recursive QuickSort Calls
  QuicksortSimple(stnInfoList,start,p);
  QuicksortSimple(newStart,p+1,end);
 

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

#endif
