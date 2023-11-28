#include<string.h>
#include "planner.h"


bool Planner::add_start(string s1, float t1, string s2, float t2){
    Train tr(s1,t1,s2,t2);
    Entry* E = Start.get(tr.S.Sta);
    if (E->key[0] == '\0'){
        strcpy(E->key, tr.S.Sta);
        E->value->QInsert(tr);
    }
    else {
        E->value->QInsert(tr);
    }
    return 1;
}

bool Planner::add(string s1, float t1, string s2, float t2){
    if (add_start(s1,t1,s2,t2)){
        return 1;
    }
    return 0;
}

bool Planner::query_station(string s1, float t1){
    char C[32];
    strcpy(C, s1.c_str());
    Entry* E = Start.get(C);
    if (E->key[0] == '\0'){
        cout << "Incorrect query, station doesn't exist!" << endl;
        return 0;
    }
    for (int i = 0; i < E->value->size(); i++){
        if (E->value->geti(i).start_time >= t1){
            cout << E->value->geti(i).start_time << " " << E->value->geti(i).D.Sta << endl;
        }
        else {
            cout << "All the trains leave before input time" << endl;
        }
    }
    return 1;
}

bool Planner::query_journey(string s1, float t1, string s2){
    char C1[32], C2[32];
    strcpy(C1, s1.c_str());
    strcpy(C2, s2.c_str());
    Entry* E = Start.get(C1);
    int I = -1, J = -1;
    for (int i = 0; i < E->value->size(); i++){
        if ((strcmp(E->value->geti(i).D.Sta, C2) == 0) && (E->value->geti(i).start_time >= t1) 
        && (I == -1 || E->value->geti(i).start_time < E->value->geti(I).start_time)){
            I = i;
            J = -1;
        }
        else if ((E->value->geti(i).start_time >= t1)&&(strcmp(E->value->geti(i).D.Sta, C2) != 0)
        &&(I == -1 ||  (E->value->geti(i).start_time < E->value->geti(I).start_time))){
            Entry* E1 = Start.get(E->value->geti(i).D.Sta);
            for (int j = 0; j < E1->value->size(); j++){
                if (strcmp(E1->value->geti(j).D.Sta,C2) == 0
                // && (E->value->geti(i).end_time < E1->value->geti(j).end_time)
                ){
                    I = i;
                    J = j;
                    break;
                }
            }
        }
    }
    if (I == -1){
        cout << "Journey Unavailable" << endl;
        return 0;
    }
    else{
        cout << E->value->geti(I).start_time;
        if (J != -1){
            Entry* E1 = Start.get(E->value->geti(I).D.Sta);
            cout << " " << E->value->geti(I).D.Sta << " " << E1->value->geti(J).start_time;
        }
        cout << endl;
    }
    return 1;
}