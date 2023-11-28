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

#define CONS_VAL 1
#define FINAL 8

static const int k = 4;

void swap_train_data(TrainInfoPerStation *&train_1, TrainInfoPerStation *&train_2){
    int journey_temp = train_1 -> journeyCode;
    train_1 -> journeyCode = train_2 -> journeyCode;
    train_2 -> journeyCode = journey_temp;
    
    int arrTime_temp = train_1 -> arrTime;
    train_1 -> arrTime = train_2 -> arrTime;
    train_2 -> arrTime = arrTime_temp;
    
    int deptTime_temp = train_1 -> depTime;
    train_1 -> depTime = train_2 -> depTime;
    train_2 -> depTime = deptTime_temp;
    
    unsigned short seq_temp = train_1 -> stopSeq;
    train_1 -> stopSeq = train_2 -> stopSeq;
    train_2 -> stopSeq = seq_temp;
    
    int i = 0;
    while(i < 7){
        bool dayofweek_temp = train_1 -> daysOfWeek[i];
        train_1 -> daysOfWeek[i] = train_2 -> journeyCode;
        train_2 -> daysOfWeek[i] = dayofweek_temp;
        i++;
    }
}

listOfObjects<TrainInfoPerStation *> *train_station_number(listOfObjects<TrainInfoPerStation *> *a[], int train_number){
    listOfObjects<TrainInfoPerStation *> *return_list = a[train_number/k];
    
    int i = 0;
    while(i < (train_number % k)){
        return_list = return_list->next;
        i++;
    }
    return return_list;
}

int funciton(bool* day, int T){
    int i = 0, j = 0, t;
    while(i < 7){
        if (day[i] == false){ continue;}
        else{
            t = CONS_VAL;
            t *= i;
            break;
        }
        i++;
    }
    
    while(j < 7){
        if (day[j] == false){j++;}
        else break;
    }
    
    if(j == 7) return FINAL + T;
    else return t + T;
}

int get_pivot(listOfObjects<TrainInfoPerStation *> **store_ls, int start, int end){
    if (start >= end) return -1;
    
    srand(time(NULL));
    int random_piv, r_value = start;
    random_piv = start + rand() % (end - start + 1);
    
    listOfObjects<TrainInfoPerStation *> *piv;
    piv = train_station_number(store_ls, random_piv);
    listOfObjects<TrainInfoPerStation *> *first_point;
    first_point = train_station_number(store_ls, start);
    listOfObjects<TrainInfoPerStation *> *end_store;
    end_store = train_station_number(store_ls, end);
    listOfObjects<TrainInfoPerStation *> *end_point;
    end_point = end_store;

    swap_train_data(piv->object, end_store->object);
    
    for(int a = 0; first_point != end_point; a++){
        if(funciton(end_store->object->daysOfWeek, end_store->object->depTime) > funciton(first_point->object->daysOfWeek, first_point->object->depTime)){
            first_point = first_point->next;
            r_value++;
        }
        else{
            for(int a = 0; first_point != end_point; a++){
                if(funciton(end_point->object->daysOfWeek, end_point->object->depTime) > funciton(end_store->object->daysOfWeek, end_store->object->depTime)){
                    end_point = end_point->prev;
                }
                else {
                    r_value++;
                    swap_train_data(first_point->object, end_point->object);
                    first_point = first_point->next;
                    break;
                }
            }
        }
    }
    swap_train_data(first_point->object, end_store->object);
    return r_value;
}

void Quick(listOfObjects<TrainInfoPerStation *> **store_ls, int start, int end){
    if (start >= end) return;
    int value = get_pivot(store_ls, start, end);
    Quick(store_ls, value + 1, end);
    Quick(store_ls, start, value - 1);
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
  
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it *once* using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.
  //
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will end up using much more than n/K space
  // overall.  So you MUST NOT allocate space in each recursive call.
  //
  // A variable/array defined using static is not created afresh in
  // each recursive call.  Instead, a single copy of it is maintained
  // across all recursions.
  
  if (recursionLevel == 0) {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
  }
  
  // Put your code for the core of Quicksort here

  // Decrement recursion level before leaving the function
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end){
    int length, i = 0;
    listOfObjects<TrainInfoPerStation *> *store_stnInfoList = stnInfoList;

    if ((end - start + 1) % k == 0) length = (end - start + 1)/k;
    else length = (end - start + 1 + k)/k;

    listOfObjects<TrainInfoPerStation *> *store_ls[length];

    while(i<length){
        store_ls[i] = stnInfoList;
        listOfObjects<TrainInfoPerStation *> *store_list;
        store_list = stnInfoList;

        int j = 0;
        while(j<k){
            if(store_list==nullptr) break;
            else store_list = store_list->next;
            j++;
        }
        stnInfoList = store_list;
        i++;
    }
    Quick(store_ls, start, end);
}

#endif
