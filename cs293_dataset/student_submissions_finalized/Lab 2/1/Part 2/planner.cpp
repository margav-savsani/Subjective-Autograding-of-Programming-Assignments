
#include "planner.h"

void planner::add_journey(char start[], char end[], float i_time, float f_time){
    struct Station *s = starts.get(start); //get the entry of the starting station
    if(s == NULL){ //if not found, add it
        s = starts.add(start);
        if(s == NULL){
            cout << "Cannot add new station" << endl;
            return;
        }
    }
    //update the array of journeys from that station
    {
    Journey j;
    copy(end, j.station2);
    j.i_time = i_time;
    j.f_time = f_time;
    s->insert_starts(j);
    s->num_journeys++;
    }

    //similar thing for journeys reaching the end station
    s = ends.get(end);
    if(s == NULL){
        s = ends.add(end);
        if(s == NULL){
            cout << "Cannot add new station" << endl;
            return;
        }
    }
    {
    Journey j;
    copy(start, j.station2);
    j.i_time = i_time;
    j.f_time = f_time;
    s->insert_ends(j);
    s->num_journeys++;
    }

    //look at journeys ending at the start station
    s = starts.get(end);
    if(s != NULL){
        for(int i = 0; i < s->num_journeys; i++){
            Journey& j = s->journeys[i];
            if(j.i_time >= f_time && !j.indirect){
            //if a direct journey reaches start before i_time, add the indirect journey 
            //to the array in the starting station's entry 
                struct Station *e1 = starts.get(start);
                Journey j1;
                j1.indirect = true;
                copy(j.station2, j1.station2);
                copy(s->station1, j1.intermediate);
                j1.f_time = j.f_time;
                j1.i_time = i_time;
                j1.int_time = j.i_time;
                e1->insert_starts(j1);
                e1->num_journeys++;
            }
        }
    }

    //similarly for direct journeys from the ending station leaving after f_time
    s = ends.get(start);
    if(s != NULL){
        for(int i = 0; i < s->num_journeys; i++){
            Journey& j = s->journeys[i];
            if(j.f_time <= i_time && !j.indirect){
                struct Station *e1 = starts.get(j.station2);
                Journey j1;
                j1.indirect = true;
                copy(end, j1.station2);
                copy(start, j1.intermediate);
                j1.f_time = f_time;
                j1.i_time = j.i_time;
                j1.int_time = i_time;
                e1->insert_starts(j1);
                e1->num_journeys++;
            }
        }
    }

}

void planner::q_station(char station[], float time){
    struct Station *s = starts.get(station);
    int init = s->find_nearest_start(time);
    if(init == s->num_journeys) cout << "NO JOURNEYS FROM " << station << " AFTER " << time << endl;
    for(int i = init; i < s->num_journeys; i++){
        if(!s->journeys[i].indirect){
            cout << "Journey at " << s->journeys[i].i_time;
            cout << " to " << s->journeys[i].station2 << endl;
        }
    }
}

void planner::q_journey(char start[], char end[], float time){
    struct Station *s = starts.get(start);
    int best_index = s->find_nearest_start(time);
    for(int i = best_index; i < s->num_journeys; i++){
        if(compare(s->journeys[i].station2, end)){
            best_index = i;
            break;
        }
    }
    if(best_index == s->num_journeys) cout << "SORRY, NO JOURNEY AVAILABLE" << endl;
    else{
        if(!s->journeys[best_index].indirect){
            cout << "Direct journey: ";
            cout << s->journeys[best_index].i_time << " to " << s->journeys[best_index].f_time << endl;
        }
        else{
            cout << "Journey with a layover at " << s->journeys[best_index].intermediate << endl;
            cout << ": Start time- " << s->journeys[best_index].i_time;
            cout << ", Leave time- " << s->journeys[best_index].int_time;
            cout << ", Reaches at- " << s->journeys[best_index].f_time << endl; 
        }
    }
}

void planner::display(){
    cout << "Journeys starting from:-\n";
    starts.display();
    cout << endl << "Journeys ending at:-\n";
    ends.display();
}