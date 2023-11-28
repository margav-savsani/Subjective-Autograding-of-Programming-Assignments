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


listOfObjects<TrainInfoPerStation *> Partition(listOfObjects<TrainInfoPerStation *> *stnInfoList,listOfObjects<TrainInfoPerStation *> *pivot,int start,int end)
{
  listOfObjects<TrainInfoPerStation *> *head= stnInfoList;
  listOfObjects<TrainInfoPerStation*> *tail= stnInfoList;
  while(tail->next !=nullptr)
  {
    tail = tail->next;
  }

  while (start<end)
  {
    while (pivot < tail)
        {
            tail = tail->prev;
            end--;
        }
        while (head < pivot)
        {
            head = head->next;
            start++;

        }

        if (end < start)
        {
          listOfObjects<TrainInfoPerStation*> *temp= head;
          tail->prev = head->prev;
          head->prev->next = tail;
          tail->next = temp->next->next;

          


            
        }
        else
        {

            return j;
        }
  }
  


}


void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *pivot = nullptr;
  listOfObjects<TrainInfoPerStation *> *ptr = stnInfoList->next;
  for (int i = 1; i < K - 1; i++)
  {
    listOfObjects<TrainInfoPerStation *> *minPivot = pivot->prev;
    listOfObjects<TrainInfoPerStation *> *maxPivot = pivot->next;

    if(maxPivot < ptr)
    {
      maxPivot = ptr;
    }
    if(maxPivot < minPivot)
    {
      maxPivot = minPivot;
    }

    if(minPivot > ptr)
    {
      minPivot = ptr;
    }
    if(minPivot > maxPivot)
    {
      minPivot = maxPivot;
    }

    if(maxPivot > ptr &&  ptr > minPivot)
    {
      pivot = ptr;
    }
    if(maxPivot > ptr->prev &&  ptr->prev > minPivot)
    {
      pivot = ptr->prev;
    }
    if(maxPivot > ptr->next &&  ptr->next > minPivot)
    {
      pivot = ptr->next;
    }

    ptr = ptr->next;
  }
  // found pivot :D



}
