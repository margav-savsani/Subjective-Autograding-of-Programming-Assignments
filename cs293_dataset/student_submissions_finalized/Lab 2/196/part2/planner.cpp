//Copyright: Yuvraj Singh 210050172
#include "planner.h"                        //Header Declaration
void RailwayManagementSystem(){             //Implements the Railway Management System
    Planner p;
    for (int i=0;i>=0;i++){                            //Taking user input 
        char input[32];
        cin>>input;
        if(strcmp(input,"EXIT") == 0){                  //If user says exit it will end the implementation
            break;
        }
        else if(strcmp(input,"ADD")==0){                //If the user says add it adds the speacified input to the Dictionary Railway through planner class
            char s1[32];
            cin>>s1;
            float st;
            cin>>st;
            char s2[32];
            cin>>s2;
            float ft;
            cin>>ft;
            p.add(s1,st,s2,ft);
            continue;
        }
        else if(strcmp(input,"QUERY_STATION")==0){      //If the user says query_station then it prints all trains starting from s1 on or after st
            char s1[32];
            cin>>s1;
            float st;
            cin>>st;
            p.q_station(s1,st);
            continue;
        }
        else if(strcmp(input,"QUERY_JOURNEY")==0){      //If the user says query_journey then it prints the journey details from s1 to s2 shortest path but with soonest possible start time
            char s1[32];    
            cin>>s1;
            float st;
            cin>>st;
            char s2[32];
            cin>>s2;
            p.q_journey(s1,st,s2);
            continue;
        }
    }
}
int main(){
    RailwayManagementSystem();                          //Call the RMS
    return 0;
}
//End of Code