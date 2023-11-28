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

int getlength(listOfObjects<T> X){
  return((X->tail)-(X->head));
}

void sortquick(Journey*j,head, tail){
    s->list = j;
    Quicksort(head,tail);
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  for(int i = 0; i < stnInfoList.length(); i++)
    {
      stnInfoList[i]->journeyCode
    }
    if(head<tail){
        int q = pivot(list,head,tail);
        Quicksort(list[0],q);
        Quicksort(q+1,list[stnInfolist.length()-1]);
        return true;
    }
    return false;
}
