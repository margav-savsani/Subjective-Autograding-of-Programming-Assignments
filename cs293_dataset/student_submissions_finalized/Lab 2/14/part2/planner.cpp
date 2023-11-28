/*
    Roll no: 210050098
    Name : Moningi Srija
*/

#include <iostream>
#include <string.h>
#include "planner.h"

using namespace std;

int main()
{
    dictionary store;
    
    while(true)
    {
        char qtype[32];
        cin >> qtype;  //query type

        if(strcmp(qtype,"EXIT") == 0)
        {
            break;
        }

        else if(strcmp(qtype,"ADD")==0)
        {
            char start[32],end[32];
            float a,b;
            cin >> start >> a >> end >> b;

            station k;
            k.status = 1;
            strcpy(k.sst, start);
            dtuple dt;
            dt.stime = a;
            dt.etime = b;
            strcpy(dt.est, end);
            (k.info).push_back(dt);
            store.put(k);
        }

        else if(strcmp(qtype,"QUERY_STATION")==0)
        {
            char stat[32];
            float a;
            cin >> stat >> a;
            int index = store.found(stat);
            if(index == -1)
            {
                cout << "ERROR\n";
            }
            else
            {
                store.querystation(a,index);
            }
        }

        else if(strcmp(qtype,"QUERY_JOURNEY")==0)
        {
            char start[32],end[32];
            float gtime;
            cin >> start >> gtime >> end;
            int index = store.found(start);
            if(index == -1)
            {
                cout << "ERROR" << endl;
                continue;
            }
            else
            {
                store.queryjourney(gtime,index,end);
            }
        }

        else
        {
            cout << "Invalid Command" << endl;
        }
    }
}


