#include<iostream>
#include "planner.h"
#include "dictionary.cpp"
using namespace std;

void planner(Dictionary &dict,Planner P){

    for(int i=0;i>=0;i++){
        char input[32];
        cout << ">>> " ;
        cin>>input;
        if(strcmp(input,"EXIT") == 0){
            break;
        }

        if(strcmp(input,"ADD") == 0){
            char startstation[32];
            cin >> startstation;
            float starttime;
            cin >> starttime;
            char destination[32];
            cin >> destination;
            float finishtime;
            cin >> finishtime;
            strcpy(P.J[P.j].S1.name,startstation);
            strcpy(P.J[P.j].S2.name,destination);
            P.J[P.j].stime = starttime;
            P.J[P.j].ftime = finishtime;
            Entry e;
            strcpy(e.key,startstation);
            e.value = P.j;
            dict.put(e);
            P.j++;
            continue;
        }

        if(strcmp(input,"QUERY_JOURNEY") == 0){
            char startstation[32];
            cin >> startstation;
            float minstarttime;
            cin >> minstarttime;
            char destination[32];
            cin >> destination;
            Entry * x = dict.get(startstation);
            Station * NEXTSTATIONSLIST = P.get_trains(startstation);
            Journey direct;
            direct.stime = 0;
            Station intermediate;
            Station * INTERMEDIATE = new Station[64];
            int o=0;
            int m=0;
            while(NEXTSTATIONSLIST[m].starttime_to_reach_here != -1){
                if((strcmp(NEXTSTATIONSLIST[m].name,destination) == 0)&&(NEXTSTATIONSLIST[m].starttime_to_reach_here >= minstarttime)){
                    direct.ftime = NEXTSTATIONSLIST[m].reaching_time;
                    direct.stime = NEXTSTATIONSLIST[m].starttime_to_reach_here;
                }
                m++;          
            }
            int n=0;
            while(NEXTSTATIONSLIST[n].starttime_to_reach_here != -1){
                if((strcmp(NEXTSTATIONSLIST[n].name,destination) != 0)&&(NEXTSTATIONSLIST[n].starttime_to_reach_here >= minstarttime)){
                    intermediate.name = NEXTSTATIONSLIST[n].name;
                    Station * NEXTNEXTSTATIONLIST = P.get_trains(intermediate.name);
                    int p = 0;
                    while(NEXTNEXTSTATIONLIST[p].starttime_to_reach_here != -1){
                        if(strcmp(NEXTNEXTSTATIONLIST[p].name,destination) == 0){
                            INTERMEDIATE[o].name = intermediate.name;
                            INTERMEDIATE[o].starttime_to_reach_here = NEXTSTATIONSLIST[n].starttime_to_reach_here;
                            INTERMEDIATE[o].reaching_time = NEXTSTATIONSLIST[n].reaching_time;
                            INTERMEDIATE[o].startingtimefornexttrain = NEXTNEXTSTATIONLIST[p].starttime_to_reach_here;
                            o++;
                        }
                        p++;
                    }
                    }
                    n++;
            }
            if((direct.stime == 0)&&(o == 0)){
                cout << "ERROR" << endl;
                continue;
            }
            else if((direct.stime != 0)&&(o == 0)){
                cout << direct.stime <<  endl;
            }
            else if((direct.stime == 0)&& (o != 0 )){
                Station X;
                float min = INTERMEDIATE[0].starttime_to_reach_here;
                X.name = INTERMEDIATE[0].name;
                X.startingtimefornexttrain = INTERMEDIATE[0].startingtimefornexttrain;
                for(int l=1;l<o;o++){
                    if(INTERMEDIATE[l].starttime_to_reach_here < min){
                        min = INTERMEDIATE[l].starttime_to_reach_here;
                        X.name = INTERMEDIATE[l].name;
                        X.startingtimefornexttrain = INTERMEDIATE[l].startingtimefornexttrain;
                    }
                }
                cout << min << " " << X.name << " "  << X.startingtimefornexttrain << endl;
            }
            else{
                Station X;
                float min = INTERMEDIATE[0].starttime_to_reach_here;
                X.name = INTERMEDIATE[0].name;
                X.startingtimefornexttrain = INTERMEDIATE[0].startingtimefornexttrain;
                for(int l=1;l<o;o++){
                    if(INTERMEDIATE[l].starttime_to_reach_here < min){
                        min = INTERMEDIATE[l].starttime_to_reach_here;
                        X.name = INTERMEDIATE[l].name;
                        X.startingtimefornexttrain = INTERMEDIATE[l].startingtimefornexttrain;
                    }
                }
                if(min >= direct.stime){
                    cout << direct.stime << " " << destination << endl;
                }
                else{cout << min << " " << X.name << " "  << X.startingtimefornexttrain << endl;}
            }
            continue;
        }

        if(strcmp(input,"QUERY_STATION") == 0){
            char startstation[32];
            cin >> startstation;
            float minstarttime;
            cin >> minstarttime;
            int k = 0;
            for(int i= dict.get(startstation)->value;i<P.j;i++){
                if((strcmp(P.J[i].S1.name,startstation)==0)&&(P.J[i].stime >= minstarttime)){
                    cout << P.J[i].stime << " " << P.J[i].S2.name << endl;
                    k++;
                }
            }
            if(k == 0){
                cout << "ERROR" << endl;
            }
            continue;     
        }

    }
}

int main(){
    Dictionary dict;
    Planner P;
    planner(dict,P);

}