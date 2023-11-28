#ifndef STD_HEADERS
#include "std_headers.h"
#endif
#include<cstdlib>
#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif
listOfObjects<TrainInfoPerStation *> *
listOfObjects<TrainInfoPerStation *> * partition(listOfObjects<TrainInfoPerStation *> *&stnInfoList,listOfObjects<TrainInfoPerStation *> *start,listOfObjects<TrainInfoPerStation *> * finish){

}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
   listOfObjects<TrainInfoPerStation *>* start=stnInfoList,*finish;
   listOfObjects<TrainInfoPerStation *>* currst=start,*prevst;
   while(currst!=nullptr){
    prevst=start;
    currst=currst->next;

   }
   finish=prevst;
   int i=partition(stnInfoList,start,finish);

}  
