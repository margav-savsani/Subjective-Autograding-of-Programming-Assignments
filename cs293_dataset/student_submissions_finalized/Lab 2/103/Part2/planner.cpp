#include <iostream>
#include <string.h>

#include "queue.h"
#include "dictionary.h"
#include "circularQueue.cpp"
#include "dictionary.cpp"
#include "planner.h"

using namespace std;

// start the query loop
void Planner::startQueryLoop(){
    string cmd; // enter the command to be executed
    cin >> cmd;
    while(cmd != "EXIT"){ // continue query loop until command is EXIT
        if(cmd == "ADD"){ // if command is ADD
            Journey newJourney; // create and enter details into newJourney
            cin >> newJourney.startStation >> newJourney.startTime >> newJourney.endStation >> newJourney.endTime;
            addJourney(newJourney); // add newJourney to the stationDetails dictionary
        } else if(cmd == "QUERY_STATION"){ // if command is QUERY_STATION
            Query query; // create and enter details into query
            query.type = 'S'; // set query type to S->Station
            cin >> query.startStation >> query.startTime;
            processQuery(query); // process the query
        } else if(cmd == "QUERY_JOURNEY"){ // if command is QUERY_JOURNEY
            Query query; // create and enter details into query
            query.type = 'J'; // set query type to J->Journey
            cin >> query.startStation >> query.startTime >> query.endStation;
            processQuery(query); // process the query
        }

        cin >> cmd; // enter the next command to be executed
    }
}

// add newJourney to the stationDetails dictionary
void Planner::addJourney(Journey newJourney){
    if(stationDetails.get(newJourney.startStation) == NULL){ // if the station name does not exist in the dictionary
        // create an entry for the station name in the dictionary
        Entry<vector<Journey>> e; strcpy(e.key, newJourney.startStation); e.value = vector<Journey>();
        stationDetails.put(e);
    }
    stationDetails.get(newJourney.startStation)->value.push_back(newJourney); // add newJourney to the list of journeys from startStation
}

// process queries
void Planner::processQuery(Query query){
    if(query.type == 'S'){ // if the query type is S->QUERY_STATION
        if(stationDetails.get(query.startStation) == NULL){ // if the station name does not exist in the dictionary
            cout << "ERROR: No Such Station" << endl;
            return;
        }

        vector<Journey> station = stationDetails.get(query.startStation)->value;
        bool found = false; // found represents if a journey has been found
        for(int idx = 0; idx < station.size(); idx++){ // loop thhrough all the journeys from the station
            if(station[idx].startTime >= query.startTime){ // if the startTime of the journey is greater than or equall to the given start time
                cout << station[idx].startTime << " " << station[idx].endStation << endl; // print required output
                found = true; // a journey has been found
            }
        }

        if(!found){ // if no journey is found
            cout << "ERROR: No Such Journey" << endl;
        }
    } else if(query.type == 'J'){ // if the query type is J->QUERY_JOURNEY
        if(stationDetails.get(query.startStation) == NULL){ // if that station name does not exist in the dictionary
            cout << "ERROR: No Such Station" << endl;
            return;
        }

        vector<Journey> station = stationDetails.get(query.startStation)->value;

        // Level 1 Pass - snly check stations directly connected to startStation
        bool found_1 = false; // found_1 represents if a journey has been found
        Journey minJourney; // minJourney stores the journey with earliest startTime
        for(int idx = 0; idx < station.size(); idx++){ // loop through all the journeys from the station
            if(station[idx].startTime > query.startTime && !strcmp(station[idx].endStation, query.endStation)){ // if the start time of the journey is greater than the given start time and the end station of the journey is the given end station
                if(!found_1){ // if no journey is found
                    found_1 = true; // set found_1 to true
                    minJourney = station[idx]; // set minJourney to current journey
                } else{
                    if(station[idx].startTime < minJourney.startTime){ // if startTime of the current journey is lesser than that of minJourney
                        minJourney = station[idx]; // set minJourney to current journey
                    }
                }
            }
        }

        // Level 2 Pass - only check stations directly connected to an intermediate station directly connected to the starting station
        bool found_2 = false; // foudn_2 represents if a journey has been found
        Journey minJourneyFirst, minJourneySecond; // minJourneyFirst and minJourneySecond stores the first and second parts of the journey respectively
        for(int idx = 0; idx < station.size(); idx++){ // loop through all the journeys from the starting station
            if(station[idx].startTime > query.startTime){ // if the startTime of the journey is greater than the given start time
                if(stationDetails.get(station[idx].endStation) != NULL){ // if the name of the intermediate station exists in the dictionary
                    vector<Journey> stationIntermediate = stationDetails.get(station[idx].endStation)->value;
                    for(int innerIdx = 0; innerIdx < stationIntermediate.size(); innerIdx++){ // loop through all the journeys from the intermediate station
                        if(stationIntermediate[innerIdx].startTime >= station[idx].endTime && !strcmp(stationIntermediate[innerIdx].endStation, query.endStation)){ // if the start time of the journey is greater than or equal to the end time of the first part of the full journey and the end station of the journey is the given end station
                            if(!found_2){ // if no journey is found
                                found_2 = true; // set journey_2 to true
                                minJourneyFirst = station[idx]; // set minJourneyFirst to first part of current full journey
                                minJourneySecond = stationIntermediate[innerIdx]; // set minJourneySecond to second part of current full journey
                            } else{
                                if(station[idx].startTime < minJourneyFirst.startTime){ // if startTime of the current full journey is lesser than that of minJourneyFirst
                                    minJourneyFirst = station[idx]; // set minJourneyFirst to first part of current full journey
                                    minJourneySecond = stationIntermediate[innerIdx]; // set minJourneySecond to second part of current full journey
                                }
                            }
                        }
                    }
                }
            }
        }

        if(!found_1 && !found_2){ // if neither a Level 1 nor a Level 2 journey is found
            cout << "ERROR: No Such Path" << endl;
        } else if(found_1 && found_2){ // if both Level 1 and Level 2 journeys are found
            if(minJourneyFirst.startTime < minJourney.startTime){ // if the Level 2 journey has an earlier startTime than the Level 1 journey
                cout << minJourneyFirst.startTime << " " << minJourneyFirst.endStation << " " << minJourneySecond.startTime << endl;
            } else{ // else if the Level 1 journey has an earlier startTime than the Level 2 journey
                cout << minJourney.startTime << endl;
            }
        } else if(found_1){ // if only a Level 1 journey is found
            cout << minJourney.startTime << endl;
        } else if(found_2){ // if only a Level 2 journey is found
            cout << minJourneyFirst.startTime << " " << minJourneyFirst.endStation << " " << minJourneySecond.startTime << endl;
        }
    }
}