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
#include <ctime>

bool isLessThen(TrainInfoPerStation * l , TrainInfoPerStation * r) {
  int i = 0;
  for (i = 0; (l->daysOfWeek[i] or r->daysOfWeek[i]) and (i < 7); i++);
  if (l->daysOfWeek[i] != r->daysOfWeek[i]) return (l->daysOfWeek[i] < r->daysOfWeek[i]);
  return (l->depTime < r->depTime);
}

void sweap(listOfObjects<TrainInfoPerStation *> * a , listOfObjects<TrainInfoPerStation *> * b) {
  TrainInfoPerStation * temp = b->object;
  b->object = a->object;
  a->object = temp;
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList) {
  srand(time(0));
  // Call appropriate pivot function based on choice
  // Split into 2 parts based on pivot choice
  // Recursively keep sorting
  //base case
  if (stnInfoList == nullptr or stnInfoList->next == nullptr) return;
  //otherwise
  // find length and last pointer
  int len;
  listOfObjects<TrainInfoPerStation *> *endNode = stnInfoList;
  for (len = 1; endNode->next != nullptr ; len ++) endNode = endNode->next;
  // find random pivot
  int rndNumber = rand() % len;
  listOfObjects<TrainInfoPerStation *> *pivot = stnInfoList;
  for (int i = 0; i <= rndNumber; ++i) pivot = pivot->next;

  // start node
  listOfObjects<TrainInfoPerStation *> *startNode = stnInfoList;

  int i = 0 , j = len;
  while (true) {
    while ( startNode != pivot and isLessThen(startNode->object, pivot->object)) {
      i++;
      startNode = startNode->next;
    }
    while ( startNode != pivot and !isLessThen(endNode->object, pivot->object)) {
      j--;
      endNode = endNode->prev;
    }
    if (j <= i) break;
    sweap(startNode,endNode);
  }
  startNode->prev->next = nullptr;
  Quicksort(stnInfoList);
  Quicksort(startNode->next);
  startNode->prev->next = startNode;
  return ;
}