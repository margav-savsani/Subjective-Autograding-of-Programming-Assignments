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

void Partion(listOfObjects<TrainInfoPerStation *> *stnInfoList , int k){
   
     
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{     int N,k;
      listOfObjects<TrainInfoPerStation *> *station_list = stnInfoList;
      TrainInfoPerStation *currInfo;
      currInfo = station_list->object;
      int c=N/k;
      TrainInfoPerStation * Array[N/k];
      for (int i=0;i<N;i++){
        currInfo = station_list->object;
            if (i%(c)==0){
              Array[i/c]= currInfo;
              station_list=station_list->next;
          }
          else{
              station_list=station_list->next;
          }
      }

  
  
  
  // Put your code here.
}
