#include "dictionary.cpp"
#include <string.h>
#include <iostream>
#include <algorithm>
#include <fstream>
int main(){
    Dictionary start_stations;
    //freopen("../input3.in", "r", stdin);
    while(true){
        char command[32];
        std::cin >> command;
        if(strcmp(command, "ADD")==0){
            char station_one[32];
            char station_two[32];
            float start_time;
            float end_time;
            std::cin >> station_one;
            std::cin >> start_time;
            std::cin >> station_two;
            std::cin >> end_time;

            //Search for the station in Dictionary
            Entry* start_station = start_stations.get(station_one);

            //If station not found, insert it in the dictionary
            if(start_station==NULL){
                Entry new_station;
                strcpy(new_station.key,station_one);
                start_stations.put(new_station);
            }
            start_station = start_stations.get(station_one);

            //Create the Journey required to be inserted
            Journey new_journey;
            strcpy(new_journey.start,station_one);
            strcpy(new_journey.end,station_two);
            new_journey.start_time = start_time;
            new_journey.end_time = end_time;

            //Find the location where the Journey has to be inserted(We insert the Journeys
            // in sorted order by start time)
            Journey* pushing_location = std::lower_bound(start_station->journeys.begin(),start_station->journeys.end(),new_journey,start_time_comp);

            //Insert the Journey
            start_station->journeys.insert(pushing_location, new_journey);
        }
        else if(strcmp(command, "QUERY_STATION")==0){
            char station_one[32];
            float start_time;
            std::cin >> station_one;
            std::cin >> start_time;
            Entry* start_station = start_stations.get(station_one);

            //Error message is no such station exists
            if(start_station==NULL){
                std::cout << "No such station exists" << std::endl;
                continue;
            }

            //Create a dummy journey with start_time to binary search
            Journey journey_check;
            journey_check.start_time = start_time;

            //get the first iterator which has start_time >= required start time
            Journey* location = std::lower_bound(start_station->journeys.begin(),start_station->journeys.end(),journey_check,start_time_comp);

            //print all the journeys after the start time
            while(location<start_station->journeys.end()){
                std::cout << location->start_time << ' ' << location->end << std::endl;
                location++; 
            }
        }
        else if(strcmp(command, "QUERY_JOURNEY")==0){
            char station_one[32];
            char station_two[32];
            float start_time;
            std::cin >> station_one;
            std::cin >> start_time;
            std::cin >> station_two;

            //search for the starting station
            Entry* start_station = start_stations.get(station_one);

            //error message if starting station not found
            if(start_station==NULL){
                std::cout << "No such start station" << std::endl;
                continue;
            }

            //create a dummy journey to binary search the vector of start_station journeys
            Journey journey_check;
            journey_check.start_time = start_time;

            //search the earliest possible journey with >= start time as compared to what is required
            Journey* location = std::lower_bound(start_station->journeys.begin(),start_station->journeys.end(),journey_check,start_time_comp);

            //variable to keep track if we find a journey or not
            bool journey_found(false);

            //Loop through all journeys after the start time
            while(location<start_station->journeys.end()){
                //if the destination is the required final destination, print it
                if(strcmp(location->end,station_two)==0){
                    std::cout << location->start_time << std::endl;
                    journey_found = true;
                    break;
                }

                //otherwise create an intermediate station of whose journeys we will track
                Entry* intermediate_station = start_stations.get(location->end);
                if(intermediate_station==NULL){
                    location++;
                    continue;
                }

                //dummy journey for binary search
                Journey second_journey_check;
                second_journey_check.start_time = location->end_time;

                //Search through the journeys beginning from intermediate station after the time we reach the station
                Journey* second_journey = std::lower_bound(intermediate_station->journeys.begin(),intermediate_station->journeys.end(),second_journey_check,start_time_comp);

                //Search through all the journeys to see if we find a journey terminating at the required destination
                while(second_journey<intermediate_station->journeys.end()){
                    if(strcmp(second_journey->end,station_two)==0){
                        //print, break and update journey_found if final destination is reached
                        std::cout << location->start_time << ' ' << intermediate_station->key << ' ' << second_journey->start_time << std::endl;
                        journey_found = true;
                        break;
                    }
                    second_journey++;
                }

                //break if journey is found
                if(journey_found) break;

                location++;
            }

            //If no journey could be found after searching through all possibilities,, print error message
            if(!journey_found) std::cout << "No path found" << std::endl;
        }
        else if(strcmp(command, "EXIT")==0){
            break;
        }
    }
}