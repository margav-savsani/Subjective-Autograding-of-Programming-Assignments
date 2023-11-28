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

listOfObjects<TrainInfoPerStation *> pivot(listOfObjects<TrainInfoPerStation *> *node){
    if(node->next){
        return node->next;
    }
}

void randQSort(listOfObjects<TrainInfoPerStation *> node1, listOfObjects<TrainInfoPerStation *> node2){
    
    listOfObjects<TrainInfoPerStation *> *n1 = node1;
    listOfObjects<TrainInfoPerStation *> *n2 = node2;
    
    listOfObjects<TrainInfoPerStation *> *n = pivot(n1)
    
    while(n1 != n2){
        if(n1->object >= n->object){
            if(n2->object <= n->object){
                swap(n1->object,n2->object);
                n1 = n1->next;
                n2 = n2->prev;
            }
            else if(n2->object >= n->object){
                n2 = n2->prev;
            }
        }
        else if(n1->object <= n->object){
            if(n2->object >= n-object){
                n1 = n1->next;
                n2 = n2->prev;
            }
            else if(n2->object <= n->object){
                n1 = n1->next;
            }
        }
    }
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    
    
    
  // Put your code here.
}
