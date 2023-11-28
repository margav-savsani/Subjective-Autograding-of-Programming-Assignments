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
  int k = 10;
  listOfObjects<TrainInfoPerStation *> *point = stnInfoList;
  int n;
  while (point != nullptr)
  {
    point = point->next;
    n++;
  }

  // Put your code here.
}

void swap(listOfObjects<TrainInfoPerStation *> *s1, listOfObjects<TrainInfoPerStation *> *s2)
{
  TrainInfoPerStation *temp;
  temp = new TrainInfoPerStation(s2->object->journeyCode, s2->object->stopSeq, s2->object->arrTime, s2->object->depTime);
  for (int i = 0; i < 7; i++)
  {
    temp->daysOfWeek[i] = s2->object->daysOfWeek[i];
    s2->object->daysOfWeek[i] = s1->object->daysOfWeek[i];
    s1->object->daysOfWeek[i] = temp->daysOfWeek[i];
  }
  s2->object->arrTime = s1->object->arrTime;
  s1->object->arrTime = temp->arrTime;
  s2->object->depTime = s1->object->depTime;
  s1->object->depTime = temp->depTime;
  s2->object->journeyCode = s1->object->journeyCode;
  s1->object->journeyCode = temp->journeyCode;
  s2->object->stopSeq = s1->object->stopSeq;
  s1->object->stopSeq = temp->stopSeq;
}

listOfObjects<TrainInfoPerStation *> *partition(listOfObjects<TrainInfoPerStation *> *l, listOfObjects<TrainInfoPerStation *> *h)
{
  // set pivot as h element
  int day;
  for (day = 0; day < 7; day++)
  {
    if (h->object->daysOfWeek[day])
    {
      break;
    }
  }

  // similar to i = l-1 for array implementation
  listOfObjects<TrainInfoPerStation *> *i = l->prev;

  // Similar to "for (int j = l; j <= h- 1; j++)"
  for (listOfObjects<TrainInfoPerStation *> *j = l; j != h; j = j->next)
  {
    int day2;
    for (day2 = 0; day2 < 7; day2++)
    {
      if (j->object->daysOfWeek[day2])
      {
        break;
      }
    }

    if (day2 < day)
    {
      swap(i,j);
      // Similar to i++ for array
      i = (i == NULL) ? l : i->next;

      
    }
    else if (day2==day){
      if(j->object->arrTime < h->object->arrTime){
        swap(i,j);

      }
    }
  }
  i = (i == NULL) ? l : i->next; // Similar to i++
  
  return i;
}

listOfObjects<TrainInfoPerStation *> *pivotchooser(listOfObjects<TrainInfoPerStation *> *stnInfoList, int n, int k){
 listOfObjects<TrainInfoPerStation *>* array[n/k];
 for(int i=0;i<(n/k);i++){
  for(int j=0;j<k;j++){
    if(j==0){
      array[i]=stnInfoList;
    }
    stnInfoList=stnInfoList->next;
  }
 }

 float x=rand();


}