#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#define RFG "\033[35m"

using namespace std;

// Train information per station
class Info
{
public:
    int journeyCode; // same as train number
    int stnidx;      // Storing the current index of station in queue
    int arrTime;     // Arrival time at station; -1 if train starts from here
    int depTime;     // Departure time from station; -1 if train ends here
    int brk;

    int train_start; // To store the starting point of this journey code

    int day; // would store current time
    int inter_day;

    bool daysofsrc[7];

    Info *child;
    int count;

public:
    Info(int jCode, int idx, int aTm, int dTm, int cnt)
    {
        journeyCode = jCode;
        stnidx = idx;
        arrTime = aTm;
        depTime = dTm;
        count = cnt;
        child = nullptr;
        brk = -1;
    }

    ~Info() { ; }
};

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

    // insert your code here

    // cout << "This function is to be implemented by you." << endl;

    // Whenever you need to print a journey, construct a
    // listOfObjects<TrainInfoPerStation *> appropriately, and then
    // use printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of
    // the Planner class. It is declared in planner.h and implemented in
    // planner.cpp

    // insert your code here
    int srcidx = stnNameToIndex.get(srcStnName)->value;
    int dstnidx = stnNameToIndex.get(destStnName)->value;

    // This would store my final selected Journey Codes
    // listOfObjects<TrainInfoPerStation *> *selected = nullptr;
    // listOfObjects<TrainInfoPerStation *> *selected_end = nullptr;
    listOfObjects<Info *> *selected = nullptr;
    listOfObjects<Info *> *selected_end = nullptr;

    // My intermediate JCs queue
    listOfObjects<Info *> *queue_start = nullptr;
    listOfObjects<Info *> *queue_end = nullptr;

    // Need to populate the queue first with all the stations connected to the source
    // StationAdjacencyList curr_source = adjacency[srcidx];
    listOfObjects<StationConnectionInfo *> *stns_connected_to_currsrc = adjacency[srcidx].toStations;
    while (stns_connected_to_currsrc != nullptr)
    {
        // Here I have found the station connected to my current source
        // I now need to iterate to cover all the trains with different journey codes
        // leaving the current station

        // Object has a list of trains and the current source stn index
        StationConnectionInfo *curr_dstn_stn = stns_connected_to_currsrc->object;

        // This is a list of the trains that is connecting my current source and the destination
        listOfObjects<TrainInfoPerStation *> *trains_connecting = curr_dstn_stn->trains;
        while (trains_connecting != nullptr)
        {
            //////////////////////////////////////////////////
            // int arrTime, deptTime;
            // unsigned short seq;
            // listOfObjects<TrainInfoPerStation *> *ptr = stationInfo[srcidx];
            // while (ptr != nullptr)
            // {
            //     if (ptr->object->journeyCode == trains_connecting->object->journeyCode)
            //     {
            //         arrTime = ptr->object->arrTime;
            //         deptTime = ptr->object->depTime;
            //         seq = ptr->object->stopSeq;
            //         break;
            //     }
            //     ptr = ptr->next;
            // }
            ////////////////////////////////////////////////
            if (stns_connected_to_currsrc->object->adjacentStnIndex == dstnidx)
            {
                // Let's add it to the final list by getting details from the queue_start
                // TrainInfoPerStation *temp = new TrainInfoPerStation(trains_connecting->object->journeyCode, trains_connecting->object->stopSeq, trains_connecting->object->arrTime, trains_connecting->object->depTime);
                // Info *temp = new Info(trains_connecting->object->journeyCode, dstnidx, arrTime, deptTime, seq, 1);
                // Setting the days
                for (int i = 0; i < 7; i++)
                {
                    // temp->daysOfWeek[i] = trains_connecting->object->daysOfWeek[i];
                    if (trains_connecting->object->daysOfWeek[i])
                    {
                        Info *temp = new Info(trains_connecting->object->journeyCode, dstnidx, trains_connecting->object->arrTime, trains_connecting->object->depTime, 0);
                        temp->day = i;
                        temp->inter_day = i;
                        temp->train_start = srcidx;
                        for (int k = 0; k < 7; k++)
                        {
                            temp->daysofsrc[k] = trains_connecting->object->daysOfWeek[k];
                        }

                        if (selected == nullptr)
                        {
                            selected = new listOfObjects<Info *>(temp);
                            selected_end = selected;
                        }
                        else
                        {
                            // Adding the elements in the list by modifying the corresponding parent and child pointers
                            listOfObjects<Info *> *to_add_list_object = new listOfObjects<Info *>(temp);
                            selected_end->next = to_add_list_object;
                            to_add_list_object->prev = selected_end;
                            selected_end = selected_end->next;
                        }
                    }
                }
            }
            else
            {
                // I will for now append the train to my queue that I made, note that this part of the function
                // will change for the stations at level more than 1 as then I need to check if the journey code
                // of the previous stn's train and current is matching or not

                // Lets create our custom object that will go into out temporary queue
                // Info *to_add;
                // to_add = new Info(trains_connecting->object->journeyCode, curr_dstn_stn->adjacentStnIndex, arrTime, deptTime, seq, 1);

                for (int i = 0; i < 7; i++)
                {
                    if (trains_connecting->object->daysOfWeek[i])
                    {
                        Info *temp = new Info(trains_connecting->object->journeyCode, curr_dstn_stn->adjacentStnIndex, trains_connecting->object->arrTime, trains_connecting->object->depTime, 0);
                        temp->day = i;
                        temp->inter_day = i;
                        temp->train_start = srcidx;

                        for (int k = 0; k < 7; k++)
                        {
                            temp->daysofsrc[k] = trains_connecting->object->daysOfWeek[k];
                        }

                        // In case my queue was empty I need to initialise my queue_start
                        if (queue_start == nullptr)
                        {
                            queue_start = new listOfObjects<Info *>(temp);
                            queue_end = queue_start;
                        }
                        else
                        {
                            // Adding the elements in the list by modifying the corresponding parent and child pointers
                            listOfObjects<Info *> *to_add_list_object = new listOfObjects<Info *>(temp);
                            queue_end->next = to_add_list_object;
                            to_add_list_object->prev = queue_end;
                            queue_end = queue_end->next;
                        }
                    }
                }
                // Now the present train along with its information have been added, let's move to see
                // the next train in route, by changing the trains_connecting variable
            }
            trains_connecting = trains_connecting->next;
        }

        // Once the above while loop ends that means all the trains for the given journey has been looked at
        // Lets move to the next station connected to the current source stn
        stns_connected_to_currsrc = stns_connected_to_currsrc->next;
    }

    // after the end of the above loop, we have initialised our queue storing all the probable JCs
    // and stnIdx from which a route may exist. Now let's start the mighty BFS, going over element present
    // in the queue and seeing the trains going from it, seeing if JC matchs the queue element, if so
    // add it in the queue else ignore, once all the stations gets exhausted for the current queue element,
    // dequeue it

    // This entire operation ends once the queue gets empty
    while (queue_start != nullptr)
    {
        Info *currstn = queue_start->object;

        // Need to update the queue based on continuation of the JC
        // StationAdjacencyList curr_source = adjacency[currstn->stnidx];
        listOfObjects<StationConnectionInfo *> *stns_connected_to_currsrc = adjacency[currstn->stnidx].toStations;
        while (stns_connected_to_currsrc != nullptr)
        {
            // Here I have found the station connected to my current source
            // I now need to iterate to cover all the trains with different journey codes
            // leaving the current station

            // Object has a list of trains and the current source stn index
            StationConnectionInfo *curr_dstn_stn = stns_connected_to_currsrc->object;

            // This is a list of the trains that is connecting my current source and the destination
            listOfObjects<TrainInfoPerStation *> *trains_connecting = curr_dstn_stn->trains;
            while (trains_connecting != nullptr)
            {
                // Now we iterate over all the trains from the curr_dest and see if current temp dstn have the same
                // JC or not
                // Check if JC matchs
                if (trains_connecting->object->journeyCode == currstn->journeyCode)
                {
                    // we will break the loop and take this element to the end of the queue if it is not same
                    // as the final destination we want to go, else simply add it to the final list
                    // of connecting trains
                    if (stns_connected_to_currsrc->object->adjacentStnIndex == dstnidx)
                    {
                        // Let's add it to the final list by getting details from the queue_start
                        // TrainInfoPerStation *temp = new TrainInfoPerStation(queue_start->object->journeyCode, queue_start->object->stopSeq, queue_start->object->arrTime, queue_start->object->depTime);
                        if (selected == nullptr)
                        {
                            listOfObjects<Info *> *parnt = new listOfObjects<Info *>(queue_start->object);
                            selected = parnt;
                            selected_end = selected;
                        }
                        else
                        {
                            listOfObjects<Info *> *parnt = new listOfObjects<Info *>(queue_start->object);
                            // Adding the elements in the list by modifying the corresponding parent and child pointers
                            selected_end->next = parnt;
                            parnt->prev = selected_end;
                            selected_end = selected_end->next;
                        }
                    }
                    else
                    {
                        Info *tmp = new Info(currstn->journeyCode, curr_dstn_stn->adjacentStnIndex, currstn->arrTime, currstn->depTime, currstn->count);
                        tmp->child = currstn->child;
                        tmp->train_start = currstn->train_start;
                        tmp->day = currstn->day;
                        for (int o = 0; o < 7; o++)
                        {
                            tmp->daysofsrc[o] = currstn->daysofsrc[o];
                        }

                        for (int o = 0; o < 7; o++)
                        {
                            bool mismatch = false;
                            for (int q = 0; q < 7; q++)
                            {
                                if (trains_connecting->object->daysOfWeek[(q + o) % 7] != currstn->daysofsrc[q])
                                {
                                    mismatch = true;
                                    break;
                                }
                            }
                            if (!mismatch)
                            {
                                tmp->inter_day = (currstn->day + o) % 7;
                                break;
                            }
                        }
                        listOfObjects<Info *> *parnt = new listOfObjects<Info *>(tmp);

                        queue_end->next = parnt;
                        parnt->prev = queue_end;
                        queue_end = queue_end->next;
                    }
                }
                else
                {
                    // We can try to further continue our search
                    if (currstn->count + 1 <= maxStopOvers)
                    {
                        ////////////////////////////////////////////////////////////////////////

                        listOfObjects<TrainInfoPerStation *> *ptr = stationInfo[currstn->stnidx];
                        while (ptr != nullptr)
                        {
                            if (ptr->object->journeyCode == currstn->journeyCode)
                            {
                                break;
                            }
                            ptr = ptr->next;
                        }

                        ////////////////////////////////////////////////////////////////////////

                        int max_days = maxTransitTime / 2400;
                        int time_gap = maxTransitTime % 2400;
                        for (int j = 0; j <= max_days + 1; j++)
                        {
                            if (trains_connecting->object->daysOfWeek[(currstn->day + j) % 7])
                            {
                                // Now check time
                                int gap;
                                if (trains_connecting->object->depTime >= ptr->object->arrTime)
                                {
                                    int digit = ((trains_connecting->object->depTime) % 100) - ((ptr->object->arrTime) % 100);
                                    if (digit < 0)
                                    {
                                        digit = digit + 60;
                                        int hour = ((trains_connecting->object->depTime) / 100) - ((ptr->object->arrTime) / 100) - 1;
                                        gap = 100 * hour + digit + j * 2400;
                                    }
                                    else
                                    {
                                        int hour;
                                        if (digit == 60)
                                        {
                                            digit = 0;
                                            hour = ((trains_connecting->object->depTime) / 100) - ((ptr->object->arrTime) / 100) + 1;
                                        }
                                        else
                                        {
                                            hour = ((trains_connecting->object->depTime) / 100) - ((ptr->object->arrTime) / 100);
                                        }
                                        gap = 100 * hour + digit + j * 2400;
                                    }
                                }
                                else
                                {
                                    int temp;
                                    int digit = -((trains_connecting->object->depTime) % 100) + ((ptr->object->arrTime) % 100);
                                    if (digit < 0)
                                    {
                                        digit = digit + 60;
                                        int hour = -((trains_connecting->object->depTime) / 100) + ((ptr->object->arrTime) / 100) - 1;
                                        temp = 100 * hour + digit;
                                    }
                                    else
                                    {
                                        int hour;
                                        if (digit == 60)
                                        {
                                            digit = 0;
                                            hour = -((trains_connecting->object->depTime) / 100) + ((ptr->object->arrTime) / 100) + 1;
                                        }
                                        else
                                        {
                                            hour = -((trains_connecting->object->depTime) / 100) + ((ptr->object->arrTime) / 100);
                                        }
                                        temp = 100 * hour + digit;
                                    }

                                    int cur;
                                    digit = -((temp) % 100) + (2400 % 100);
                                    if (digit < 0)
                                    {
                                        digit = digit + 60;
                                        int hour = -((temp) / 100) + ((2400) / 100) - 1;
                                        cur = 100 * hour + digit;
                                    }
                                    else
                                    {
                                        int hour;
                                        if (digit == 60)
                                        {
                                            digit = 0;
                                            hour = -((temp) / 100) + ((2400) / 100) + 1;
                                        }
                                        else
                                        {
                                            hour = -((temp) / 100) + ((2400) / 100);
                                        }
                                        cur = 100 * hour + digit;
                                    }

                                    gap = cur + 2400 * (j - 1);
                                }

                                // gap = (trains_connecting->object->depTime - ptr->object->arrTime) + j * 2400;
                                if (gap >= 0 && gap <= maxTransitTime)
                                {
                                    // Condition satisfied lets add nodes, we will need to check if destn reached too
                                    if (stns_connected_to_currsrc->object->adjacentStnIndex == dstnidx)
                                    {
                                        Info *tmp = new Info(trains_connecting->object->journeyCode, dstnidx, trains_connecting->object->arrTime, trains_connecting->object->depTime, currstn->count + 1);
                                        tmp->brk = gap;
                                        tmp->child = currstn;
                                        tmp->train_start = queue_start->object->stnidx;
                                        tmp->day = (currstn->day + j) % 7;
                                        tmp->inter_day = (currstn->day + j) % 7;

                                        for (int y = 0; y < 7; y++)
                                        {
                                            tmp->daysofsrc[y] = trains_connecting->object->daysOfWeek[y];
                                        }

                                        listOfObjects<Info *> *parnt = new listOfObjects<Info *>(tmp);

                                        if (selected == nullptr)
                                        {
                                            selected = parnt;
                                            selected_end = selected;
                                        }
                                        else
                                        {
                                            selected_end->next = parnt;
                                            parnt->prev = selected_end;
                                            selected_end = selected_end->next;
                                        }
                                    }
                                    else
                                    {
                                        Info *tmp = new Info(trains_connecting->object->journeyCode, stns_connected_to_currsrc->object->adjacentStnIndex, trains_connecting->object->arrTime, trains_connecting->object->depTime, currstn->count + 1);
                                        tmp->brk = gap;
                                        tmp->child = currstn;
                                        tmp->train_start = queue_start->object->stnidx;
                                        tmp->day = (currstn->day + j) % 7;
                                        tmp->inter_day = (currstn->day + j) % 7;

                                        for (int y = 0; y < 7; y++)
                                        {
                                            tmp->daysofsrc[y] = trains_connecting->object->daysOfWeek[y];
                                        }

                                        listOfObjects<Info *> *parnt = new listOfObjects<Info *>(tmp);
                                        queue_end->next = parnt;
                                        parnt->prev = queue_end;
                                        queue_end = queue_end->next;
                                    }
                                }
                            }
                        }
                    }
                }
                // Now the present train did not match the JC, let's move to see
                // the next train in route, by changing the trains_connecting variable
                trains_connecting = trains_connecting->next;
            }
            // Once the above while loop ends that means all the trains for the given journey has been looked at
            // Lets move to the next station connected to the current source stn
            stns_connected_to_currsrc = stns_connected_to_currsrc->next;
        }
        queue_start = queue_start->next;
        if (queue_start != nullptr)
        {
            queue_start->prev = nullptr;
        }
    }

    // Hopefully if everything went well we have recieved our list of trains
    // Lets send it to print and see what happens
    if (selected != nullptr)
    {
        // printStationInfo(selected);
        string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

        listOfObjects<Info *> *currList;
        Info *currInfo;

        currList = selected;

        cout << RFG << "\t \t \t VIABLE JOURNEYS" << RESET << endl;
        cout << "\t \t \t _______________" << endl;
        cout << endl;
        cout << "The journeys are printed in bottom up order indicated by upward pointing arrows arrows" << endl;
        cout << endl;
        int i = 1;
        while (currList != nullptr)
        {
            currInfo = currList->object;

            // Info *current = currInfo;
            // Info *prev = nullptr, *next = nullptr;

            // while (current != NULL)
            // {
            //     // Store next
            //     next = current->child;
            //     // Reverse current node's pointer
            //     current->child = prev;
            //     // Move pointers one position ahead.
            //     prev = current;
            //     current = next;
            // }
            // currInfo = prev;

            cout << RED << "TRAIN " << i << " : " << RESET << endl;
            while (currInfo != nullptr)
            {
                cout << GREEN << "Day(s): " << RESET;
                cout << days[currInfo->day] << " ";
                cout << "\t"
                     << "FROM : " << stnNameToIndex.getKeyAtIndex(currInfo->train_start);
                cout << endl;
                cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
                cout << RED << "Arr: " << RESET;
                if (currInfo->arrTime == -1)
                {
                    cout << "Starts";
                }
                else
                {
                    cout << currInfo->arrTime;
                }
                cout << RED << " Dep: " << RESET;
                if (currInfo->depTime == -1)
                {
                    cout << "Ends";
                }
                else
                {
                    cout << currInfo->depTime;
                }
                cout << endl;
                string key = stnNameToIndex.getKeyAtIndex(currInfo->train_start);
                if (currInfo->child != nullptr)
                {
                    // string key = stnNameToIndex.getKeyAtIndex(currInfo->child->train_start);
                    // cout << GREEN << "Train will be changed at " << key << " with transit time : " << currInfo->child->brk << RESET;
                    cout << GREEN << "Train will be changed at " << key << " with transit time : " << currInfo->brk << RESET;
                    cout << endl;
                    cout << "\t \t \t"
                         << "^" << endl;
                    cout << "\t \t \t"
                         << "|" << endl;
                }
                currInfo = currInfo->child;
            }
            cout << endl;
            currList = currList->next;
            i++;
        }
    }
    else
    {
        cout << "No journeys found" << endl;
    }

    // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
    // for the source station and then we can print it out by invoking
    // printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of the Planner class
    // It is declared in planner.h and implemented in planner.cpp

    return;
}

#endif
