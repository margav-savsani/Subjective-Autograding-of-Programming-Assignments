#include <iostream>
using namespace std;
#include "planner.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include <cmath>
#include <vector>

int main(){
    Planner p;
    char start[32];
    char end[32];
    float ts, te;

    for(int i=0;i>=0;i++){
        char input[32];
        cout<<">>> ";
        cin>>input;
        if(strcmp(input,"EXIT")==0){
            break;
        }

        if(strcmp(input,"ADD")==0){
            cin >> start;
            cin >> ts;
            cin >> end;
            cin >> te;
            p.add(start, ts, end, te);
        }

        else if(strcmp(input,"QUERY_STATION")==0){
            cin >> start;
            cin >> ts;
            query_queue *q = p.query(start, ts);
            while((*q).get_length() != 0){
                Query *elem = (*q).get_head();
                cout << (*elem).starttime << " " << (*elem).destination << endl;
                (*q).remove();
            }
            delete q;
        }

        else if(strcmp(input,"QUERY_JOURNEY")==0){
            cin >> start;
            cin >> ts;
            cin >> end;

            Journey *j = p.query_journey(start, ts, end);
            if ((*j).start <= 2400){
                if ((*j).leave_time == 2500){
                    cout << (*j).start << endl;
                }
                else{
                    cout << (*j).start << " " << (*j).intermediate << " " << (*j).leave_time << endl;
                }
            }
        }
    }
}

