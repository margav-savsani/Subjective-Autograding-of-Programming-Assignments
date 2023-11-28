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

listOfObjects<TrainInfoPerStation *> *Selectpivot(listOfObjects<TrainInfoPerStation *> *stnInfoList,int len){
    int k =0,p =1;
    if(len < 5){k = 1+rand()%len; }
    else{ k = 1+rand()%5; }
    listOfObjects<TrainInfoPerStation *> *m = stnInfoList;
    while(p < k){
      m = m->next;
      p++;
    }
    return m;
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{

  // Put your code here.
}
