#include<iostream>
#include<cstring>
#include "planner.h"

using namespace std;

void Query_Handler(Planner planner)
{
	char s[32];
	cout << "WELCOME TO RAIL PLANNER\n\n";
	cout << "YOU CAN USE THREE COMMANDS\n";
	cout << "1) ADD <station_one> <start_time> <station_two> <finish_time>\n Used to add a new train route from station_one to station_two at timings start_time to finish_time.\n";
	cout << "2) QUERY_STATION <station_one> <start_time>\n Shows all trains from station_one which starts after starting_time.\n";
	cout << "3) QUERY_JOURNEY <station_one> <start_time> <station_two>\n Gives fastest route from station_one to station_two with atmost one connection between them.\n";
	cout << ">>>";
	cin >> s;
	int i = 1;
	while (true)
	{
		if (!strcmp(s, "EXIT")) return;
		//The program stops if we input EXIT

		else if (!strcmp(s, "ADD"))
		//Adds the train to the planner
		{
			
			char starting_point[32];
			float starting_time;
			char ending_point[32];
			float ending_time;
			cin >> starting_point >> starting_time >> ending_point >> ending_time;
			planner.Add(starting_point, starting_time, ending_point, ending_time);
			cout << ">>>";
			cin >> s;
		}

		else if (!strcmp(s, "QUERY_STATION"))
		//Gives all the trains from station after the given starting time
		{
			char station_name[32];
			cin >> station_name;
			float start_time;
			cin >> start_time;
			planner.querystation(station_name, start_time);
			cout << ">>>";
			cin >> s;
		}

		else if (!strcmp(s, "QUERY_JOURNEY"))
		//Gives fastest route between two stations
		{
			char st[32];
			float time;
			char et[32];
			cin >> st >> time >> et;
			planner.query_journey(st, time, et);
			cout << ">>>";
			cin >> s;
		}

		else 
		{
			cout << ">>>";
			cin >> s;
		}
	}
}

int main(){
	Planner planner;
	Query_Handler(planner);
}
