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
  listOfObjects<TrainInfoPerStation *>* a;
  a = stnInfoList;
  //cout << a->object->journeyCode << endl;
  //int b = a->object->journeyCode;
  listOfObjects<TrainInfoPerStation*>* temp;
  temp = a;
  while(a->next != nullptr){
    a = a->next;
  }
}
