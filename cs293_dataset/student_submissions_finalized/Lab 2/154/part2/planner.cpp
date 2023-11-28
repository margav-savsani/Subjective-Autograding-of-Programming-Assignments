#include<iostream>
#include<math.h>
#include "planner.h"
using namespace std;

Journey::Journey(float start, char* station, float end){
    start_time = start;
    end_time = end;
    for(int i=0; i<32; i++){
        end_station[i] = station[i];
    }
    next = NULL;
}

Station::Station(){
    name[0] = NULL_KEY;
    journey = NULL;
}

Query_result::Query_result(float start){
    // for direct journey
    start_time = start;
    stop[0] = NULL_KEY;
}

Query_result::Query_result(float start, float next, char *station){
    // for indirect journey
    start_time = start;
    next_time = next;
    for(int i=0; i<32; i++){
        stop[i] = station[i];
    }
}

bool isequal(const char* a, const char* b){
    // manually defined function to check if two char strings are equal or not
    for(int i=0; i<32; i++){
        if(a[i] != b[i]) return false;
        if(a[i]==0 && b[i] == 0) return true;
    }
    return true;
}

int Planner::hashValue(char *key){
    int x = 33;   // x value for polynomial accumulation
    double PHI = (sqrt(5) - 1)/2;  // fibonacci constant for compression mapping

    long long hash = 0;
    long long m = 1610612741; // large prime number

    for(int i=0; i<32 && key[i]!= 0; i++){
        hash = (hash*x + key[i] - 'A' + 1) % m;  // polynomial accumulation
    }
    double frac = hash*PHI - int(hash*PHI); // fractional part
    return int(frac*N); // compresssed hash value
}

int Planner::find_station(char* station){
    // returns the index of station in the hashed array
    int init_idx = hashValue(station); 
    int idx = init_idx;
    for(int i=0; i<N && Stations[idx].name[0] != NULL_KEY; i++){
        idx = (init_idx + i)%N;
        if(isequal(station, Stations[idx].name)){
            return idx;
        }
    }
    return -1; // if given station isn't present in dictionary
}

Planner::Planner(){
    N = DICT_SIZE;
    Stations = new Station[N];
}

bool Planner::add(char *start_station, float start_time, char *end_station, float end_time)
{
    int init_idx = hashValue(start_station);
    int idx;

    for(int i=0; i<N; i++)
    {
        idx = (init_idx + i)%N;

        // empty station i.e, not a station before
        if(Stations[idx].name[0] == NULL_KEY)
        {
            for(int i=0; i<32; i++){
                Stations[idx].name[i] = start_station[i];
            }
            Stations[idx].journey = new Journey(start_time, end_station, end_time);
            return true;
        }
        
        if(isequal(start_station, Stations[idx].name))
        {
            // insert at head of linked list
            if(Stations[idx].journey->start_time >= start_time)
            {
                Journey *temp = new Journey(start_time, end_station, end_time);
                temp->next = Stations[idx].journey;
                Stations[idx].journey = temp;
                return true;
            }

            // insert in middle/end of linked list between x and y
            Journey* x = Stations[idx].journey;
            Journey* y = x->next;
            while(y != NULL)
            {
                if(y->start_time >= start_time) break;
                x = y;
                y = x->next;
            }
            Journey *temp = new Journey(start_time, end_station, end_time);
            temp->next = y;
            x->next = temp;
            return true;
        }
    }
    return false; // insert failed
}

Journey* Planner::query_station(char* station, float time){
    int idx = find_station(station);
    if(idx != -1){
        Journey* x = Stations[idx].journey;
        while(x != NULL){
            if(x->start_time >= time){
                return x;
            }
            x = x->next;
        }
    }
    return NULL;
}

Query_result* Planner::query_journey(char* start_station, float start_time, char* end_station){

    int start_idx = find_station(start_station);
    if(start_idx == -1) return NULL;

    Journey* first_j = Stations[start_idx].journey;
    while(first_j != NULL){
        if(first_j->start_time >= start_time)
        {
            // checking direct journey
            if(isequal(first_j->end_station, end_station)){
                return new Query_result(first_j->start_time);
            }

            // Checking for journey with intermediate stop
            int stop_idx = find_station(first_j->end_station);
            if(stop_idx != -1){
                Journey* stop_j = Stations[stop_idx].journey;
                while(stop_j != NULL)
                {
                    if(stop_j->start_time >= first_j->end_time)
                    {
                        // checking direct journey from this intermediate stop
                        if(isequal(stop_j->end_station, end_station)){
                            return new Query_result(first_j->start_time, stop_j->start_time, Stations[stop_idx].name);
                        }
                    }
                    stop_j = stop_j->next;
                }
            }
        }
        first_j = first_j->next;
    }
    return NULL;
}
