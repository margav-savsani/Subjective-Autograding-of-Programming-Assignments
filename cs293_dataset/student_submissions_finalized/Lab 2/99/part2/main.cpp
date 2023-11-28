#include "journey.cpp"

int main()
{
    cout << "Rail Planner System\n\n";
    cout << "--To add train route: ADD <station_one> <start_time> <station_two> <finish_time>\n";
    cout << "--To get list of trains from station_one starting from and after start_time: QUERY_STATION <station_one> <start_time>\n";
    cout << "--To get the soonest journey from station_one to station_two: QUERY_JOURNEY <station_one> <start_time> <station_two>\n";
    cout << "--To exit query loop: QUIT\n\n";
    planner P;
    while (true)
    {
        string cmd;
        cout << ">>> ";
        cin >> cmd;
        if (cmd == "ADD")
        {
            string station_one, station_two;
            float start_time, finish_time;
            cin >> station_one >> start_time >> station_two >> finish_time;
            journey x(station_one, station_two, start_time, finish_time);
            bool check = P.addjourney(x);
            if (!check) cout << "Route not added: no available slots\n";
        }
        else if (cmd == "QUERY_STATION")
        {
            string station_one;
            float start_time;
            cin >> station_one >> start_time;
            int numofroutes = 0, indices[64];
            journey routes[64];
            bool x = P.getall(station_one, start_time, routes, indices, numofroutes);
            if (!x) cout << "ERROR: station doesn't exist\n";
            else
            {
                if (numofroutes == 0) cout << "No such routes exist\n";
                for (int i = 0; i < numofroutes; i++)
                {
                    journey * c = P.getA(indices[i]);
                    cout << c->start_time << ' ' << c->station_2 << endl;
                }
            }
        }
        else if (cmd == "QUERY_JOURNEY")
        {
            string station_one, station_two;
            float start_time;
            cin >> station_one >> start_time >> station_two;
            int index;
            int x = P.getsoonest(station_one, start_time, station_two, index);
            if (x == -1) cout << "ERROR: No possible route\n";
            else if (x == 1)
            {
                journey * c = P.getA(index);
                cout << c->start_time << endl;
            }
            else
            {
                three_s * c = P.getB(index);
                cout << c->start_time1 << ' ' << c->s2 << ' ' << c->start_time2 << endl;
            }
        }
        else if (cmd == "QUIT")
        {
            return 1;
        }
        else continue;
    }
}