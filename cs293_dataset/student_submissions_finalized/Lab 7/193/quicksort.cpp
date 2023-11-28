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
listOfObjects<TrainInfoPerStation*> partition(listOfObjects<TrainInfoPerStation*>  ){
   //Returns the pointer to the NODE which has 


}

//Function to choose a pivot.
listOfObjects<TrainInfoPerStation *>* pivot(listOfObjects<TrainInfoPerStation *> *stnInfoList){
  //Takes in the head of the linked list and returns a pointer to the pivot choosen for the list.

}

//Sorts the list taking in the last element before which we need to do quicksort.
void RevQuicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList) 
{
  if(stnInfoList == NULL){
    return;
  }
  listOfObjects<TrainInfoPerStation *> *choosen = pivot(stnInfoList);
  while(choosen!=NULL){
    choosen = choosen->prev;
  }
  choosen = choosen->next; //First Node of the list.
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList) //Sorts the list in place.
//The list which has to be sorted according to date and time. 
{
  listOfObjects<TrainInfoPerStation *> *choosen = pivot(stnInfoList);
  Quicksort();
  RevQuicksort(choosen);
}
