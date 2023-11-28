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

void Quicksort(listOfObjects<TrainInfoPerStation*>* stnInfoList)
{
    listOfObjects<TrainInfoPerStation*>* pivot = stnInfoList;
    if (pivot == nullptr)
        return;
    listOfObjects<TrainInfoPerStation*>* less = nullptr;
    listOfObjects<TrainInfoPerStation*>* more = nullptr;
    
    listOfObjects<TrainInfoPerStation*>* head = stnInfoList->next;
    while (!head) {
        if (head->object < pivot->object) {
            if (less == nullptr)
                less = head;
            else {
                less->next = head;
                head->prev->next = nullptr;
                head->prev = less;
                less = less->next;
                less->next = nullptr;
                head = head->next;
                head->prev = nullptr;
            }
        }
        else {
            if (right == nullptr)
                right = head;
            else {
                more->next = head;
                head->prev->next = nullptr;
                head->prev = less;
                more = less->next;
                more->next = nullptr;
                head = head->next;
                head->prev = nullptr;                                                                                                                                    
            }
        }
        if (left && right)
            break;
    }
    while (!head) {
        if (head->object < pivot->object) {
            less->next = head;
            head->prev->next = nullptr;
            head->prev = less;
            less = less->next;
            less->next = nullptr;
            head = head->next;
            head->prev = nullptr;
        }
        else {
            more->next = head;
            head->prev->next = nullptr;
            head->prev = less;
            more = less->next;
            more->next = nullptr;
            head = head->next;
            head->prev = nullptr;
        }
    }
}
