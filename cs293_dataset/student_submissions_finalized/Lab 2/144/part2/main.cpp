#include "planner.h"
#include <iostream>

int main()
{
    //Dictionary of Stations
    Dictionary stations;

    //Taking query
    std::string query;
    std::cin >> query;

    while (query != "EXIT")
    {
        //Handling Add query
        if (query == "ADD")
        {
            std::string start, end;
            float start_time, end_time;
            std::cin >> start >> start_time >> end >> end_time;
            //Creating journey struct
            Journey J;
            J.end = end;
            J.start = start;
            J.end_time = end_time;
            J.start_time = start_time;

            //Checking if station is already present in dictionary
            Station *station_to_add = stations.get(start);
            if (station_to_add == NULL)
            {
                //If not present, create a new station and add.
                Station temp(start);
                //Adding journey to station
                temp.journey_arr->insert(J);

                stations.put(temp);
            }

            else
            {
                //Else, add journey to existing value in dictionary.
                station_to_add->journey_arr->insert(J);
            }
        }

        if (query == "QUERY_STATION")
        {
            std::string start;
            float time;
            std::cin >> start >> time;
            //Check if station is present in dictionary

            Station *station_to_add = stations.get(start);

            if (station_to_add == nullptr)
            {
                //Error if not present
                std::cout << "ERROR!\n";
                std::cin >> query;
                continue;
            }

            //Get index of first element in array with start time greater than or equal to input time.
            int start_index = station_to_add->journey_arr->getIndex(time);
            if (start_index < 0)
            {
                //If index is negative, no journey exists which fulfills the condition
                std::cout << "ERROR!\n";
                std::cin >> query;
                continue;
            }

            //Iterating through array and print the journeys
            int size = station_to_add->journey_arr->getSize();
            for (int i = start_index; i < size; i++)
            {
                Journey *temp = station_to_add->journey_arr->getJourney(i);
                std::cout << temp->start_time << " " << temp->end << "\n";
            }
        }

        if (query == "QUERY_JOURNEY")
        {
            std::string start, end;
            float start_time;

            std::cin >> start >> start_time >> end;

            //Get starting station from dictionary
            Station *station_to_add = stations.get(start);

            if (station_to_add == nullptr)
            {
                //Error if not found
                std::cout << "ERROR!\n";
                std::cin >> query;
                continue;
            }

            //Get index of first journey with start_time greater than or equal to input time
            int start_index = station_to_add->journey_arr->getIndex(start_time);

            if (start_index < 0)
            {
                //Error if no journey is present
                std::cout << "ERROR!\n";
                std::cin >> query;
                continue;
            }
            
            int size = station_to_add->journey_arr->getSize();
            //Iterate through the array from index
            bool found = false;
            for(int i = start_index; i < size; i++){
                Journey *temp = station_to_add->journey_arr->getJourney(i);

                //If end station is input station, found and exit.
                if(temp->end == end){
                    std::cout << temp->start_time << '\n';
                    found = true;
                    break;
                }

                //Check if a journey exists from end of first journey to final station AFTER train arrives at the first station.
                std::string mid_station = temp->end;
                float mid_station_time = temp->end_time;

                Station* mid_station_ptr = stations.get(mid_station);

                //If no journey from the station, continue searching
                if(mid_station_ptr == NULL) continue;

                int mid_station_index = mid_station_ptr->journey_arr->getIndex(mid_station_time);

                //If no journey exists after arrival time, continue
                if(mid_station_index < 0) continue;

                int mid_station_size = mid_station_ptr->journey_arr->getSize();

                //Iterate through the second array.
                for(int i = mid_station_index; i < mid_station_size; i++){
                    //If found, exit
                    if(mid_station_ptr->journey_arr->getJourney(i)->end == end){
                        std::cout << temp->start_time<<" "<<mid_station_ptr->name << " " << mid_station_ptr->journey_arr->getJourney(i)->start_time << '\n';
                        found = true;
                        break;
                    }
                }

                if (found) break; //If found, exit
            }

            if(!found) std::cout << "ERROR!\n"; //If not found, exit
        }
        std::cin >> query;
    }

    return 0;
}