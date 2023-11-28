#include "planner.h"

#include<iostream>
#include<string>
#include "circularQueue.cpp"

#include"dictionary.cpp"

using namespace std;

string float_to_string(float x){
    if(x - (float)((int)x) < 0.01) return to_string((int)x);
    else return to_string(x);
}
void Planner::run(bool automatic){
    for(int i=0;i>=0;i++){
        char input[32];
        cin>>input;
        if(strcmp(input,"EXIT") == 0){
        break;
        }
        char args[32];
        Query q;

        // INS <key> <value>
        if(strcmp(input,"ADD") == 0){
            q.type = ADD_JOURNEY;

            cin >> args; strcpy(q.s1.name, args);
            cin >> q.t1;
            cin >> args; strcpy(q.s2.name, args);
            cin >> q.t2;

            this->handleQuery(q);
        }

        // DEL <key>
        else if(strcmp(input, "QUERY_STATION") == 0){
            q.type = Q_STATION;
            cin >> args; strcpy(q.s1.name, args);
            cin >> q.t1;

            this->handleQuery(q);
        }

        // FIND <key>
        else if(strcmp(input,"QUERY_JOURNEY") == 0){
            q.type = Q_JOURNEY;
            cin >> args; strcpy(q.s1.name, args);
            cin >> q.t1;
            cin >> args; strcpy(q.s2.name, args);
            
            this->handleQuery(q);
        }
    }
}

void Planner::handleQuery(Query q){
    switch(q.type){
        case ADD_JOURNEY:
            this->addJourney(q);
            break;
        case Q_JOURNEY:
            this->queryJourney(q);
            break;
        case Q_STATION:
            this->queryStation(q);
            return;
            break;
        default:
            break;
    }
}

void Planner::addJourney(Query q){
    Entry* qp = this->journey_dict.get(q.s1.name);

    if(qp == nullptr){
        Entry data;
        strcpy(data.key, q.s1.name);
        data.value = this->journey_dict.findFreeIndex(q.s1.name);
        this->journey_dict.put(data);
        
        qp = this->journey_dict.get(q.s1.name);
    }

    Journey to_add;
    strcpy(to_add.origin.name, q.s1.name);
    strcpy(to_add.destination.name, q.s2.name);
    to_add.start_time=q.t1;
    to_add.end_time=q.t2;


    if(qp->journey_index >= 128) return;
    qp->journey_queue[qp->journey_index]=to_add;
    qp->journey_index++;
}
void Planner::queryJourney(Query q){

    Entry* qp = this->journey_dict.get(q.s1.name);
    string output = "ERROR";float min_start = 2500; 
    int cur_pos;Journey cur_journey;
    for(int i=0; i<qp->journey_index; i++){
        cur_pos = i;
        cur_journey = qp->journey_queue[i];

        if(!strcmp(cur_journey.origin.name, q.s1.name)){
            if(cur_journey.start_time >= q.t1 && cur_journey.start_time < min_start){
                if(!strcmp(cur_journey.destination.name, q.s2.name)){
                    min_start = cur_journey.start_time;
                    output = float_to_string(cur_journey.start_time);
                }else{
                    Entry* qp1 = this->journey_dict.get(cur_journey.destination.name);
                    int cur_pos1;Journey cur_journey1;
                    for(int j=0; j<qp1->journey_index; j++){
                        cur_pos1 = j;
                        cur_journey1 = qp1->journey_queue[j];

                        if(!strcmp(cur_journey1.origin.name, cur_journey.destination.name)){
                            if(cur_journey1.start_time >= cur_journey.end_time){
                                if(!strcmp(cur_journey1.destination.name, q.s2.name)){
                                    min_start = cur_journey.start_time;
                                    output = float_to_string(cur_journey.start_time)+" "+cur_journey.destination.name+" "+float_to_string(cur_journey1.start_time);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    cout<<output<<"\n";
}
void Planner::queryStation(Query q){
    Entry* qp = this->journey_dict.get(q.s1.name);
    if(qp==nullptr){
        return;
    }
    Journey cur_journey;
    bool match = false;
    
    for(int i=0; i<qp->journey_index; i++){
        cur_journey = qp->journey_queue[i];
        if(!strcmp(cur_journey.origin.name, q.s1.name)){
            if(cur_journey.start_time >= q.t1){
                cout << cur_journey.start_time << " " << cur_journey.destination.name << "\n";
                match=true;
            }
        }
    }

    if(!match) cout<<"ERROR\n";
}

int main(){
    Planner p;
    p.run(true);
}