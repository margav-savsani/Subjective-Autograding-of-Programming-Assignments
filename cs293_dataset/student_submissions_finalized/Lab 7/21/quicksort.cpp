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

#include<cstdlib>

// listOfObjects<TrainInfoPerStation *>* pickrandompivot(int n, ){
//   int i = rand()%n;
//   int j = n/4;
//   while
// }

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  int k = 4;
  int j=1;
  int size = 0;
  listOfObjects<TrainInfoPerStation *>* *arr = new listOfObjects<TrainInfoPerStation *>*(stnInfoList);
  listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
  while (temp != nullptr){
    if (j%4 == 0) arr[j/4] = temp;
    j++;
    size++;
    temp = temp->next;
  }

  int i = rand()%size;
  int q = i/4;
  int r = i%4;

  listOfObjects<TrainInfoPerStation *> *pivot = arr[q];
  for (int k=0; k<r;k++){
    if (pivot->next != nullptr){
      pivot = pivot->next;
    }
    else break;
  }

}
