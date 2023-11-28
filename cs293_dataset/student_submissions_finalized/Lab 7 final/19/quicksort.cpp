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


void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  static int K = 4; 
  static int recursionLevel = -1; 
  
  static int n = 0;
  static listOfObjects<TrainInfoPerStation *>* *array = nullptr;
  recursionLevel++;
  
  if (recursionLevel == 0) {
		;
  }
  

  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  static int K = 4;
  static int recursionLevel = -1;

  static int n = 0;
  static listOfObjects<TrainInfoPerStation *>* *array = nullptr;
  //using static list to access the same array in every recursive call without calculating it again.

  recursionLevel++;


  if (recursionLevel == 0) {
    listOfObjects<TrainInfoPerStation *> *a;
    a = stnInfoList;

    int n = 0;
    while(a != nullptr){
      n += 1;
      a = a->next;
    }
    int size = (n / K) + 1;

    array =  new listOfObjects<TrainInfoPerStation *>* [size];

    listOfObjects<TrainInfoPerStation *> *b;
    b = stnInfoList;

    int count = 0;
    
    while(true){
      array[count] = b;
      count += 1;
      if(count == size){ //it will check until count beomes size.
        break;
      }
      for(int i =0; i < K; i++){
        b = b->next;
      }
    }
  }

  // It should only sort if start < end..
  if(start < end){
    int index = start + rand()%(end - start + 1);  //found the random index with in range [start, end] 

    listOfObjects<TrainInfoPerStation *> *pivot;

    pivot = array[index/K];
    for(int i = 0; i < (index % K); i++){
      pivot = pivot->next;  //we choose pivot with O(K) with 
    }

    listOfObjects<TrainInfoPerStation *> * last; 
    listOfObjects<TrainInfoPerStation *> * first;
    first = stnInfoList;
    last = stnInfoList;
    for(int i = 0; i < start; i++){
      first = first->next; //got the pointer with index: start
    }
    for(int j = 0; j < end; j++){
      last = last->next;  //got the pointer with index: end
    }
    //calculated the first and last pointer.
    //cout << "step-1" << endl;

    swap(pivot->object,last->object); // swapped the pivot and last.
    //cout << "step-2" << endl;
     
      //partition function implementation.
      listOfObjects<TrainInfoPerStation *> * train_i;
      train_i = first;
      listOfObjects<TrainInfoPerStation *> * train_j;
      train_j = first;

      int i = start -1;
      for(int j = start-1; j <= end -1; j++){
        int tra_j = 0;
        int tra_last = 0;

        for(int k = 0; k < 7; k++){
          if(train_j->object->daysOfWeek[k]){
            tra_j = k;
          }
        }
        for(int k = 0; k < 7; k++){
          if(last->object->daysOfWeek[k]){
            tra_last = k;
          }
        }

        if((tra_j < tra_last) || (train_j->object->depTime < last->object->depTime && tra_j == tra_last) || 
         (train_j->object->depTime == last->object->depTime && tra_j == tra_last && train_j->object->arrTime < last->object->arrTime) ){
          // if condition for sorting 
          i++;
          swap(train_i->object,train_j->object);
          train_i = train_i->next;
        }
        train_j = train_j->next;
      }

      swap(train_i->object, last->object);
      //cout << "last-step-also-done" << endl;
    int x = i+1;
    //partition function implementation done.
    
      //calling recursiely the next two.
      QuicksortSimple(stnInfoList, start, x -1);
      QuicksortSimple(stnInfoList, x+1, end);
    }

  recursionLevel--;
  return;
}

#endif
