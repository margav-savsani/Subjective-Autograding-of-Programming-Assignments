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

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int numArrayElements;
  static int numElements;
  static vector<listOfObjects<TrainInfoPerStation *> *> myArray;
  recursionLevel++;
  recursionLevel--;
  return;
}

void swaps(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b)
{
  TrainInfoPerStation *t = a->object;
  a->object = b->object;
  b->object = t;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4;               // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static int numArrayElements;
  static int numElements;
  // Vector uses space n/K.
  static vector<listOfObjects<TrainInfoPerStation *> *> myArray;
  // Increment recursion level on entering the function
  recursionLevel++;
  if (recursionLevel == 0)
  {
    numArrayElements = (end + 1) / K + 1;
    int ListIndex = 0, ArrayIndex = 0;
    listOfObjects<TrainInfoPerStation *> *currentNode = stnInfoList;
    while (currentNode != NULL)
    {
      // only n/K times it goes inside the loop.
      if (ListIndex % K == 0)
      {
        // Adds elements which are Listindex % K in the vector.
        myArray.push_back(currentNode);
        ArrayIndex++;
      }
      ListIndex++;
      currentNode = currentNode->next;
    }
  }
  // Checks appropriate case
  if (start < end)
  {
    // Generatimg random number
    srand(time(0));
    int pivotIndex = start + (rand() % (end - start));
    // Getting pivot in time O(K)
    listOfObjects<TrainInfoPerStation *> *Pivot = myArray[pivotIndex / K];
    for (int i = 0; i < pivotIndex % K; i++)
    {
      Pivot = Pivot->next;
    }
    // Find head in time complexity O(K)
    listOfObjects<TrainInfoPerStation *> *head = myArray[start / K];
    for (int i = 0; i < start % K; i++)
    {
      head = head->next;
    }
    // Find tail in time complexity O(K)
    listOfObjects<TrainInfoPerStation *> *tail = myArray[end / K];
    for (int i = 0; i < end % K; i++)
    {
      tail = tail->next;
    }
    TrainInfoPerStation *pivot = Pivot->object;
    // Swaps the tail and Pivot
    swaps(Pivot, tail);

    // Partition
    listOfObjects<TrainInfoPerStation *> *iList = head->prev;
    listOfObjects<TrainInfoPerStation *> *jList = head;
    int k = start - 1;
    for (int j = start; j <= (end - 1); j++)
    {
      //************Checks for inequality**************
      bool inequality = false;
      int m, n;
      for (int l = 0; l < 7; l++)
      {
        if (pivot->daysOfWeek[l])
        {
          n = l;
        }
      }
      for (int l = 0; l < 7; l++)
      {
        if (jList->object->daysOfWeek[l])
        {
          m = l;
        }
      }
      if (m < n)
      {
        inequality = true;
      }
      else if (m == n)
      {
        if (pivot->depTime == jList->object->depTime)
        {
          if (pivot->arrTime >= jList->object->arrTime)
          {
            inequality = true;
          }
        }
        if (pivot->depTime >= jList->object->depTime)
        {
          inequality = true;
        }
      }
      //*********************************************
      if (inequality)
      {
        k++;
        if (iList == NULL)
        {
          iList = head;
        }
        else
        {
          iList = iList->next;
        }
        swaps(iList, jList);
      }
      jList = jList->next;
    }
    if (iList == NULL)
    {
      iList = head;
    }
    else
    {
      iList = iList->next;
    }
    // swaps pivot with iList (Pivot made partition here)
    swaps(iList, tail);
    k++;
    // partition finishes
    // Calling function recursively
    QuicksortSimple(stnInfoList, start, k - 1);
    QuicksortSimple(stnInfoList, k + 1, end);
  }
  recursionLevel--;
  // clearing the static vector before leaving function, as it can give wrong output if function called 2 times.
  if (recursionLevel == -1)
  {
    myArray.clear();
  }
  return;
}

#endif
