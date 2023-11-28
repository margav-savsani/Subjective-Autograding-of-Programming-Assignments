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

int K = 5;

bool operator<(TrainInfoPerStation t1,TrainInfoPerStation t2){
    for(int i=0;i<7;i++){
        if (t1.daysOfWeek[i] < t2.daysOfWeek[i]) return true;
        else if (t1.daysOfWeek[i] > t2.daysOfWeek[i]) return false;
        else if (t1.daysOfWeek[i] == 1){
            if (t1.arrTime < t2.arrTime){
                return true;
            }
            else return false;
        }
    }
    return false;
}

void partition(listOfObjects<TrainInfoPerStation *> *stnInfoList){
    
}



void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  


}
