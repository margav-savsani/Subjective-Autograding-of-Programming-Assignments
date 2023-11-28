#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

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

int listLength(listOfObjects<TrainInfoPerStation *> *stnInfoList){

    listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
    int i=0;
    while(temp!=NULL)
    {
        i++;
        temp=temp->next;
    }
    return i;
}

/*==================
in every for loop static int ...
====================
*/

int compare(TrainInfoPerStation* &obj1, TrainInfoPerStation* &obj2){
  // 1 for less than is true, 2 for equal is true and 3 for greater than
  static int i=0;
  for(i=0; i<7; i++){
    
    if( obj1->daysOfWeek[i] && obj2->daysOfWeek[i]==false )
      return 1; 
    
    else if(obj1->daysOfWeek[i]==false && obj2->daysOfWeek[i] )
      return 3;

    else if(obj1->daysOfWeek[i] && obj2->daysOfWeek[i]){
      if(obj1->arrTime < obj2->arrTime)
        return 1;
      else if( obj1->arrTime > obj2->arrTime )
        return 3;
      else 
        return 2;
    }

  }
}

void mySwap( TrainInfoPerStation* &obj1, TrainInfoPerStation* &obj2 ){
  static TrainInfoPerStation* temp = new TrainInfoPerStation(obj1->journeyCode, obj1->stopSeq, obj1->arrTime, obj1->depTime);
  static int i=0;

  temp->arrTime = obj1->arrTime;
  temp->depTime = obj1->depTime;
  temp->journeyCode = obj1->journeyCode;
  temp->stopSeq = obj1->stopSeq;
  for(i=0; i<7; i++){
    if(obj1->daysOfWeek[i])
      temp->setDayOfWeek(i);
    else
      temp->resetDayOfWeek(i);
  }

  obj1->arrTime = obj2->arrTime;
  obj1->depTime = obj2->depTime;
  obj1->journeyCode = obj2->journeyCode;
  obj1->stopSeq = obj2->stopSeq;
  for(i=0; i<7; i++){
    if(obj2->daysOfWeek[i])
      obj1->setDayOfWeek(i);
    else
      obj1->resetDayOfWeek(i);
  }

  obj2->arrTime = temp->arrTime;
  obj2->depTime = temp->depTime;
  obj2->journeyCode = temp->journeyCode;
  obj2->stopSeq = temp->stopSeq;
  for(i=0; i<7; i++){
    if(temp->daysOfWeek[i])
      obj2->setDayOfWeek(i);
    else
      obj2->resetDayOfWeek(i);
  }

}

int partition(listOfObjects<TrainInfoPerStation *> **&arr, int &left, int &right, int &K, int &n, int& start, int& end){

  static int pivot, countRem, Quo, lcountRem, lQuo, rcountRem, rQuo;
  static listOfObjects<TrainInfoPerStation *> *pivotptr, *leftptr, *rightptr;
  static TrainInfoPerStation *train = new TrainInfoPerStation(-1, -1, -1, -1);
  static listOfObjects<TrainInfoPerStation *> *pivotObj = new listOfObjects<TrainInfoPerStation *>(train);
  static int i=0;
  //static things

  if(left<0 || right>=n)
    return -1;

  pivot = left + rand()%(right-left+1);
  // pivot = right;
  countRem = pivot%K;
  Quo = pivot/K;
  pivotptr = arr[Quo];
  while( countRem--){
    pivotptr = pivotptr->next;
  }
  //once i got my pivotptr just copy the things to pivotObj and use pivotObj- train to compare
  train->arrTime = pivotptr->object->arrTime;
  train->depTime = pivotptr->object->depTime;
  train->journeyCode = pivotptr->object->journeyCode;
  train->stopSeq = pivotptr->object->stopSeq;
  for(i=0; i<7; i++){
    if(pivotptr->object->daysOfWeek[i])
      train->setDayOfWeek(i);
    else
      train->resetDayOfWeek(i);
  }

  lcountRem = left%K;
  lQuo = left/K;
  leftptr = arr[lQuo];
  while(lcountRem--){
    leftptr = leftptr->next;
  }

  rcountRem = right%K;
  rQuo = right/K;
  rightptr = arr[rQuo];
  while(rightptr!=nullptr && rcountRem--){
    rightptr = rightptr->next;
  }
  //now i have my pivotptr rightptr and everything ....place the pivot at the left most position
  mySwap(pivotptr->object, leftptr->object);
  pivotptr = leftptr;

  while(left < right){

    while( leftptr!=nullptr && compare(leftptr->object, train) != 3 ) //less than equal both cases to be taken
    {
      leftptr = leftptr->next;
      left++;
    }

    while ( rightptr!=nullptr && compare(rightptr->object, train) == 3 ) //strictly greater than
    {
      rightptr = rightptr->prev;
      right--;
    }

    if(left<right){
      mySwap(leftptr->object, rightptr->object);
    }

  }
 
    mySwap(rightptr->object, pivotptr->object);//since pivot wont be changed
    //i assured that last element would be pivot
    //also right == start case will only have the first elemnt eitther less than pivot or equal to pivot
    //which is what we want ...see quicksort

  

  return right;

}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;
  // Put your code here.
  static int n = listLength(stnInfoList);

  static listOfObjects<TrainInfoPerStation *> **arr = new listOfObjects<TrainInfoPerStation *> *;
  static int ai=0, sj=0; //i for arr and j for stnInfolist
  static listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
  

  static int startToPass, endToPass;
  // static int parti;
  if(recursionLevel==0){
    n = listLength(stnInfoList);
    temp = stnInfoList;
    ai=0; sj=0;
    while(sj<n){
      if(sj%K==0){
        arr[ai] = temp;
        ai++;
      }
      temp = temp->next;
      sj++;
    }
  }

  if( start<end ){
    startToPass = start;
    endToPass = end;
    int parti = partition(arr, startToPass, endToPass, K, n, start, end);
    
      QuicksortSimple( **&arr, start, parti-1);
      QuicksortSimple(**&arr, parti+1, end);

  }

  recursionLevel--;
  return;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  recursionLevel++;
  // Put your code here.
  static int n = listLength(stnInfoList);

  static listOfObjects<TrainInfoPerStation *> **arr = new listOfObjects<TrainInfoPerStation *> *;
  static int ai=0, sj=0; //i for arr and j for stnInfolist
  static listOfObjects<TrainInfoPerStation *> *temp = stnInfoList;
  static int start, end;

  static int startToPass, endToPass;
  // static int parti;
  if(recursionLevel==0){
    
    n = listLength(stnInfoList);
    start = recursionLevel;
    end = n-recursionLevel-1;
    temp = stnInfoList;
    ai=0; sj=0;
    while(sj<n){
      if(sj%K==0){
        arr[ai] = temp;
        ai++;
      }
      temp = temp->next;
      sj++;
    }
  }

  if( start<end ){

    int helpStart = start;
    int helpEnd = end;
    startToPass = start;
    endToPass = end;

    int parti = partition(arr, startToPass, endToPass, K, n, start, end);
  
      start = helpStart;
      end = parti-1;
      Quicksort( **&arr);

      start = parti+1;
      end = helpEnd;
      Quicksort(**&arr);    


  }

  recursionLevel--;
  return;
}

#endif
