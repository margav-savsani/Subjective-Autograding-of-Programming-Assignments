#include "planner.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
    Planner p;

    while(true){

        string s;
        cin >> s;


        if ( s.compare("ADD") == 0 ) {
            string station1, station2;
            int time1, time2;

            
            cin >> station1 >> time1 >> station2 >> time2;

            p.add(station1, time1, station2, time2);

        }

        else if ( s.compare("QUERY_STATION") == 0 ) {
            string station1;
            int time1;

            cin >> station1 >> time1;

            p.query_station(station1, time1);
        }

        
        else if ( s.compare("QUERY_JOURNEY") == 0 ) {
            string station1, station2;
            int time1;

            cin >> station1 >> time1 >> station2;

            p.query_journey(station1, time1, station2);
        }


        else if ( s.compare("EXIT") == 0 ) {
            return 0;
        }

        else {
            cout << "INVALID INPUT";
        }

        cout << endl;

    }

    // p.add("Berlin" ,1300, "Munich" ,1700);


    return 0;
}