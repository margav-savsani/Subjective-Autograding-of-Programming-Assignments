#include "planner.h"

int main(){
    string input;
    station_grp s;                                                 // class containing add, query station and query journey function
    while (true){
        cin >> input;

        if(input == "EXIT"){          
            break;
        }

        if(input =="ADD"){                                      //call to add function
            string s1,s2;
            float a1,a2;
            cin >> s1 >> a1 >> s2 >> a2;
            s.add(s1,a1,s2,a2);
        }

        if(input =="QUERY_JOURNEY"){                              // call to journey function from class station_grp
            string s1,s2;
            float f;
            cin >> s1>>f >>s2;
            s.journey_(s1,f,s2);
        }

        if(input =="QUERY_STATION"){                               // call to display function from class station_grp
            string s1;
            float f;
            cin >> s1 >> f;
            s.display(s1,f);
        }

    }

}