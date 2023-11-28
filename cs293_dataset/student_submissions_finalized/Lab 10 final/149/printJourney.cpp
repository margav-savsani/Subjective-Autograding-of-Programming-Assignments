#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

int depValue(TrainInfoPerStation *a, int b)
{
    if (a->daysOfWeek[b])
        return b * 2400 + a->depTime;
    else
        return -1;
}

int arrValue(TrainInfoPerStation *a, int b)
{
    if (a->daysOfWeek[b])
        return b * 2400 + a->arrTime;
    else
        return -1;
}

/// @brief struct to store al, info regarding the journey
struct Node
{
    int station;
    int journey;
    bool days[7];
    int arr;
    int dep;
    Node *next;
    Node()
    {
        next = nullptr;
    }
    Node(int a, int b)
    {
        station = a;
        journey = b;
        next = nullptr;
    }
    Node(int a, int b, int c, int d)
    {
        station = a;
        journey = b;
        arr = c;
        dep = d;
        next = nullptr;
    }
};

/// @brief the function is implemented as dfs where it travels all the way to destination or to a point where it can not go further. It comea back after that to a point forged, i.e., having more than one journeys, travels it agiain recursively hence travelling all the edges. Static variables are used ti create the recursive function here.
/// @param srcStnName name of the source station
/// @param destStnName 
/// @param maxStopOvers 
/// @param maxTransitTime 
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
    int src = stnNameToIndex.get(srcStnName)->value;
    int dest = stnNameToIndex.get(destStnName)->value;
    static int recursionLevel = -1;
    static int journeyC;
    static Node *list;
    static int time;
    static bool days[7];
    static bool journeyPrinted;
    recursionLevel++;
    if (maxStopOvers == -1)
    {
        recursionLevel--;
        return;
    }
    else if (src == dest)
    {
        int counter = -1;
        while (list != nullptr)
        {
            int a = list->station;
            int b = list->journey;
            listOfObjects<TrainInfoPerStation *> *s = stationInfo[a];
            listOfObjects<TrainInfoPerStation *> *m;
            while (s != nullptr)
            {
                if (s->object->journeyCode == b)
                {
                    m = new listOfObjects<TrainInfoPerStation *>(s->object);
                    m->next = nullptr;
                    m->prev = nullptr;
                    break;
                }
                s = s->next;
            }
            cout << stnNameToIndex.getKeyAtIndex(a) << endl;
            string ds[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
            for (int i = 0; i < 7; i++)
            {
                if (list->days[i])
                {
                    string k = to_string(list->arr);
                    if (list->arr == -1)
                        k = "start";
                    string o = to_string(list->dep);
                    if (list->dep == -1)
                        o = "end";
                    cout << "Days: " << ds[i] << endl;
                    cout << "Journey Code: " << list->journey << "    "
                         << " Arr: " << list->arr << " Dep: " << list->dep << endl;
                    journeyPrinted = true;
                }
            }
            list = list->next;
            counter++;
        }
        if (journeyPrinted)
        {
            cout << "Journey with " << counter << " stops" << endl
                 << endl;
        }
    }
    else if (recursionLevel == 0)
    {
        listOfObjects<StationConnectionInfo *> *currnode = adjacency[src].toStations;
        while (currnode != nullptr)
        {
            listOfObjects<TrainInfoPerStation *> *currtrain = currnode->object->trains;
            while (currtrain != nullptr)
            {
                journeyC = currtrain->object->journeyCode;
                time = currtrain->object->arrTime;
                listOfObjects<TrainInfoPerStation *> *s = stationInfo[src];
                listOfObjects<TrainInfoPerStation *> *m;
                while (s != nullptr)
                {
                    if (s->object->journeyCode == journeyC)
                    {
                        m = new listOfObjects<TrainInfoPerStation *>(s->object);
                        m->next = nullptr;
                        m->prev = nullptr;
                        break;
                    }
                    s = s->next;
                }
                list = new Node(src, journeyC, m->object->arrTime, m->object->depTime);
                for (int i = 0; i < 7; i++)
                {
                    list->days[i] = m->object->daysOfWeek[i];
                }
                string stnName = stnNameToIndex.getKeyAtIndex(currnode->object->adjacentStnIndex);
                printPlanJourneys(stnName, destStnName, maxStopOvers, maxTransitTime);
                list = nullptr;
                currtrain = currtrain->next;
            }
            currnode = currnode->next;
        }
        if (!journeyPrinted)
        {
            cout << "No Journeys Avavilable" << endl;
        }
    }
    else
    {
        int t = time;
        Node *l;
        l = new Node(list->station, list->journey, list->arr, list->dep);
        for (int i = 0; i < 7; i++)
        {
            l->days[i] = list->days[i];
        }
        Node *z = l;
        Node *y = list->next;
        while (y != nullptr)
        {
            z->next = new Node(y->station, y->journey, y->arr, y->dep);
            for (int i = 0; i < 7; i++)
            {
                z->next->days[i] = y->days[i];
            }
            y = y->next;
            z = z->next;
        }
        int j = journeyC;
        listOfObjects<StationConnectionInfo *> *currnode = adjacency[src].toStations;
        while (currnode != nullptr)
        {
            string stnName = stnNameToIndex.getKeyAtIndex(currnode->object->adjacentStnIndex);
            listOfObjects<TrainInfoPerStation *> *currtrain = currnode->object->trains;
            while (currtrain != nullptr)
            {
                if (journeyC == currtrain->object->journeyCode)
                {
                    printPlanJourneys(stnName, destStnName, maxStopOvers, maxTransitTime);
                }
                else
                {
                    journeyC = currtrain->object->journeyCode;
                    listOfObjects<TrainInfoPerStation *> *s = stationInfo[src];
                    listOfObjects<TrainInfoPerStation *> *m;
                    while (s != nullptr)
                    {
                        if (s->object->journeyCode == journeyC)
                        {
                            m = new listOfObjects<TrainInfoPerStation *>(s->object);
                            m->next = nullptr;
                            m->prev = nullptr;
                            break;
                        }
                        s = s->next;
                    }
                    Node *x = list;
                    while (x->next != nullptr)
                        x = x->next;
                    x->next = new Node(src, journeyC);
                    bool goAhead = false;
                    for (int i = 0; i < 7; i++)
                    {
                        if (x->days[i])
                        {
                            if (m->object->daysOfWeek[i])
                            {
                                if (time < m->object->depTime && m->object->depTime - time <= maxTransitTime)
                                {
                                    x->next->arr = m->object->arrTime;
                                    x->next->dep = m->object->depTime;
                                    x->next->days[i] = true;
                                    time = currtrain->object->arrTime;
                                    goAhead = true;
                                }
                            }
                            else if (m->object->daysOfWeek[(i + 1) % 7])
                            {
                                if (time > m->object->depTime && 2400 + m->object->depTime - time <= maxTransitTime)
                                {
                                    x->next->arr = m->object->arrTime;
                                    x->next->dep = m->object->depTime;
                                    x->next->days[(i + 1) % 7] = true;
                                    time = currtrain->object->arrTime;
                                    goAhead = true;
                                }
                            }
                            else
                            {
                                x->days[i] = false;
                            }
                        }
                    }
                    if (goAhead)
                    {
                        printPlanJourneys(stnName, destStnName, maxStopOvers - 1, maxTransitTime);
                    }
                }
                list = new Node(l->station, l->journey, l->arr, l->dep);
                for (int i = 0; i < 7; i++)
                {
                    list->days[i] = l->days[i];
                }
                y = list;
                z = l->next;
                while (z != nullptr)
                {
                    y->next = new Node(z->station, z->journey, z->arr, z->dep);
                    for (int i = 0; i < 7; i++)
                    {
                        y->next->days[i] = z->days[i];
                    }
                    y = y->next;
                    z = z->next;
                }
                journeyC = j;
                currtrain = currtrain->next;
                time = t;
            }
            currnode = currnode->next;
        }
    }
    recursionLevel--;
}
#endif