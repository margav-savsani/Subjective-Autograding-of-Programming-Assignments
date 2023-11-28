#include "planner.h"

int main(){
    Planner P;
    while(1){   
        string command;
        cout<<">>>";
        cin>>command;
        if(command=="EXIT"){      // To exit from railway planner
            break;                   
        }
        if(command=="ADD"){      // Adding entries to railway planner
            string S1,S2;
            float T1,T2;
            cin>>S1>>T1>>S2>>T2;    
            P.ADD(S1,T1,S2,T2);
        }
        if(command=="QUERY_STATION"){   // returns all the trains with given start time and destination
            string S; 
            float time=0;
            cin>>S>>time;
            P.Q_S(S,time);
        }
        if(command=="QUERY_JOURNEY"){   // soonest time function given in pdf
            string S1,S2;
            float time;
            cin>>S1>>time>>S2;
            P.Q_J(S1,time,S2);
        }
    }
    return 0;
}   
