#include <string.h>
#include <iostream>
#include <limits>
#include "dictionary.h"
#include "journey.h"
using namespace std;

class Planner {
    // define suitable fields here
    Dictionary hashtable;
public:
    Planner(){}
    // add a journey to the system
    bool add_journey(Journey &journey){
        char *key = journey.getstart();
        Entry *location = hashtable.get(key);
        if (!location){
            Entry new_entry(journey);
            if (!hashtable.put(new_entry)) return false;
        }
        else location->add(journey);
        return true;
    }
    
    // get all journeys from start after min_start_time. This result is stored in ans. Note that we expect that ans is indexable till MAX_JOURNEYS.
    void get_all_journeys_from(char *start, float min_start_time, Journey **ans){
        for (int i = 0; i < MAX_JOURNEYS; i++) 
            ans[i] = NULL;
        Entry *location = hashtable.get(start);
        if (!location)
            return;
        
        Journey *journeys = location->value;
        for (int i = 0, j = 0; i < location->num_journeys; i++){
            if (journeys[i].getstart_time() >= min_start_time)
                ans[j++] = &journeys[i];
        }
        return;
        // NULL is returned if the station doesn't (yet) exist or if no train starts from the station after min_start_time.
    }
    
    // get the earliest direct journey from start to dest after min_start_time, if exists.
    Journey *min_if_direct(char *start, char *dest, float min_start_time){
        Journey *journeys[MAX_JOURNEYS];
        get_all_journeys_from(start, min_start_time, journeys);
        
        if (!journeys[0]) return NULL;
        
        Journey *min = NULL;
        float min_start = std::numeric_limits<float>::infinity(); // infinity is a static function hence it is called this way.

        for (int i = 0; journeys[i] != NULL; i++){
            if (strcmp(journeys[i]->getdest(), dest) != 0) 
                continue;

            if(journeys[i]->getstart_time() < min_start){
                min = journeys[i];
                min_start = journeys[i]->getstart_time();
            }
        }
        return min;
    }

    // get the earliest journey with exactly one stop from start to dest after min_start_time, if exists.
    pair<Journey *, Journey *> min_if_one_stop(char *start, char *dest, float min_start_time){
        Journey *journeys[MAX_JOURNEYS];
        get_all_journeys_from(start, min_start_time, journeys);
        pair<Journey *, Journey *> ans(NULL, NULL);

        float min_start = std::numeric_limits<float>::infinity();
        for (int i = 0; journeys[i] != NULL; i++){
            if (!strcmp(journeys[i]->getdest(), dest)) 
                continue; // we don't want the direct routes here.

            if(journeys[i]->getstart_time() < min_start){
                Journey *journeys_from_stop[MAX_JOURNEYS];
                get_all_journeys_from(journeys[i]->getdest(), journeys[i]->getend_time(), journeys_from_stop);
                for (int j = 0; journeys_from_stop[j] != NULL; j++){
                    if (!strcmp(journeys_from_stop[j]->getdest(), dest)){
                        ans.first = journeys[i];
                        ans.second = journeys_from_stop[j];
                        min_start = journeys[i]->getstart_time();
                        break;
                    }
                }
            }
        }
        return ans;
    }
    void query_loop(){
        char cmd[14]; // 14=max length of allowed commands.
        while(true){
            cin >> cmd;
            if (!strcmp(cmd, "ADD")){
                char start[MAXLEN], dest[MAXLEN];
                float start_time, end_time;
                cin >> start >> start_time >> dest >> end_time;
                Journey journey(start, dest, start_time, end_time);\
                add_journey(journey);
                // hashtable.print();
            }
            else if (!strcmp(cmd, "QUERY_STATION")){
                char start[MAXLEN];
                float start_time;
                cin >> start >> start_time;
                Journey *journeys[MAX_JOURNEYS];
                get_all_journeys_from(start, start_time, journeys);
                if (!journeys[0]){
                    cout << "Either " << start << " doesn't exist or there are no trains from " << start << " after " << start_time << endl;
                }
                for (int i = 0; journeys[i] != NULL; i++){
                    journeys[i]->print();
                }
            }
            else if (!strcmp(cmd, "QUERY_JOURNEY")){
                char start[MAXLEN], dest[MAXLEN];
                float start_time;
                cin >> start >> start_time >> dest;
                Journey *journey = min_if_direct(start, dest, start_time);
                auto journeys = min_if_one_stop(start, dest, start_time);

                if (!journeys.first && !journey) cout << "Either " << start << " doesn't exist or there are no trains from " << start << " to " << dest << " after " << start_time << endl;
                else if (!journey){
                    journeys.first->print();
                    journeys.second->print();
                }
                else if (!journeys.first){
                    journey->print();
                }
                else{
                    if (journeys.first->getstart_time() < journey->getstart_time()){
                        journeys.first->print(); journeys.second->print();
                    }
                    else journey->print();
                }
            }
            else if (!strcmp(cmd, "EXIT"))
                return;
            else
                cout << "--------\n" << "Usage:\n" << "ADD <station_one> <start_time> <station_two> <finish_time>\n" << "QUERY_STATION <station_one> <start_time>\n" << "QUERY_JOURNEY <station_one> <start_time> <station_two>\n" << "EXIT\n" << "--------\n";
        }
    }
};

int main(){
    Planner p;
    p.query_loop();
}