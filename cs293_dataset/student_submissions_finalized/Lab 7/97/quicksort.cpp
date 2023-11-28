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
#include <random>

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  if(stnInfoList == nullptr)
    return;
  listOfObjects<TrainInfoPerStation *> *first = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *last = nullptr;
  int num = 1;
  while(true){
    if(temp->next == nullptr){
      last = temp;
      break;
    }
    temp = temp->next;
    num++;
  }
  recurseQuick(stnInfoList, first, last, num);
}

void recurseQuick(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> *first, listOfObjects<TrainInfoPerStation *> *last,int num){
  if(first == last)
    return;
  else{
    int pivotIdx;
    listOfObjects<TrainInfoPerStation *> *pivot = Partition(stnInfoList, first, last, num, pivotIdx);
    recurseQuick(stnInfoList, first, pivot->prev, pivotIdx);
    recurseQuick(stnInfoList, pivot->next, last, num-pivotIdx);
    //check for various test cases, pivot can be last or first as well, also any other pivot
  }
}

listOfObjects<TrainInfoPerStation *> * Partition(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> *first, listOfObjects<TrainInfoPerStation *> *last, int num, int &pivotIdx){
  random_device dev;
  mt19937 rng(dev());
  uniform_int_distribution<mt19937::result_type> dist(0, num-1);
  int n = dist(rng);
  cout << n << endl;
  listOfObjects<TrainInfoPerStation *> *pivot = first;
  for (int i = 0; i<= n; i++)
    pivot = pivot->next;
  
}