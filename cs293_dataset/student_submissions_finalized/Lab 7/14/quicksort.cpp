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
  // Put your code here.
  // take a random k for now i am taking 4
  int K = 4;
  // store pointer of every kth node of linked list starting from 1
  // so that we can use only n/k additional space
  // so that to search a node we can find the nerest element in array and go k steps fwd or backward
  
  //finding length of array
  int len = 0;
  listOfObjects<TrainInfoPerStation *> * help = stnInfoList;
  while(help)
  {
    len++;
    help = help->next;
  }
  len = len/(K);
  //since we just need len/k space

  //storing pointers in the array
  TrainInfoPerStation* arr[len];
  listOfObjects<TrainInfoPerStation *> * help = stnInfoList; //head of linked list
  int i=1;
  while(i<=len)
  {
    if((i-1)%(K))
    {
      arr[(i-1)/(K)] =  help->object;
    }
    else
    {
      help = help->next;
    }
  }

  //storing got completed
  //now for finding random pivot
  int index = (rand()%len) +1; 
  // now find the pointer nearest to it
  int arr_idx = index - (index%4) + 1;
  // reach the required pointer from the pointer at arr_idx
  listOfObjects<TrainInfoPerStation *> * pivot = stnInfoList;
  for(int i=0;i<(index%4) - 1;i++)
  {
    pivot = pivot->next;
  }
  //found pivot
}
