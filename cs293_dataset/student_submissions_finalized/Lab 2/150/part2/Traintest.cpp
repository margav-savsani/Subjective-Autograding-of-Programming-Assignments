#include "Train.cpp"
#include <string>
#include <cstring>

int main()
{   // interaction window
    Planner p;
    cout << "welcome to journey planner"; // starting query mode
    while (true)
    {
        cout << ">>>";
        char inputKey[32];
        cin >> inputKey;
        string s(inputKey);

        if (s == "ADD")  // for adding the journeys
        {
            char station[32], dest[32];
            float start, end;
            cin >> station >>  start >> dest>> end;
            p.put(station, dest, start, end);
        }

        if (s == "EXIT") // to exit the infinite loop 
        {
            return 0;
        }

        if (s == "QUERY_STATION")  // printing the station 
        {
            char station[32];
            float time;
            cin >> station >> time;
            p.print(station, time);
        }

        if (s == "QUERY_JOURNEY")   // searching for appopirate journey
        {
            char station[32], dest[32];
            float start;
            cin >> station >>  start >> dest;
            if(p.findjourney(station, dest, start)== -1) cout << "ERROR" << endl;
        }
    }
}