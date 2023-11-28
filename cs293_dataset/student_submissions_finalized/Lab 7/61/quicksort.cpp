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

void Quicksort(listOfObjects <TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation> *input = NULL;
  listOfObjects<TrainInfoPerStation *> *current = stnInfoList;
  while (current != NULL)
  {
    for (int i = 0; i < 7; i++)
    {
      if (current->object->daysOfWeek[i])
      {
        listOfObjects<TrainInfoPerStation> *newentry = new listOfObjects<TrainInfoPerStation> (TrainInfoPerStation(current->object->journeyCode,current->object->stopSeq, current->object->arrTime,current->object->depTime));
        newentry->object.setDayOfWeek(i);
        newentry->next = input;;
        input = newentry;
      }
    }
    current = current->next;
  }
  

}
