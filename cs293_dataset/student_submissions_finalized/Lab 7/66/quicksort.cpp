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

unsigned short pivotchoice(listOfObjects<TrainInfoPerStation *> *stnInfoList,int k){
   int i=0;
   
   listOfObjects<TrainInfoPerStation *> *x=listOfObjects<TrainInfoPerStation *> *stnInfoList
   unsigned short ch = stnInfoList->object->stopSeq;
   for(int j=0;j<k;j++){ 
       
        if( x->next==nullptr ) break;
        if(x->next->object->stopSeq>x){ ch = x->next->object->stopSeq; }
        x = x->next;    
   }
   return ch;
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
   unsigned short choice = pivotchoice(listOfObjects<TrainInfoPerStation *> *stnInfoList,int k);
   
   
}
