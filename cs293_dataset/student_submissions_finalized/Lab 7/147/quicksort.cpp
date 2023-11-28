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

int K = 4;
typedef listOfObjects<TrainInfoPerStation *> *ptrToStationsLL;

template <class T>
void myswap(const T *a, const T *b){
    const T tmp = *a;
    *a = *b;
    *b = tmp;
}
bool operator<(const TrainInfoPerStation &a, const TrainInfoPerStation &b){
  int firstday_a = 7, firstday_b = 7;
  for (int i = 0; i < 7; i++) if (a.daysOfWeek[i]){
    firstday_a = i; break;
  }
  for (int i = 0; i < 7; i++) if (b.daysOfWeek[i]){
    firstday_b = i; break;
  }
  if (firstday_a < firstday_b) return true;
  if (firstday_b < firstday_a) return false;

  return a.arrTime < b.arrTime;
}

ptrToStationsLL partition(ptrToStationsLL pivot, ptrToStationsLL start, ptrToStationsLL end){
  myswap(pivot->object, end->object); // swap the two TrainInfoPerStation objects's contents.
  auto x = end;
  ptrToStationsLL i = nullptr;
  // run through each element of the subarray in order
  for (auto j = start; j->next != end; j = j->next){ // treat j like an iterator
    if (j->object < x->object){
        myswap(i? i->next->object: start->object, j->object); // *(i->next->object) is the wall ie >= pivot. swap it with *(j->object) < pivot.
        i = i? i->next: start; // move i forward.
    }
  }
  myswap(i? i->next->object: start->object, end->object); // finally get *(end->object) = *(x->object) before all elements >= *(x->object)
  return i? i->next: start;
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  int n = 0;
  for (auto i = stnInfoList; i; i = i->next, n++);
  ptrToStationsLL ptrsModK[(n-1)/K + 1];
  int howManyMoreToSkip = 0, added = 0;
  for (auto i = stnInfoList; i; i = i->next, howManyMoreToSkip--){
    if (howManyMoreToSkip == 0){
      ptrsModK[added++] = i;
      howManyMoreToSkip = K;
    }
  }
}

int getPivot(int start, int end){
  return start + rand() % (end - start);
}

void RealQuickSort(ptrToStationsLL stnInfoList, int start, int end, ){

}
