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
class Node 
{ 
    public:
    int data; 
    Node *next; 
    Node *prev; 
};
void partition(Node *h,Node *l){
  
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  if (h != NULL && l != h && l != h->next) 
    { 
        Node *p = partition(l, h); 
        _quickSort(l, p->prev); 
        _quickSort(p->next, h); 
    } 
  // Put your code here.
}
