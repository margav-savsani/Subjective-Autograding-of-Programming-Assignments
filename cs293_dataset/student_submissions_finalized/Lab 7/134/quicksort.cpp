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

//////////////////////////////
listOfObjects<TrainInfoPerStation *> *inplaceSorter(listOfObjects<TrainInfoPerStation *> *start, listOfObjects<TrainInfoPerStation *> *end=NULL){
    int finishstore = finish;
    start--;
    finish++;
    while(true){
        while(finish > 0 && *pivot < array[--finish]){ // or !(array[finish] >= pivot)
            comparisons++;
        }
        while(start < finishstore && array[++start] < *pivot){
            comparisons++;
        }
        comparisons+=2;
        if(finish == finishstore && start == finishstore){ //this is if pivot it last and largest element
            return finish-1;
        }
        else if(start < finish){
            Journey var = array[start];
            array[start] = array[finish];
            array[finish] = var;
        }
        /*else if(start == finish){
            return finish+1;
        }*/
        else{
            //for(int i=start; i<=finish; i++)
            //    cout << i << ":" << array[i].getJourneyCode() << "  ";
            //cout << endl;
            return finish;
        }
    }
}

listOfObjects<TrainInfoPerStation *> *genpivot(listOfObjects<TrainInfoPerStation *> *start, listOfObjects<TrainInfoPerStation *> * end){

}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> endofList=NULL)
{
  // Put your code here.
    listOfObjects<TrainInfoPerStation *> pivot = genpivot(stnInfoList, endofList);
    listOfObjects<TrainInfoPerStation *> partition = inplaceSorter(pivot, stnInfoList, endofList);
    Quicksort(stnInfoList, partition);
    Quicksort(partition->next);
  
    return true;

}






