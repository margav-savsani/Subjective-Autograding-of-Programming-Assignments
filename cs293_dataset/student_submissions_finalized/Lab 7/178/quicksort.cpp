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

struct Trienode *SelectPivot(struct Trienode *list)
{
    int k, n, i = 0;
    n = ListLength(list);
    struct TrieNode *pivot=list;
    k=rand()%n;  //
    for (; i < k; ++i)
    {
        pivot=pivot->next;
    }
    return pivot;
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
}
