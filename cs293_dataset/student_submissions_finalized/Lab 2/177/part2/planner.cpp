#include "planner.h"
#include <iostream>
#include <cmath>

void Planner::add_journey(std::string s1, float t1, std::string s2, float t2){
        if (jour_list.findFreeIndex(s1) != -1){ // Add the Entry if free space is present in the dictionary

            // Since addition to dictionaries are in the form of Entries, making an entry of the Journey to add in the Dictionary of Station struct
            Entry<Journey> jour_to_add;
            Journey j;
            j.start_station = s1;
            j.end_station = s2;
            j.start_time = t1;
            j.end_time = t2;
            jour_to_add.key = s1;
            jour_to_add.element = j;

            jour_list.put(jour_to_add);
        }
        else {std::cout << "No more space available in Planner Dictionary. Failed to add journey." << std::endl;}

}

void Planner::query_station(std::string st, float tm){
    if (jour_list.get(st) == NULL) {std::cout << "No such station with departures" << std::endl;}
    else {
        bool station_found = false;
        for (int i = 0; i < DICT_SIZE; i++){
            if ((jour_list.A[i].marker == 1) && (jour_list.A[i].element.start_station == st) && (jour_list.A[i].element.start_time >= tm)){
                std::cout << jour_list.A[i].element.start_time << " " << jour_list.A[i].element.end_station << std::endl;
                station_found = true;
            }
        }
        if (!station_found) {std::cout << "No such station with departures" << std::endl;}

    }
}

void Planner::query_journey(std::string s1, float tm, std::string s2){
    if (jour_list.get(s1) == NULL) {std::cout << "No such station with departures" << std::endl;}
    else {
        // Code for finding direct path

        bool station_found = false;
        int direct_min_index = 0;
        float min_time = 1000000;
        for (int i = 0; i < DICT_SIZE; i++){
            if ((jour_list.A[i].marker == 1) && (jour_list.A[i].element.start_station == s1) &&(jour_list.A[i].element.end_station == s2) && (jour_list.A[i].element.start_time >= tm)){
                if (jour_list.A[i].element.start_time <= min_time){
                    direct_min_index = i;
                    min_time = jour_list.A[i].element.start_time;
                    station_found = true;
                }
            }
        }

        // Code for indirect path
        int int_min_index = 0;
        int end_min_index = 0;
        float min_time_2 = 1000000;
        for (int i = 0; i < DICT_SIZE; i++){
            if ((jour_list.A[i].marker == 1) && (jour_list.A[i].element.start_station == s1) && (jour_list.A[i].element.start_time >= tm)){
                for (int j = 0; j < DICT_SIZE; j++){
                    if ((jour_list.A[j].marker == 1) && (jour_list.A[j].element.end_station == s2) && (jour_list.A[i].element.end_station == jour_list.A[j].element.start_station) && (jour_list.A[i].element.end_time <= jour_list.A[j].element.start_time)){
                        if (jour_list.A[i].element.start_time <= min_time_2){
                            int_min_index = i;
                            end_min_index = j;
                            min_time_2 = jour_list.A[i].element.start_time;
                            station_found = true;
                        }
                    }
                }
            }
        }

        if (!station_found) {{std::cout << "No such station with departures" << std::endl;}}
        else {
            if (min_time > min_time_2){
                std::cout << jour_list.A[int_min_index].element.start_time << " " << jour_list.A[int_min_index].element.end_station << " " << jour_list.A[end_min_index].element.start_time << std::endl;
        
            }
            else {
                std::cout << jour_list.A[direct_min_index].element.start_time << std::endl;
            }
        }

    }
}

void automatic(Planner &rail_planner){
  while (true)
  {
    char input[32];
    std::cout << ">>> " ;
    std::cin >> input;
    if(strcmp(input,"EXIT") == 0){
      break;
    }

    // ADD
    if(strcmp(input,"ADD") == 0){

      std::string s1,s2;
      float t1,t2;
      std::cin >> s1 >> t1 >> s2 >> t2;
      rail_planner.add_journey(s1,t1,s2,t2);
    }

    // QUERY_STATION
    else if(strcmp(input, "QUERY_STATION") == 0){
      std::string s1;
      float t1;
      std::cin >> s1 >> t1;
    rail_planner.query_station(s1,t1);
    }

    // QUERY_JOURNEY
    else if(strcmp(input,"QUERY_JOURNEY") == 0){
      std::string s1,s2;
      float t1;
      std::cin >> s1 >> t1 >> s2;
      rail_planner.query_journey(s1,t1,s2);
    }
  }
}

int main(){}