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



//Operator less than overloaded to compare the departure time of two trains
bool operator<(TrainInfoPerStation  t1, TrainInfoPerStation  t2)
{
  int i, j;
  
  for(int m = 0; m < 7; m++)
  {
    if(t1.daysOfWeek[m])
    {
      i = m;
    }
    
    if(t2.daysOfWeek[m])
    {
      j = m;
    }
  }
  
  if(i < j)
  {
    return true;
  }
  
  else if(j < i)
  {
    return false;
  }
  
  else //Comparing time
  {
    if(t1.depTime < t2.depTime)
    {
      return true;
    }
    
    else if(t1.depTime > t2.depTime)
    {
      return false;
    }
    
    else
    {
      if(t1.arrTime<t2.arrTime)
      {
      	return true;
      }
      
      else if(t1.arrTime>t2.arrTime)
      {
        return false;
      }
      return false;
    }
  }
  //Returns true if first argument arrives earlier than the second argument
  //and false otherwise
}

//Swaps the Infos 
void swap(listOfObjects<TrainInfoPerStation *> *n1, listOfObjects<TrainInfoPerStation *> *n2){
  TrainInfoPerStation * T = n2->object;
  n2->object = n1->object;
  n1->object = T;
}

//Partitions the linked list and returns the pivot index 
int partition(listOfObjects<TrainInfoPerStation *> *stnInfoList,listOfObjects<TrainInfoPerStation *> *lastNode,TrainInfoPerStation* pivotValue, int start, int end)
{
    int i = start - 1;
    int j = end + 1;
    
    while(true)
    {
      do
      {
        if(i != start - 1)
        {
          stnInfoList = stnInfoList->next;
        }
        i++;
      }
      
      while(*(stnInfoList->object)<*(pivotValue));
      do{
          if(j != end + 1)
          {
            lastNode = lastNode->prev;
          }
          j--;
      }
      
      while(*(pivotValue) < *(lastNode->object));
      if(i < j)
      {
        swap(stnInfoList,lastNode);
      }
      
      else
      {
        return j;
      }
    }
}



void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  static int k = 4; // Parameter K
  static int level = -1; // This can be used to find out at which 
                         //level of recursion we are in

  // Increment recursion level on entering the function
  level++;
    
  if (level == 0) {
    
  }

  // Decrement recursion level before leaving the function
  level--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  static int k = 4; // Parameter to be experimented with
  static int level = -1; 
  
  //Base Case
  if (end <= start)
  {
    return;
  }
   
  if(stnInfoList == nullptr || stnInfoList->next == nullptr)
  { //If the list has 0 and 1 elements
    return;
  }
    
  listOfObjects<TrainInfoPerStation *>* lastNode = stnInfoList; //Stores the last node  
  int i = start;
  
  while(i < end)
  {
    lastNode = lastNode->next;
    i++;
  }
    
  static listOfObjects<TrainInfoPerStation *>* *arr; //Array to store pointers to 
                                                     //linked list nodes  
  level++;   // Increment recursion level on entering the function
   
  //In recursiveLevel 0
  if (level == 0) 
  {  
    static int l = end - start + 1;  //Length of the list
    
    arr = new listOfObjects<TrainInfoPerStation *>*[(l/k)+1]; //Initializing the array
    
    int i = start; 
    
    listOfObjects<TrainInfoPerStation *>* List = stnInfoList; 
    //Adding elements at each K interval to the static array
    while(i < end)
    {
      if(i % k == 0)
      {
        arr[i/k] = List;
      }
      List = List->next;
      i++;
    }   
  }
  
  //Choosing Pivot in O(K) time
  //Generating random pivot index between start and end
  int pivotIndex = start + (rand() % (end - start + 1));
  
  int j = pivotIndex/k;
  listOfObjects<TrainInfoPerStation *>* pivot=arr[j];
  
  for(int z = 0; z < pivotIndex % k; z++)
  {
    pivot = pivot->next;
  }
  
  TrainInfoPerStation* pivotValue = pivot->object; //Pivot Value
  
  int p = partition(stnInfoList, lastNode, pivotValue, start, end); //Partitioning the 
                                         //list and returning the pivot index
  
  int t = p/k; //newStart stores the linked list node after the pivot index 
  listOfObjects<TrainInfoPerStation *>* newstart = arr[t];
  
  for(int z = 0; z < p%k; z++)
  {
    newstart = newstart->next;
  }
  
  newstart = newstart->next;
  
  //Recursive QuickSort Calls
  QuicksortSimple(stnInfoList, start, p - 1);
  QuicksortSimple(newstart, p + 1, end);
 
  level--; // Decrement recursion level
  return;
}

#endif
