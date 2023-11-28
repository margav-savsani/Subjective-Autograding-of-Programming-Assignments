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
  listOfObjects<TrainInfoPerStation *> *temp=NULL, *next=NULL, *less=NULL, *more=NULL;
  while(temp != NULL)
    {

        next = temp->next;

        if(temp->value < pivot->value)
        {
            temp->next = less;
            less = temp;
        }
        else 
        {
            temp->next = more;
            more = temp;

        }
        temp = next;
    }
}
