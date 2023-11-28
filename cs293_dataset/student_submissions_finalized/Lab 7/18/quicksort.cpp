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

listOfObjects<int> **list_divider(listOfObjects<int> *codes){
    int k=4;
    //int *arr;
     //= new int;

    listOfObjects<int> **arr;
    int i=0;
    while(codes != nullptr){
        int r = i%k;
        int q = i/k;
        if(r==0) arr[q] = new listOfObjects<int> (codes->object);
        else{
            arr[q]->next = new listOfObjects<int> (codes->object);
        }
        i++;
        codes=codes->next;
    }    
    return arr;
}

int pivot_chooser(listOfObjects<int> **array_of_list){
    
}


void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  
  //create a list with journey codes of the trains
  listOfObjects<int> *codes = new listOfObjects<int> (stnInfoList->object->journeyCode);
  listOfObjects<int> **divided_list = list_divider(codes);
  int pivot = pivot_chooser(divided_list);

}
