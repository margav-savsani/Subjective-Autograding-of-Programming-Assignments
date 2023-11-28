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

#define lst listOfObjects<TrainInfoPerStation *>

template<typename T> void swap_t(T &a, T &b) {
   (a ^= b), (b ^= a), (a ^= b);
}

void swap_data(lst *a, lst *b) {
    swap_t (a->object->journeyCode, b->object->journeyCode);
    swap_t (a->object->stopSeq, b->object->stopSeq);
    swap_t (a->object->arrTime, b->object->arrTime);
    swap_t (a->object->depTime, b->object->depTime);
    for(int i=0; i<7; i++)
        swap_t (a->object->daysOfWeek[i], b->object->daysOfWeek[i]);  
}

bool compare (lst const &a, lst const &b) {
    // to do
}

TrainInfoPerStation* get_tail(lst *head, lst *tail, int &n){
    tail = head;
    while (tail && tail->next) {
        tail = tail->next;
        n++;
    }
    n++;
}

void choose_random_pivot(lst *head, lst *pivot, int &n){
    pivot = head;
    int k = rand() % n;
    for(int i=0; i<k; i++)
        pivot = pivot->next;
}

void partition(lst *head, lst *tail, lst *pivot, int &n, int &m) {
    lst *i = head->prev;
    choose_random_pivot(head, pivot, n);
    swap_data(pivot, tail);
    for(lst *ptr = head; ptr != tail; ptr = ptr->next) {
        // to do
    }
}

void _Quicksort(lst *head, lst *tail, int &n){
    if(head != nullptr && head != tail && tail != head->next) {
        lst *pivot;
        int i = 0;
        partition(head, tail, pivot, n, i);

        // to do
    }
}

void Quicksort(lst *stnInfoList)
{
    int n = 0;
    lst *tail;
    get_tail(stnInfoList, tail, n);
    _Quicksort(stnInfoList, tail, n);
}
