#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "planner.cpp"
using namespace std;

/*

In interactive mode you can give commands '
  QUIT
  INS <key> <value>
  DEL <key>
  FIND <key>

*/
/*
to run code add the file name in the ifstream open part and do g++ main.cpp and ./a.out
to know all the entries add SHOW in the input file.
*/
void PlannerHandler(Planner &planner)
{
    ifstream f;
    f.open("input2.in");
    
    for (int i = 0; i >= 0; i++)
    {
        // if(f.eof());
        char input[32];
        f >> input;
        if (strcmp(input, "EXIT") == 0)
        {
            break;
        }

        // ADD <key> <value>
        if (strcmp(input, "ADD") == 0)
        {

            // taking input of values.

            char station1[32];
            f >> station1;
            
            int start_time;
            f >> start_time;
            
            char station2[32];
            f >> station2;
            
            int end_time;
            f >> end_time;
            
            // cout << station1 << "\n";
            Journey data;

            //   string demo_key = station1 + station2;
            // data.key = &station1[0];
            data.key = new char[32];
            strcpy(data.key, station1);
            //   cout << "no-issue" << endl;

            // filling values in the data members.
            // data.start = &station1[0];
            data.start = new char[32];
            strcpy(data.start, station1);
            // data.end = &station2[0];
            data.end = new char[32];
            strcpy(data.end, station2);
            data.time_start = start_time;
            data.time_end = end_time;
            // cout << "data correctness : " << data.start << " " << data.time_start << " " << data.end << " " << data.time_end << "\n";
            int hashValueData = planner.hashValue(data.key);
            int freeIndexData = planner.findFreeIndex(data.key);
            // cout << "Hash Value: " << hashValueData << endl;
            // cout << "Free Location: "<< freeIndexData << endl;
            if (freeIndexData >= 0)
            {
                planner.put(data);
                // cout << "Successfully Added " << endl;
            }
        }

        // QUERY_JOURNEY <key>
        else if(strcmp(input, "QUERY_JOURNEY") == 0){
          char station1[32];
          f >> station1;
          int start_time;
          f >> start_time;
          char station2[32];
          f >> station2;

          int check_time = planner.query_journey(station1, station2, start_time, false);
          if(check_time == error_time){
            cout << "ERROR\n";
          }
        }

        // Query_Station <key>
        else if (strcmp(input, "QUERY_STATION") == 0)
        {
            char inputKey[32];
            f >> inputKey;
            int check;
            f >> check;
            if(!planner.query_station(inputKey, check))
                cout << "The given station with suitable time not found\n";
        }
        // Show all entries
        else if(strcmp(input, "SHOW") == 0){
            planner.show();
        }
    }
}

void interactive()
{
    Planner planner;
    PlannerHandler(planner);
}

int main()
{
    interactive();
    return 0;
}
