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

#ifndef RANDOM
#include <random>
#include <ctime>
#endif

int random_number(int start, int end){
  srand(time());
  return start + rand()%(end - start);
}

listOfObjects<TrainInfoPerStation*> get_last(listOfObjects<TrainInfoPerStation*>* lst){
  listOfObjects<TrainInfoPerStation*>* tmp = lst;
  while (tmp -> next != nullptr) tmp = tmp -> next;
  return tmp -> obejct;
}

void swap(listOfObjects<TrainInfoPerStation*> &e1, listOfObjects<TrainInfoPerStation*> &e2){
  TrainInfoPerStation*  e1_info = (e1 -> object);
  TrainInfoPerStation*  e2_info = (e2 -> object);
  e1 -> object = e2_info;
  e2 -> object = e1_info;
}

listOfObjects<TrainInfoPerStation*> operator < (listOfObjects<TrainInfoPerStation*> ob2){
  for (int i = 0; i < 7; i++){
    if (this -> daysOfWeek[i] == false && ob2 -> daysOfWeek[i] == false) continue;
    else if (this -> daysOfWeek[i] == true && ob2 -> daysOfWeek[i] == false) return false;
    else if (this -> daysOfWeek[i] == false && ob2 -> daysOfWeek[i] == true) return true;
    else if (this -> daysOfWeek[i] == true && ob2 -> daysOfWeek[i] == true){
      if (this -> arrTime == ob2 -> arrTime) return this -> depTime < ob2 -> depTime;
      else return this -> arrTime < ob2 -> arrTime;
    }
  }
}

int partition(int start, int end, listOfObjects<TrainInfoPerStation*>* stnInfoList){
  swap(stnInfoList + random_number(start,end), get_last(stnInfoList));

}

void Quicksort(listOfObjects<TrainInfoPerStation*>* stnInfoList)
{
  
}
