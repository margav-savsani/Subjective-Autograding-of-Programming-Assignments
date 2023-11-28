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

void swaplink(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b)
{
  TrainInfoPerStation *temp = a->object;
  a->object = b->object;
  b->object = temp;
  temp = nullptr;
}

listOfObjects<TrainInfoPerStation *> *Partition(listOfObjects<TrainInfoPerStation *> *p, listOfObjects<TrainInfoPerStation *> *r, listOfObjects<TrainInfoPerStation *> *pivot)
{
  listOfObjects<TrainInfoPerStation *> *pivot = random_pivot_selector();
  listOfObjects<TrainInfoPerStation *> *i = p->prev;
  listOfObjects<TrainInfoPerStation *> *j = p;
  while (j != r->next)
  {
    if (j->object->daysOfWeek < pivot->object->daysOfWeek || ((j->object->daysOfWeek < pivot->object->daysOfWeek) && (j->object->arrTime < pivot->object->arrTime))){
      i = i->next;
      swaplink(i, j);
    }
    
  }
}

listOfObjects<TrainInfoPerStation *> *random_pivot_selector(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  return stnInfoList;
}
void QuicksortRecursive(listOfObjects<TrainInfoPerStation *> *p, listOfObjects<TrainInfoPerStation *> *r)
{
  listOfObjects<TrainInfoPerStation *> *q = Partition(p, r);
  QuicksortRecursive(p, q->prev);
  QuicksortRecursive(q->next, r);
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.

  listOfObjects<TrainInfoPerStation *> i, j;
}
