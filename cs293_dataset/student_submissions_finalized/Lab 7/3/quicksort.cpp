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
  // Put your code here.

    // Return NULL list
    if (ListLength(list) <= 1) return list;

    struct listnode *less=NULL, *more=NULL, *next, *endl, *temp=list;

    /*Select a random pivot point*/
    struct listnode *pivot = SelectPivot(list);

    printf("Pivot Value = %lo\n", pivot->value);



    /*Divide & Conquer*/
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



    less = Quicksort(less);
    more = Quicksort(more);

    // Merge
    if(ListLength(less)!=0)
    {       
        while(endl != NULL)
        {
            endl = less->next;
            less->next = more;
            more = less;
            less = endl;
        }

        return more;        
    }
}
