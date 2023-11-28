#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#include <cassert>

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef QUEUE_TPL
#define QUEUE_TPL
template <typename T> struct Node_dll {
    T value;
    Node_dll<T>* next;
    Node_dll<T>* prev;
    Node_dll(T value, Node_dll<T>* next, Node_dll<T>* prev)
        : value(value), next(next), prev(prev)
    {
    }
};

template <typename T> class Queue {
    Node_dll<T>* head;
    Node_dll<T>* tail;
    int size;

  public:
    // constructor
    Queue()
        : head(nullptr), tail(nullptr), size(0)
    {
    }

    ~Queue()
    {
        while (head != nullptr) {
            Node_dll<T>* temp = head->next;
            delete head;
            head = temp;
        }
    }

    void enqueue(T v)
    {
        if (head == nullptr) {
            head = new Node_dll<T>(v, nullptr, nullptr);
            tail = head;
        }
        else {
            tail->next = new Node_dll<T>(v, nullptr, tail);
            tail = tail->next;
        }
        size++;
    }

    bool is_empty() const
    {
        return (head == nullptr);
    }
    
    T front() const
    {
        if (head != nullptr)
            return head->value;
        std::cerr << "No front of empty queue\n";
        assert(false);
    }

    void dequeue()
    {
        if (head != nullptr) {
            if (head == tail) {
                delete head;
                head = tail = nullptr;
            }
            else {
                Node_dll<T>* temp = head;
                head = head->next;
                head->prev = nullptr;
                delete temp;
            }
            size--;
        }
        else {
            std::cerr << "Dequeueing from empty queue\n";
            assert(false);
        }
    }
    
    void print()
    {
        if (head != nullptr) {
            Node_dll<T>* temp = head;
            while (temp != nullptr) {
                std::cout << temp->value << ' ';
                temp = temp->next;
            }
        }
        else {
            std::cout << "<Empty Queue>";
        }                                                                          
    }
};
#endif  // QUEUE_TPL

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"

class JourneyAndStation {
  public:
    int stnIndex;
    TrainInfoPerStation* jrny;

    JourneyAndStation(int sI, TrainInfoPerStation* ptr)
        : stnIndex(sI), jrny(ptr)
    {
    }
};

class JourneyWithStops {
  public:
    int stnIndex;
    int stopOvers;
    listOfObjects<JourneyAndStation*>* history;

    JourneyWithStops()
        : stnIndex(-1), stopOvers(-1), history(nullptr)
    {
    }

    JourneyWithStops(int sI, int sO)
        : stnIndex(sI), stopOvers(sO), history(nullptr)
    {
    }

    JourneyWithStops(int sI, int sO, listOfObjects<JourneyAndStation*>* ptr)
        : stnIndex(sI), stopOvers(sO), history(ptr)
    {
    }
};

template <typename T> void insertAtTail(listOfObjects<T>*& head, T v)
{
    if (head == nullptr) {
        head = new listOfObjects<T>(v);
    }
    else {
        listOfObjects<T>* old_tail = head;

        while (old_tail->next != nullptr) {
            old_tail = old_tail->next;
        }

        old_tail->next = new listOfObjects<T>(v);
        old_tail->next->prev = old_tail;
    }
}

listOfObjects<TrainInfoPerStation*>* separator(listOfObjects<TrainInfoPerStation*>* currList, bool isSrc = false)
{
    listOfObjects<TrainInfoPerStation*>* expandedList = nullptr;
    TrainInfoPerStation* currInfo;

    // Expanding information in stnInfoList to get a list of train info
    // in which each element of the list refers to a single day of the
    // week.
    
    while (currList != nullptr) {
        currInfo = currList->object;
        if (currInfo != nullptr) {
            // Make as many copies of currInfo as the total count of days in the week
            // when this train runs from/to this station
            int jCode = currInfo->journeyCode;
            int stSeq = currInfo->stopSeq;
            int arrTime = currInfo->arrTime;
            int depTime = currInfo->depTime;

            if (depTime == -1 && isSrc) {
                currList = currList->next;
                continue;
            }

            for (int i = 0; i < 7; i++) {
                if (currInfo->daysOfWeek[i]) {
                    TrainInfoPerStation* newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
                    newExpandedElement->setDayOfWeek(i);

                    listOfObjects<TrainInfoPerStation*>* newExpandedListElement = new listOfObjects<TrainInfoPerStation*>(newExpandedElement);

                    if (expandedList == nullptr)
                        expandedList = newExpandedListElement;
                    else {
                        newExpandedListElement->next = expandedList;
                        expandedList->prev = newExpandedListElement;
                        expandedList = newExpandedListElement;
                    }
                }
            }
        }
        currList = currList->next;
    }
    return expandedList;
}

void initialenqueue(Queue<JourneyWithStops*>& q, listOfObjects<TrainInfoPerStation*>* ptr, int stnIndx)
{
    while (ptr != nullptr) {
        TrainInfoPerStation* okJrny = new TrainInfoPerStation(ptr->object->journeyCode, ptr->object->stopSeq, ptr->object->arrTime, ptr->object->depTime);

        for (int i = 0; i < 7; i++) {
            if (ptr->object->daysOfWeek[i])
                okJrny->setDayOfWeek(i);
        }

        JourneyAndStation* newObj = new JourneyAndStation(stnIndx, okJrny);
        listOfObjects<JourneyAndStation*>* newList = new listOfObjects<JourneyAndStation*>(newObj);

        JourneyWithStops* temp = new JourneyWithStops(stnIndx, 0, newList);
        q.enqueue(temp);
        ptr = ptr->next;
    }
}

bool checkValidTransit(int day1, int time1, int day2, int time2, int max)
{
    int dt = (2400 + time2 - time1) % 2400;
    int dd = (7 + day2 - day1) % 7;

    if (dt == 0)
        dd++;

    return (dd * 2400 + dt <= max);
}

bool offset(TrainInfoPerStation* a, TrainInfoPerStation* b)
{
    for (int i = 0; i < 7; i++) {
        if (a->daysOfWeek[i] != b->daysOfWeek[i])
            return true;
    }
    return false;
}

int dayOfWeek(TrainInfoPerStation* t)
{
    int j = -1;
    for (int i = 0; i < 7; i++) {
        if (t->daysOfWeek[i])
            j = i;
    }
    return j;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
    std::string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    int srcIndex = stnNameToIndex.get(srcStnName)->value;
    int destIndex = stnNameToIndex.get(destStnName)->value;

    listOfObjects<TrainInfoPerStation*>* prunedSrcJournies = separator(stationInfo[srcIndex], true);
    Queue<JourneyWithStops*> q;
    initialenqueue(q, prunedSrcJournies, srcIndex);

    int journeysFound = 0;
    while (!q.is_empty()) {
        JourneyWithStops* now = q.front();
        if (now->stnIndex == destIndex) {
            journeysFound++;
            std::cout << "Journey " << journeysFound << '\n';
            listOfObjects<JourneyAndStation*>* print = now->history;
            
            int d = dayOfWeek(print->object->jrny);

            std::cout << GREEN << "JC: " << print->object->jrny->journeyCode << " " << BLUE << stnNameToIndex.getKeyAtIndex(print->object->stnIndex) << GREEN << " " << days[d] << " " << print->object->jrny->depTime << RESET << " ===> ";

            listOfObjects<JourneyAndStation*>* prevPrint = now->history;
            print = print->next;

            while (print != nullptr) {
                if (print->object->jrny->journeyCode == prevPrint->object->jrny->journeyCode) {
                    print = print->next;
                    prevPrint = prevPrint->next;
                    continue;
                }

                d = dayOfWeek(prevPrint->object->jrny);
                std::cout << BLUE << stnNameToIndex.getKeyAtIndex(prevPrint->object->stnIndex) << GREEN << " " << days[d] << " " << prevPrint->object->jrny->arrTime << RESET << '\n';

                d = dayOfWeek(print->object->jrny);
                std::cout << GREEN << "JC: " << print->object->jrny->journeyCode << " " << BLUE << stnNameToIndex.getKeyAtIndex(prevPrint->object->stnIndex) << GREEN << " " << days[d] << " " << prevPrint->object->jrny->depTime << RESET << " ===> ";

                print = print->next;
                prevPrint = prevPrint->next;
            }

            std::cout << BLUE << stnNameToIndex.getKeyAtIndex(prevPrint->object->stnIndex) << GREEN << " " << days[d] << " " << prevPrint->object->jrny->arrTime << RESET << "\n\n";
            q.dequeue();
            continue;
        }
        
        {
            int currStnIndx = now->stnIndex;
            listOfObjects<JourneyAndStation*>* ptr = now->history;
            assert(ptr != nullptr);
            while (ptr->next != nullptr)
                ptr = ptr->next;

            listOfObjects<StationConnectionInfo*>* outward = adjacency[currStnIndx].toStations;

            while (outward != nullptr) {
                int adjStnIndx = outward->object->adjacentStnIndex;
                listOfObjects<TrainInfoPerStation*>* outTrains = separator(outward->object->trains);

                while (outTrains != nullptr) {
                    int jC = outTrains->object->journeyCode;
                    
                    int time1 = ptr->object->jrny->arrTime;
                    int day1 = dayOfWeek(ptr->object->jrny);

                    int time2 = outTrains->object->depTime;
                    int day2 = dayOfWeek(outTrains->object);

                    if (outTrains->object->journeyCode == ptr->object->jrny->journeyCode) {
                        if (offset(outTrains->object, ptr->object->jrny)) {
                            outTrains = outTrains->next;
                            continue;
                        }

                        listOfObjects<JourneyAndStation*>* tempPtr = now->history;
                        listOfObjects<JourneyAndStation*>* buildNew = nullptr;

                        while (tempPtr != nullptr) {
                            int ix = tempPtr->object->stnIndex;
                            TrainInfoPerStation* t = tempPtr->object->jrny;

                            TrainInfoPerStation* newt = new TrainInfoPerStation(t->journeyCode, t->stopSeq, t->arrTime, t->depTime);
                            newt->setDayOfWeek(dayOfWeek(t));

                            JourneyAndStation* naya = new JourneyAndStation(ix, newt);
                            insertAtTail<JourneyAndStation*>(buildNew, naya);
                            tempPtr = tempPtr->next;
                        }

                        listOfObjects<StationConnectionInfo*>* m = adjacency[adjStnIndx].fromStations;

                        while (m->object->adjacentStnIndex != currStnIndx)
                            m = m->next;

                        listOfObjects<TrainInfoPerStation*>* n = m->object->trains;

                        while (n->object->journeyCode != outTrains->object->journeyCode)
                            n = n->next;

                        TrainInfoPerStation* t = n->object;

                        TrainInfoPerStation* newt = new TrainInfoPerStation(t->journeyCode, t->stopSeq, t->arrTime, t->depTime);

                        listOfObjects<StationConnectionInfo*>* pp = outward;

                        while (pp->object->adjacentStnIndex != adjStnIndx)
                            pp = pp->next;

                        listOfObjects<TrainInfoPerStation*>* bb = pp->object->trains;

                        while (bb->object->journeyCode != outTrains->object->journeyCode)
                            bb = bb->next;

                        bool isoff = offset(t, bb->object);

                        for (int i = 0; i < 7; i++) {
                            if (outTrains->object->daysOfWeek[i]) {
                                if (isoff)
                                    newt->setDayOfWeek((i + 1) % 7);
                                else
                                    newt->setDayOfWeek(i);
                            }
                        }

                        JourneyAndStation* naya = new JourneyAndStation(adjStnIndx, newt);
                        insertAtTail<JourneyAndStation*>(buildNew, naya);

                        JourneyWithStops* enqueueing = new JourneyWithStops(adjStnIndx, now->stopOvers, buildNew);
                        q.enqueue(enqueueing);
                    }
                    else {
                        if (now->stnIndex == srcIndex || now->stopOvers >= maxStopOvers) {
                            outTrains = outTrains->next;
                            continue;
                        }

                        bool flag = checkValidTransit(day1, time1, day2, time2, maxTransitTime);

                        if (flag) {
                            listOfObjects<JourneyAndStation*>* tempPtr = now->history;
                            listOfObjects<JourneyAndStation*>* buildNew = nullptr;

                            while (tempPtr != nullptr) {
                                int ix = tempPtr->object->stnIndex;
                                TrainInfoPerStation* t = tempPtr->object->jrny;

                                TrainInfoPerStation* newt = new TrainInfoPerStation(t->journeyCode, t->stopSeq, t->arrTime, t->depTime);

                                if (tempPtr->next == nullptr)
                                    newt->depTime = outTrains->object->depTime;

                                newt->setDayOfWeek(dayOfWeek(t));

                                JourneyAndStation* naya = new JourneyAndStation(ix, newt);

                                insertAtTail<JourneyAndStation*>(buildNew, naya);

                                tempPtr = tempPtr->next;
                            }

                            listOfObjects<StationConnectionInfo*>* m = adjacency[adjStnIndx].fromStations;

                            while (m->object->adjacentStnIndex != currStnIndx)
                                m = m->next;

                            listOfObjects<TrainInfoPerStation*>* n = m->object->trains;

                            while (n->object->journeyCode != outTrains->object->journeyCode)
                                n = n->next;

                            TrainInfoPerStation* t = n->object;

                            TrainInfoPerStation* newt = new TrainInfoPerStation(t->journeyCode, t->stopSeq, t->arrTime, t->depTime);

                            listOfObjects<StationConnectionInfo*>* pp = outward;

                            while (pp->object->adjacentStnIndex != adjStnIndx)
                                pp = pp->next;

                            listOfObjects<TrainInfoPerStation*>* bb = pp->object->trains;

                            while (bb->object->journeyCode != outTrains->object->journeyCode)
                                bb = bb->next;

                            bool isoff = offset(t, bb->object);

                            for (int i = 0; i < 7; i++) {
                                if (outTrains->object->daysOfWeek[i]) {
                                    if (isoff)
                                        newt->setDayOfWeek((i + 1) % 7);
                                    else
                                        newt->setDayOfWeek(i);
                                }
                            }

                            JourneyAndStation* naya = new JourneyAndStation(adjStnIndx, newt);
                            insertAtTail<JourneyAndStation*>(buildNew, naya);
                            JourneyWithStops* enqueueing = new JourneyWithStops(adjStnIndx, now->stopOvers + 1, buildNew);
                            q.enqueue(enqueueing);
                        }
                    }
                    outTrains = outTrains->next;
                }
                outward = outward->next;
            }
        }
        q.dequeue();
    }
}

#endif
