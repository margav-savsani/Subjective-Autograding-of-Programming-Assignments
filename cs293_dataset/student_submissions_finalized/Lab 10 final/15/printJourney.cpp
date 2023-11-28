#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define CONST_GROWTH 20
#define INIT_SIZE 10

template <typename T>

// For adding to a linked list
void add_ll(listOfObjects<T> *&L, T val)
{
    if (L == nullptr)
    {
        L = new listOfObjects<T>(val);
        return;
    }
    else
    {
        listOfObjects<T> *curr = L;
        while (curr->next != nullptr)
        {
            curr = curr->next;
        }
        curr->next = new listOfObjects<T>(val);
        return;
    }
}

// For deleting the last element of a linked list
template <typename T>
void del_ll(listOfObjects<T> *&L)
{
    if (L == nullptr)
    {
        return;
    }
    if (L->next == nullptr)
    {
        L = nullptr;
        return;
    }
    else
    {
        listOfObjects<T> *curr = L;
        while (curr->next->next != nullptr)
        {
            curr = curr->next;
        }
        curr->next = nullptr;
        return;
    }
}

// This stores the information about a transit
class Transit
{
public:
    string stn;       // Station at which transit is made
    int transit_time; // Time of Transit
    Transit(string stn, int transit_time)
    {
        this->stn = stn;
        this->transit_time = transit_time;
    }
};

// My modification of printStationInfo
void MyprintStationInfo(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<Transit *> *Transits)
{
    listOfObjects<TrainInfoPerStation *> *currList;
    TrainInfoPerStation *currInfo;
    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    currList = stnInfoList;
    int jc_now = currList->object->journeyCode;
    while (currList != nullptr)
    {
        currInfo = currList->object;
        if (currInfo->journeyCode != jc_now)
        {
            jc_now = currInfo->journeyCode;
            cout << RED << "Transit at " << RESET << Transits->object->stn << RED << "\nTime of Transit " << RESET << Transits->object->transit_time / 100 << " Hours " << Transits->object->transit_time % 100 << " Minutes" << endl;
            ;
            Transits = Transits->next;
        }
        cout << GREEN << "Day(s): " << RESET;
        for (int i = 0; i < 7; i++)
        {
            if (currInfo->daysOfWeek[i])
                cout << days[i] << " ";
        }
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

        currList = currList->next;
    }
    cout << endl;
}


// I have done a recursive implementation
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

    if (maxStopOvers == -1) // base case when we have already stopped at enough stations
    {
        return;
    }
    // This is a list of informations about the jouneys whenever we change trains we add info about the second train to this list
    static listOfObjects<TrainInfoPerStation *> *Infos = nullptr;
    // This is the jouney code of the train we are currently on initially it would be 0. This would be helpful in checking
    // Whether we are changing trains at a station.
    static int jc_now = 0;
    // This is the reaching time of the train we are currently on, on the source station in this call of function.
    // Initially it would be 0
    static int reaching_time = 0;
    // This basically stores information about transits ie station of transit and time of transit.
    static listOfObjects<Transit *> *Transits = nullptr;
    // cout << "calling prinPlanJourneys with " << srcStnName << "\n"
    //      << destStnName << "\n"
    //      << maxStopOvers << "\n"
    //      << maxTransitTime << endl
    //      << jc_now << endl
    //      << reaching_time << endl;
    // printStationInfo(Infos);

    // When we have reached the destination
    if (destStnName == srcStnName)
    {
        static int i = 0;
        i++;
        cout << BLUE << i << "th Journey Plan:-" << RESET << endl;
        MyprintStationInfo(Infos, Transits);
        return;
    }

    int src = stnNameToIndex.get(srcStnName)->value, dest = stnNameToIndex.get(destStnName)->value;

    // When we are at the first level of recursion we nee to add all trains going from the source and assign the reacing_time
    // and jc_now for each train appropriately
    if (jc_now == 0)
    {
        // I did all calculations assuming the time would be given in minutes but it is given in hours so converting it into minutes
        maxTransitTime *= 100;

        // maxTransitTime=100*maxTransitTime;

        cout << endl;
        listOfObjects<StationConnectionInfo *> *Station = adjacency[src].toStations; // All reachable stations
        while (Station != nullptr)
        {
            listOfObjects<TrainInfoPerStation *> *trains = Station->object->trains;
            // printStationInfo(trains);
            int next_stn = Station->object->adjacentStnIndex;
            string next_name = stnNameToIndex.getKeyAtIndex(next_stn);

            while (trains != nullptr)
            {
                TrainInfoPerStation *t = trains->object;

                jc_now = t->journeyCode; // We assign jc_now to the journey code of train we take

                // To get at what time this train reaches the next station we need to go to the from Stations list of the next station
                listOfObjects<StationConnectionInfo *> *Station2 = adjacency[next_stn].fromStations;
                while (Station2->object->adjacentStnIndex != src)
                {
                    Station2 = Station2->next;
                }
                listOfObjects<TrainInfoPerStation *> *trains2 = Station2->object->trains;
                while (trains2->object->journeyCode != jc_now)
                {
                    trains2 = trains2->next;
                }
                TrainInfoPerStation S = TrainInfoPerStation(t->journeyCode, t->stopSeq, t->arrTime, t->depTime);
                for (int i = 0; i < 7; i++)
                {
                    if (t->daysOfWeek[i])
                    {
                        S.setDayOfWeek(i);
                        add_ll(Infos, &S);
                        // k is the reaching day at the second station it will always be after the ith day
                        int k = i;
                        //we always reach the next station after the previous station so we increment k by 1 in this case
                        if (trains2->object->arrTime < t->arrTime)
                            k=(k+1)%7;
                        while (!trains2->object->daysOfWeek[k])
                        {
                            k = (k + 1) % 7; // %7 because we can have i=6 and k=0 a satruday sunday situation.
                        }
                        reaching_time = k * 2400 + trains2->object->arrTime;

                        printPlanJourneys(next_name, destStnName, maxStopOvers, maxTransitTime); // recursing

                        reaching_time = 0;

                        Infos = nullptr;

                        S.resetDayOfWeek(i);
                    }
                }
                jc_now = 0;
                trains = trains->next;
            }
            Station = Station->next;
        }
    }
    else
    {
        listOfObjects<StationConnectionInfo *> *Station = adjacency[src].toStations; // All reachable stations
        while (Station != nullptr)
        {
            listOfObjects<TrainInfoPerStation *> *trains = Station->object->trains;
            int next_stn = Station->object->adjacentStnIndex;
            string next_name = stnNameToIndex.getKeyAtIndex(next_stn);

            while (trains != nullptr)
            {
                TrainInfoPerStation *t = trains->object;
                // So that we can jc_now when we return from recurssion.
                int prev_jc = jc_now;
                jc_now = t->journeyCode;
                listOfObjects<StationConnectionInfo *> *Station2 = adjacency[next_stn].fromStations;
                while (Station2->object->adjacentStnIndex != src)
                {
                    Station2 = Station2->next;
                }
                listOfObjects<TrainInfoPerStation *> *trains2 = Station2->object->trains;
                while (trains2->object->journeyCode != jc_now)
                {
                    trains2 = trains2->next;
                }
                TrainInfoPerStation S = TrainInfoPerStation(t->journeyCode, t->stopSeq, t->arrTime, t->depTime);

                // The case when we do not change trains and remain on the same journey code
                // I am assuming that we never switch to a train with the same journey code. For example if a train reaches on
                // a station on tuesday and thrusday when the passenger comes on tuesday he would never go on the thurstday train.
                if (jc_now == prev_jc)
                {
                    for (int i = 0; i < 7; i++)
                    {
                        if (t->daysOfWeek[i])
                        {
                            // cout<<jc_now<<" "<<i<<endl;
                            // If its the same train the reaching time should be exactly equal to the arrival time
                            if (i * 2400 + t->arrTime == reaching_time)
                            {
                                S.setDayOfWeek(i);

                                // add_ll(Infos, &S);

                                int prev_reaching_time = reaching_time;
                                int k = i;
                                if (trains2->object->arrTime < t->arrTime)
                                    k=(k+1)%7;
                                while (!trains2->object->daysOfWeek[k])
                                {
                                    k = (k + 1) % 7;
                                }
                                reaching_time = k * 2400 + trains2->object->arrTime;
                                printPlanJourneys(next_name, destStnName, maxStopOvers, maxTransitTime);
                                reaching_time = prev_reaching_time;
                                // del_ll(Infos);
                                S.resetDayOfWeek(i);
                                break;
                            }
                        }
                    }
                }
                else
                {
                    // Now we are switching to a train with another journey code
                    for (int i = 0; i < 7; i++)
                    {
                        if (t->daysOfWeek[i])
                        {
                            // cout<<jc_now<<" "<<i<<endl;
                            int transit_time = i * 2400 + t->depTime - reaching_time;
                            // this is need for the case when arrival and departure happen on different days
                            if(t->depTime<t->arrTime)transit_time+=2400;
                            
                            // as the time is in HHMM format we need to be careful when subtracting 
                            // This just handles the case when directly subtracting would give a wrong answer
                            if (reaching_time % 100 > t->depTime % 100)
                            {
                                transit_time -= 40;
                            }

                            // here we check if the journey is permittable according to the max allowed trainsit time
                            // The condition after the || is to include roll over situations like arriving on saturday and leaving on sunday
                            if ((transit_time > 0 && transit_time <= maxTransitTime) || (7 * 2400 + transit_time <= maxTransitTime))
                            {
                                if (transit_time < 0)
                                {
                                    transit_time += 7 * 2400;
                                }
                                // We basically have a change of trains so adding to the list of transits
                                Transit Tr(srcStnName, transit_time);
                                add_ll(Transits, &Tr);

                                S.setDayOfWeek(i);
                                // Adding to the information list as we have changed trains
                                add_ll(Infos, &S);

                                // Temporarily storing the reaching time as we need to reassign it after the recurssion.
                                int prev_reaching_time = reaching_time;
                                int k = i;
                                if (trains2->object->arrTime < t->arrTime)
                                    k=(k+1)%7;
                                while (!trains2->object->daysOfWeek[k])
                                {
                                    k = (k + 1) % 7; // %7 for the roll over case
                                }
                                reaching_time = k * 2400 + trains2->object->arrTime;
                                printPlanJourneys(next_name, destStnName, maxStopOvers - 1, maxTransitTime);

                                // After returning from recursion we need to reassign the values
                                reaching_time = prev_reaching_time;
                                del_ll(Infos);
                                del_ll(Transits);
                                S.resetDayOfWeek(i);
                            }
                        }
                    }
                }
                jc_now = prev_jc;
                trains = trains->next;
            }
            Station = Station->next;
        }
    }
    return;
}

#endif
