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
#include <vector>
void exchange(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b)
{
  TrainInfoPerStation *t = a->object;
  a->object = b->object;
  b->object = t;
}
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int numArrayElements;
  static int numElements;
  static vector<listOfObjects<TrainInfoPerStation *> *> partition;
  recursionLevel++;
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  static int K = 4;     
  static int recursionLevel = -1;
  static int numArrayElements;
  static int numElements;
  static vector<listOfObjects<TrainInfoPerStation *> *> partition;
  recursionLevel++;
  if (recursionLevel == 0)
  {
    numArrayElements = (end + 1) / K + 1;//number of elements in array
    int Lindex = 0, Aindex = 0;//initialising
    listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;//saving without pointer so that it wont be changed by operations on currNode
    while (temp != NULL)//adding into vector
    {
      if (Lindex % K == 0)//only certain elements so that only n/k space to be used 
      {
        partition.push_back(temp);//adding into vector
        Aindex++;//increasing index
      }
      Lindex++;//total length
      temp = temp->next;//moving forward
    }
  }
  if (start < end)//partition 
  {
    srand(time(0));//seed changed
    int pivotIndex = start + (rand() % (end - start));//random value inside the region
    listOfObjects<TrainInfoPerStation *> *P = partition[pivotIndex / K];//finding partition
    for (int i = 0; i < pivotIndex % K; i++)
    {
      P = P->next;//reaching partition
    }
    listOfObjects<TrainInfoPerStation *> *head = partition[start / K];//finding start
    for (int i = 0; i < start % K; i++)
    {
      head = head->next;//reaching start
    }
    listOfObjects<TrainInfoPerStation *> *tail = partition[end / K];//finding tail
    for (int i = 0; i < end % K; i++)
    {
      tail = tail->next;//reaching tail
    }
    TrainInfoPerStation *p = P->object;//partition object being saved
    exchange(P, tail);//changing pivot to last
    listOfObjects<TrainInfoPerStation *> *array1 = head->prev;//initialisation
    listOfObjects<TrainInfoPerStation *> *array2 = head;//initialisation
    int k = start - 1;//to keep track of pivot position finally
    for (int j = start; j <= (end - 1); j++)
    {
      bool notequal = false;//checking equality
      int a, b;//2 numbers to be saved for weekdays
      for (int r = 0; r < 7; r++)
      {
        if (p->daysOfWeek[r])//which day of 1
        {
          b = r;
        }
      }
      for (int r = 0; r < 7; r++)//which day of 2
      {
        if (array2->object->daysOfWeek[r])
        {
          a = r;
        }
      }
      if (a < b)//checking to changed or not
      {
        notequal = true;
      }
      else if (a == b)//checking to changed or not
      {
        if (p->depTime >= array2->object->depTime)
        {
          notequal = true;
        }
      }
      if (notequal)//changing when required
      {
        k++;//pivot position
        if (array1 == NULL)
        {
          array1 = head;
        }
        else
        {
          array1 = array1->next;//array1 moving forward
        }
        exchange(array1, array2);//exchanging
      }
      array2 = array2->next;//moving forward
    }
    if (array1 == NULL)
    {
      array1 = head;//array1 moving forward
    }
    else
    {
      array1 = array1->next;//array1 moving forward
    }
    exchange(array1, tail);//changing pivot to its rightful place
    QuicksortSimple(stnInfoList, start, k );
    QuicksortSimple(stnInfoList, k + 2, end);
  }
  recursionLevel--;
  if (recursionLevel == -1)
  {
    partition.clear();
  }
  return;
}

#endif
