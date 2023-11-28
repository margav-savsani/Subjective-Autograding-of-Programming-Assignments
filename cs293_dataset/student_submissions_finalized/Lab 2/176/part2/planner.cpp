#include <algorithm>
#include <limits>
#include "planner.h"
#include "dictionary.h"
#define MAX_F numeric_limits<float>::max()

Planner::Planner() {
    N = MAX_JOURNEY;
}

bool Planner::add(Query* query) {
    Entry stat;                                 // based on dictionary.cpp: stores a string key and corresponding value based on hash
    strcpy(stat.key, query->stat1);                // key is the start station
    
    if(dict_names.get(stat.key) == NULL) {      // if station not already present in list
        Station abc;
        abc.index = names.size();               // station inserted at last of present list
        stat.value = abc.index;
        dict_names.put(stat);                   // add station name to dictionary
        strcpy(abc.name, query->stat1);

        Journey des;
        des.index = (abc.list2).size();             // new journey being added at end of list
        strcpy(stat.key, query->stat2);             // hashing based on destination
        stat.value = des.index;
        abc.dict_journey.put(stat);                 // add journey destination name to dictionary
        strcpy(des.desti, query->stat2);
        des.s_t = query->time1;
        des.d_t = query->time2;
        des.time = des.d_t - des.s_t;
        abc.list2.push_back({des});
       
        names.push_back(abc);       // add the station with the journey, to the list of stations
         
    }
    else {      // when station already present in list
        Station &abc = names[dict_names.get(stat.key)->value];      // the station entered
        Journey des;
        des.index = (abc.list2).size();
        strcpy(stat.key, query->stat2);
        if(abc.dict_journey.get(stat.key) == NULL) {            // if previous journey to same destination not present
            stat.value = des.index;
            abc.dict_journey.put(stat);
            strcpy(des.desti, query->stat2);
            des.s_t = query->time1;
            des.d_t = query->time2;
            des.time = des.d_t - des.s_t;
            abc.list2.push_back({des});                        // pushing back to a new index
        }
        else {                                                 // if previous destination already encountered
            stat = *(abc.dict_journey.get(stat.key));
            des.index = stat.value;
            strcpy(des.desti, query->stat2);
            des.s_t = query->time1;
            des.d_t = query->time2;
            des.time = des.d_t - des.s_t;
            ((abc.list2)[des.index]).push_back(des);            // pushing back to a already present index based on destination
        }
    }
    return 1;   // journey added successfully
}

bool Planner::station(Query* query) {
    vector<Journey> list;                                   // stores a list of all journeys according to query
    int index = -1;
    Entry *a = dict_names.get(query->stat1);
    if(a!=NULL) index=a->value;                             //  start station available

    if(index == -1)                                         // starting station not present, so no journeys available
        return false;

    Station &start = names[index];
    float start_time = query->time1;
    for(long unsigned int i=0; i< ((start.list2).size()); i++) {            // going through all the available destination
        for(long unsigned int j=0; j< (start.list2[0].size()); j++) {       // going through all journeys of a particular destination
            Journey temp = ((start.list2)[i])[j];
            if(temp.s_t >= start_time)                                  // if journey departure is later than the passed time, add to list 
                list.push_back(temp);
        }
    }
    if (list.size() == 0)   // no journeys available based on given time constraint
        return false;

    print_station(list);    // printing all journeys accordingly
    return true;
}

void Planner::print_station(vector<Journey> &list) {        // prints the journeys passed to it accordingly
    for(long unsigned int i=0; i<list.size(); i++)
        cout << list[i].s_t << " " << list[i].desti << "\n";
    return;
}

bool Planner::possible(Query* query, int &index) {      // checks if a station is present in the names list, and alters the index to its value
    index=-1;
    Entry *a = dict_names.get(query->stat1);
    if(a!=NULL) index=a->value;                     // if station found
    if(index == -1)                                 // if station not found
        return false;
    return true;
}

bool Planner::journey(Query* query) {
    float least_d = MAX_F;                  // stored the earliest departure time for a direct journey
    float least_m = MAX_F;                  // stored the earliest departure time for a stoppered journey
    int ind = -1;
    if(!possible(query,ind)) {              // if staring station not available
        return false;
    };
    Journey direct;
    Station &start = names[ind];
    Entry *a = start.dict_journey.get(query->stat2);
    ind = -1;
    if(a!=NULL) ind=a->value;
    if(ind >= 0) {                                                  // direct journey possible
        if (shortest(start.list2[ind], query->time1, direct))
            least_d = direct.s_t;
    }

    // Checking for journey with 1 stop in between
    Journey first;          // stores the first journey of the 2-part journey
    Journey second;         // stores the second journey of the 2-part journey
    second.s_t = MAX_F;
    second.d_t = MAX_F;
    for(long unsigned int i=0; i<start.list2.size(); i++) {
        if(ind!=-1 && (int)i == ind)    // if encountering direct journey list
            continue;

        Journey dum_f;      // dummy storing 1st journey
        Journey dum_s;      // dummy storing 2nd journey
        int sec_ind = -1;
        Query dummy;
        strcpy(dummy.stat1,start.list2[i][0].desti); 
        strcpy(dummy.stat2,query->stat2); 
        dummy.time1 = query->time1;                        // storing query for 2nd part of journey
        if(!possible(&dummy, sec_ind))                     // if no available stations for 2nd journey
            continue;
        if(!shortest(start.list2[i], query->time1, dum_f))  // if no journeys from start staion to middle station
            continue;
        Entry *a = names[sec_ind].dict_journey.get(query->stat2);
        int index=-1;
        if(a!=NULL) index=a->value;
        if(index == -1)             // journey from middle station to destination unavailable
            continue;
        if(shortest(names[sec_ind].list2[index], dum_f.d_t, dum_s)) {       // if journey available
            if(dum_f.s_t == least_m && dum_s.s_t <= second.s_t) {           // if this 2-part journey is equal to earliest starting
                if(dum_s.s_t == second.s_t && dum_s.d_t > second.d_t)       // the 2nd part of journey starts later than before
                    continue;
                least_m = dum_f.s_t;                         // if 2nd part of journey is also staring earlier, then this becomes new earliest journey
                first = dum_f;
                second = dum_s;
            }
            else if(dum_f.s_t < least_m) {              // if journey is earlier than already present
                least_m = dum_f.s_t;
                first = dum_f;
                second = dum_s;
            }
        }
    }
    
    if (least_m == MAX_F && least_d == MAX_F)           // no journeys available
        return false;
    if(least_d <= least_m)                 // earliest journey is a direct one
        cout << direct.s_t << "\n";
    else                                   // earliest journey is a 2-part one
        cout << first.s_t << " " << first.desti << " " << second.s_t << "\n";
    return true;
}

bool Planner::shortest(vector<Journey> &list, float &time, Journey &ans) {          // finds earliest journey to a particular destination ou a list
                                                                                    // returns true if found any departing later than the given time
    float least = MAX_F;        // stores staring time of earliest journey
    for(long unsigned int i=0; i<list.size(); i++) {
        if((list[i].s_t < least) && (list[i].s_t >= time)) {
            least = list[i].s_t; 
            ans = list[i];
        }
    }
    if(least == MAX_F)      // if no journey found
        return false;
    return true;
}
