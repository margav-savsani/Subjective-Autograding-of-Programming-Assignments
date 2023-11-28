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

void swap(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b){
  TrainInfoPerStation *temp = new TrainInfoPerStation(a->object->journeyCode, a->object->stopSeq, a->object->arrTime, a->object->depTime);
  for(int i=0; i<7; i++){
    temp->daysOfWeek[i]=a->object->daysOfWeek[i];
    a->object->daysOfWeek[i]=b->object->daysOfWeek[i];
    b->object->daysOfWeek[i]=temp->daysOfWeek[i];
  }
  a->object->arrTime=b->object->arrTime;
  b->object->arrTime=temp->arrTime;
  a->object->depTime=b->object->depTime;
  b->object->depTime=temp->depTime;
  a->object->journeyCode=b->object->journeyCode;
  b->object->journeyCode=temp->journeyCode;
  a->object->stopSeq=b->object->stopSeq;
  b->object->stopSeq=temp->stopSeq;

}

bool checkCondition(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b){
  for(int i=0; i<7; i++){

  }
}


listOfObjects<TrainInfoPerStation *> * partition(listOfObjects<TrainInfoPerStation *> *l, listOfObjects<TrainInfoPerStation *> *h) 
{ 
    // set pivot as h element 
     
  
    // similar to i = l-1 for array implementation 
    listOfObjects<TrainInfoPerStation *> *i = l->prev;
  
    // Similar to "for (int j = l; j <= h- 1; j++)" 
    for (listOfObjects<TrainInfoPerStation *> *j = l; j != h; j = j->next) 
    { 
      int day1=0;
      for(; day1<7; i++){
        if(j->object->daysOfWeek[day1]){
          break;
        }
        day1++;
      }
      int day2=0;
      for( ; day2<7; day2++){
        if(h->object->daysOfWeek[day2]){
          break;
        }
        day2++;
      }
        if (day1 < day2) 
        { 
            // Similar to i++ for array 
            i = (i == NULL)? l : i->next; 
  
            swap((i), (j)); 
        }
        else if(day1==day2){
          if(j->object->arrTime < h->object->arrTime){
            i = (i == NULL)? l : i->next; 
            swap(i,j);
          }
        } 
    } 
    i = (i == NULL)? l : i->next; // Similar to i++ 
    swap((i), (h)); 
    return i; 
}

listOfObjects<TrainInfoPerStation *>* pivotChoser(int k, int n, listOfObjects<TrainInfoPerStation *>* firststation){
  listOfObjects<TrainInfoPerStation *>* arr[n/k];
  listOfObjects<TrainInfoPerStation *>* currstn = firststation->next;
  for(int j=0; j<n/k; j++){
    if(j==0){
      arr[0]=firststation;
    }
    else{
      for(int i=0; i<k; i++){
        currstn=currstn->next;
      }
    arr[j]=currstn;
    }
  }
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  listOfObjects<TrainInfoPerStation *> *a = stnInfoList;
  int n=0; //number of elements in the list
  while(a!=nullptr){
    n++;
    a=a->next;
  }



}
