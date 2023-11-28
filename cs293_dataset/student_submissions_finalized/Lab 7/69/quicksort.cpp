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

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList){
    // Put your code here.
    listOfObjects<TrainInfoPerStation *> last;
    listOfObjects<TrainInfoPerStation *> pivot;
    int len = 0;0
    listOfObjects<TrainInfoPerStation *> *node = *stnInfoList;
    while(node != nullptr){
        len++;
        last = node;
        node = node->next;
    }
    int pivotpos = len*rand()/RAND_MAX;
    for(int i=0; i<pivotpos; i++){
        if(pivot == nullptr){
            pivot = stnInfoList;
        }
        pivot = pivot->next;
    }

}
