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
listOfObjects<TrainInfoPerStation *> * Partition(listOfObjects<TrainInfoPerStation *> *start, listOfObjects<TrainInfoPerStation *> *end){
  // Setting the pivot for Implimenting Quicksort
  listOfObjects<TrainInfoPerStation *> *pivot = end;

  // A Node for traversing the linked list
  listOfObjects<TrainInfoPerStation *> *currNode = start;
  listOfObjects<TrainInfoPerStation *> *prevNode = start;
  while(currNode!=pivot){
    int i = 0;
    while(currNode->object->arrTime < pivot->object->arrTime){
      currNode = currNode->next;
      if (i==0){
        continue;
        i++;
      }
      else{
        prevNode = prevNode->next;
        i++;
      }
    }

    // Now we have encountered a node whose value is not less than the pivot, so move it after the pivot
    swap(prevNode, pivot);
  }
}
// Cuts the node after "node1" and pastes it after "node2"
void swap(listOfObjects<TrainInfoPerStation *> *node1, listOfObjects<TrainInfoPerStation *> *node2 ){
  // Removing the node after node1
  node1->next = node1->next->next;

  // Pasting the node after node2
  listOfObjects<TrainInfoPerStation *> *tempNode = node1->next;
  node2->next = tempNode;
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *currNode = stnInfoList;
  while(currNode->next!=NULL){
    currNode = currNode->next;
  }
  // Initializes the start and end nodes of the linked list to QuickSort
  listOfObjects<TrainInfoPerStation *> *start = stnInfoList;
  listOfObjects<TrainInfoPerStation *> *end = currNode;

  // Calling Recursive QuickSort
  myQuickSort(start, end);

}
void myQuickSort(listOfObjects<TrainInfoPerStation *> *start, listOfObjects<TrainInfoPerStation *> *end){
  if(start == NULL || start == end) // base case
    return;

  // Partitioning the linked list
  listOfObjects<TrainInfoPerStation *>* partition = Partition(start, end);// randomly selects a node out of the linked list and partitions the linked list according to that 
  // Calling Quicksort on the first part
  myQuickSort(start, partition);
  // Calling Quicksort on the second part 
  if (partition->next != NULL){
    myQuickSort(partition->next, end);
  }
}
