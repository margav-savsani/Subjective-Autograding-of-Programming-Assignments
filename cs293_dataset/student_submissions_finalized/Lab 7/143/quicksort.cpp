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
  int k = 4;
  int n = 1;
  listOfObjects<TrainInfoPerStation *> *head = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *head1 = stnInfoList;
  while(head->next!=nullptr){
    head = head->next;
    n++;
  }
  listOfObjects<TrainInfoPerStation *> *pivot[n/k];
  for(int i = 0;i < n/k ; i++){
    pivot[i] = head1;
    for(int j = 0 ;j<k;j++){
      head1 = head1->next;
    }
  }


}
