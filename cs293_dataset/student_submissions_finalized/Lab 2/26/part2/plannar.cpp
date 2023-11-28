
#include<tuple>
#include "planner.h"
using namespace std;

int main(){

    Planner Train;

    for(int i=0;i>=0;i++){
        char COM[32];
        cin>>COM;
        if(strcmp(COM,"ADD")==0){
            char st[32];
            cin>>st;
            float stime;
            cin>>stime; 
            char ft[32];
            cin>>ft;
            float ftime;
            cin>>ftime;
            Train.Add(st,ft,stime,ftime);

        }
        else if(strcmp(COM,"QUERY_STATION")==0){
            char st[32];
            cin>>st;
            float stime;
            cin>>stime;  
            Train.QUERY_STATION(st,stime);

        }
        else if(strcmp(COM,"QUERY_JOURNEY")==0){
            char st[32];
            cin>>st;
            float stime;
            cin>>stime; 
            char ft[32];
            cin>>ft;
            Train.QUERY_JOURNEY(st,stime,ft);

        }

        else if(strcmp(COM,"EXIT")==0){
            break;
        }

        
    }

    




}