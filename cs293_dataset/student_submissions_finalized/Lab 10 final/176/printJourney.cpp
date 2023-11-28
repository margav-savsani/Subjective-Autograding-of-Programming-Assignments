#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <vector>
using namespace std;


// to store elements of journeys from one station to another
struct Tuple {
    public:
    int jcode;
    string from;
    string to;
    int dtime;
    int atime = -1;
    Tuple(int j, string s, string d, int t) {jcode = j; from = s; to = d; dtime = t;}
};


// prints the list of journeys undertaken to reach destination from source
void printJourney(listOfObjects<Tuple *> *journeys, listOfObjects<int *> *day) {
    string days[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

    // list starts from last to first
    while(journeys->next != nullptr)
        journeys = journeys->next;
    while(day->next != nullptr)
        day = day->next;
    
    cout << "Journey:\n";
    cout << BLUE << "Station: " << journeys->object->from << RESET <<endl;
    while(journeys != nullptr) {
        cout << GREEN << "|  " << "JourneyCode: " << journeys->object->jcode << RESET <<"  ";
        cout << RED << "Departs: " << days[day->object[0]] << ", " << journeys->object->dtime; 
        cout << "    Arrives: " << days[day->object[1]] << ", " << journeys->object->atime << RESET <<endl;
        cout << BLUE << "Station: " << journeys->object->to << RESET;
        if(journeys->prev != nullptr) {
            if(journeys->object->jcode != journeys->prev->object->jcode) {
                int arr_time = day->object[1]*24*60 + (journeys->object->atime / 100)*60 + journeys->object->atime % 100;
                int dep_time = day->prev->object[0]*24*60 + (journeys->prev->object->dtime / 100)*60 + journeys->prev->object->dtime % 100;
                int diff = dep_time - arr_time;
                int transit = (diff/60)*100 + (diff%60);
                cout << GREEN << "  Transit time: " << transit << RESET;
            }
        }
        cout << endl;
        journeys = journeys->prev;
        day = day->prev;
    }
    cout << endl;
}


void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime) {
    // storing the recursion level of call to this function
    static int recursion = -1;
    recursion++;
    static listOfObjects<Tuple *> *journeys;    // list of journeys from source to destination
    static listOfObjects<int *> *day;           // days of departure and arrival of journeys
                                                // (separated for ease of use in computations)

    int start_id = stnNameToIndex.get(srcStnName)->value;       // index of the source station
    
    static int d;       // the day in consideration to start tht journey on
    if(recursion == 0)  // starting with possibilities on a Sunday
        d = 0;

    if(d>=7 || (maxStopOvers < 0) && (srcStnName != destStnName)) {     // no further journeys possible
        recursion--;
        return;
    }

    listOfObjects<StationConnectionInfo *> *stations = adjacency[start_id].toStations;      // all the stations to which trains go to from source
    
        // setting the arrival time of previous journey using trains outgoing from current station
        listOfObjects<TrainInfoPerStation *> *all_trains = stationInfo[start_id];
        while(all_trains != nullptr && journeys != nullptr) {
            if (all_trains->object->journeyCode == journeys->object->jcode) {
                journeys->object->atime = all_trains->object->arrTime;
                if(journeys->object->atime < journeys->object->dtime)
                    day->object[1] = (day->object[1] + 1) % 7;
                break;
            }
            all_trains = all_trains->next;
        }
        
    // reached the end of a path and also ended up at the destination
    if(stations == nullptr && srcStnName == destStnName) {
        printJourney(journeys, day);
        recursion--;
        return;
    }

    // iterating through all trains to all stations adjacent to current station
    while(stations != nullptr) {
        string name = stnNameToIndex.getKeyAtIndex(stations->object->adjacentStnIndex); // name of adjacent station
        
        listOfObjects<TrainInfoPerStation *> *trains = stations->object->trains;
        while(trains != nullptr) {
            // we are at the destination
            if ((srcStnName == destStnName)){
                if (trains->object->journeyCode == journeys->object->jcode){
                    printJourney(journeys, day);
                    break;
                }
            }
            // intermediate station
            else{
            // appending a new journey from this station to adjacent
            listOfObjects<Tuple *> *new_journey = new listOfObjects<Tuple *>(new Tuple(trains->object->journeyCode ,srcStnName, name, trains->object->depTime));
            if(journeys == nullptr) {
                journeys = new_journey;
            }
            else {
                new_journey->next = journeys;
                journeys->prev = new_journey;
                journeys = new_journey;
            }
            listOfObjects<int *> *new_day = new listOfObjects<int *>(new int[2]);
            if(day == nullptr){
                day = new_day;
                day->object[0] = d;
                day->object[1] = d;
            }
            else {
                new_day->next = day;
                day->prev = new_day;
                day = new_day;
                day->object[0] = day->next->object[1];
                day->object[1] = day->next->object[1];
            }

            // checking if the journey meets constraints
            bool possible = false;
            if(journeys->next != nullptr) { // not the source station
                // arrival time in minutes from sunday midnight onwards
                int arr_time = day->next->object[1]*24*60 + (journeys->next->object->atime / 100)*60 + journeys->next->object->atime % 100;
                for(int j=0; j<7; j++) {    // checking the first feasible day where journey is possible
                    int k = (j + day->object[0]) % 7;
                    if(!trains->object->daysOfWeek[k])
                        continue;
                    int dep_time = (j + day->object[0])*24*60 + (journeys->object->dtime / 100)*60 + journeys->object->dtime % 100;
                    // check transit time only when there is a stopOver
                    if(journeys->object->jcode != journeys->next->object->jcode)
                        if((dep_time - arr_time) > maxTransitTime*60)
                            continue;
                    if((dep_time - arr_time) < 0)
                        continue;
                    possible = true;
                    day->object[0] = day->object[1] = k;
                    break;
                }
            }
            else {  // source station
                if(trains->object->daysOfWeek[d])
                    possible = true;
            }
                
                // continue with the current journey
                if(possible) {
                    if(journeys->next)
                        if(trains->object->journeyCode != journeys->next->object->jcode)
                            maxStopOvers--;     // there is a stopover
                    printPlanJourneys(name, destStnName, maxStopOvers, maxTransitTime);
                }
            
            // deleting the current journey head before moving on to next iteration of dfs
            listOfObjects<Tuple *> *jtemp = journeys->next;
            delete journeys;
            journeys = jtemp;
            listOfObjects<int *> *dtemp = day->next;
            delete day;
            day = dtemp;
            }
            trains = trains->next;
        }
        stations = stations->next;
    }

    // we came back to the source after checking all possible journeys for the present day
    // we now check with the next day
    if (journeys == nullptr){
        d++;
        printPlanJourneys(srcStnName, destStnName, maxStopOvers, maxTransitTime);
    }

    // decrease recursion level before exiting the function
    recursion--;
    return;
}
#endif
