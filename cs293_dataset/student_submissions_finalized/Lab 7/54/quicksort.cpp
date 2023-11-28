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
if (len(stnInfoList <= 1) return stnInfOList;

    struct listnode *less=NULL, *more=NULL, *next, *endl, *temp=list;
    struct listnode *pivot = SelectPivot(stnInfoList);
    while(stnInfoList->next != NULL)
    {
       next = stnInfoList->next->next;

        if(stnInfoList->next->value < pivot->value)
        {
            stnInfoList->next->next = less;
            less = stnInfoList->next;
        }
        else 
        {
            stnInfoList->next = more;
            more = stnInfoList;

        }
        stnInfoList = next;
    }
  
  }
