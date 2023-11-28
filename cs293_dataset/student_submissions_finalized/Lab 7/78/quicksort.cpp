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

#include<ctime>


/*
//function which will choose a random pivot
TrainInfoPerStation *choose_pvt(listOfObjects<TrainInfoPerStation *> list , int K){
  //array to store the n/k th element in the list into the array
  listOfObjects<TrainInfoPerStation *> temp = list;
  TrainInfoPerStation *array = new TrainInfoPerStation(K);
  int cnt=0;
  while(temp->next != NULL){
    if(cnt%k == 0){
      array[cnt] = list;
    }
    cnt ++;
    temp=temp->next;
  }
  srand(time(0)); 
  int index=rand()%cnt;
  //


  //
}
*/

void partition(listOfObjects<TrainInfoPerStation *> list , int K){

}

void quicksort(listOfObjects<TrainInfoPerStation *> *start , listOfObjects<TrainInfoPerStation *> *end){
  if(end != NULL && start!=end && start!=end->next){ 
    listOfObjects<TrainInfoPerStation *> *mid=partition(start, end, K);
    quicksort(start , mid->prev , K);
    quicksort(mid->next , end , K);
  }
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *curr=stnInfoList;
  int K=4;
  //to get the last element of the list
  while(curr && curr->next){
    curr=curr->next;
  }
  //call to the quicksort function which will sort the list with starting and ending objects as stnInfoList and curr respectively
  quicksort(stnInfoList, curr, k);
  // Put your code here.
}
