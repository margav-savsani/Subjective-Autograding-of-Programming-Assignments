#include "planner.h"

int main(){
    Planner P;
    while(1){//INFINITE LOOP IS RUNNED
        string command;
        cout<<">>>";
        cin>>command;
        if(command=="EXIT"){
            break;//IF COMMAND IS THEN EXIT THE LOOP
        }
        if(command=="ADD"){//IF ADD THEN CALLING THE ADD FUNCTION FROM PLANNER.H
            string S1,S2;
            float T1,T2;
            cin>>S1>>T1>>S2>>T2;    
            P.ADD(S1,T1,S2,T2);
        }
        if(command=="QUERY_STATION"){//FUNCTION IS CALLED FROM PLANNER.H
            string S; 
            float time=0;
            cin>>S>>time;
            P.QUEERY_STATION(S,time);
        }
        if(command=="QUERY_JOURNEY"){//FUMCTION IS CALLED FROM PLANNER.H
            string S1,S2;
            float time;
            cin>>S1>>time>>S2;
            P.QUEERY_JOURNEY(S1,time,S2);
        }
    }
    return 0;
}
