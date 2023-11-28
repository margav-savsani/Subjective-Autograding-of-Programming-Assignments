#include "planner.h"

void plannerHandler(Planner &rail_plan) {
    while(true){
        char keyword[20];
        std::cin >> keyword;
        
        if (strcmp (keyword, "ADD") == 0){
            Journey to_add;
            std::cin >> to_add.start >> to_add.start_time >> to_add.end >> to_add.end_time;
            rail_plan.add(to_add);
        }

        else if(strcmp(keyword, "QUERY_STATION") == 0){
            char station[32];
            float time;
            std::cin >> station;
            std::cin >> time;
            rail_plan.query_station(station, time);
        }

        else if(strcmp(keyword, "QUERY_JOURNEY") == 0){
            char start_station[32];
            float time;
            char end_station[32];
            std::cin>> start_station >> time >> end_station;
            rail_plan.query_journey(start_station,time,end_station);
        }

        else if(strcmp(keyword, "EXIT") == 0){
            return;
        }
    }
    
}

int main(){
    Planner rail_plan;
    plannerHandler(rail_plan);
}
