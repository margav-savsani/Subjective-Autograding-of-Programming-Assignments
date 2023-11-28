#include <fstream>
#include "planner.h"
#include <iterator>
#include "dictionary.h"
#include "Journey.h"
#include <iterator>

using namespace std;

// This accept queries from sample-planner.txt and stores ouput in result.txt
void Planner::run(){

	ifstream input;
	ofstream output;
	input.open("sample-planner.txt");
	output.open("result.txt");
	
	char queryType[32];
	
	while(input >> queryType)
	{
		if(strcmp(queryType , "ADD") == 0)
		{
			char stationA[32] , stationB[32];
			float start , end;
			
			//taking train start station , end station , start time, end time as input from file
			input >> stationA >> start >> stationB >> end;
			
			// saving this data into struct Journey
			struct Journey *j = new struct Journey;
			strcpy(j->from , stationA);
			j->departure = start;
			strcpy(j->destination , stationB);
			j->arrival = end;
			
			//Putting journey into dictionary
			bool journeyAdded = D.put(*j);
			if(!journeyAdded) output << "No space available\n";
			
		}
		
		else if( strcmp(queryType , "QUERY_JOURNEY" ) == 0)
		{	
			//Taking input from file
			char stationA[32] , stationB[32];
			float start;
			input >> stationA >> start >> stationB;
			
			//pulling trains starting from stationA
			vector<struct Journey*> upcomingTrains = D.get(stationA);
			float minTimeViaDirect = INT_MAX , minTimeViaStop = INT_MAX , intermediateTime;
			char intermediateStation[32];
			
			//If no trains available
			if(upcomingTrains.empty())
			{
				output <<"No trains available, Try again tomorrow!  :)\n";
			}
			else
			{	
				vector<struct Journey*>::iterator itr;
				
				for(itr = upcomingTrains.begin() ; itr != upcomingTrains.end() ; itr++)
				{
					//if train goes from staionA to staionB directly
					if( strcmp((*itr)->destination , stationB) == 0)
					{
						if((*itr)->departure >= start) minTimeViaDirect = min(minTimeViaDirect , (*itr)->departure);
					}
					//Searching from trains with one intermediate stop that go from A to B via C
					else
					{
						if( (*itr)->departure >= start) 
						{
							// Searching for trains from intermediate station
							vector<struct Journey*> oneStopTrains = D.get((*itr)->destination);
							
							vector<struct Journey*>::iterator itr2;
							
							// Searching for trains from intermediate station to final destination
							for(itr2 = oneStopTrains.begin() ; itr2 != oneStopTrains.end() ; itr2++)
							{
								if( strcmp( (*itr2)->destination , stationB) == 0 && (*itr2)->departure >= (*itr)->arrival)
								{
									minTimeViaStop = (*itr)->departure;
									strcpy(intermediateStation , (*itr)->destination);
									intermediateTime = (*itr2)->departure;
								}	
							}
						}
					
					}
				}
				//If no trains are available
				if(minTimeViaDirect == INT_MAX && minTimeViaStop == INT_MAX)
				{
					output << "No trains available at the moment! Please try again tomorrow. :)\n";
				}	
				// If direct train is available
				else if(minTimeViaDirect <= minTimeViaStop)
				{
					output<<minTimeViaDirect<<endl;
				}
				// If trains is available with one stop
				else
				{	
					output<<minTimeViaStop<<' '<<intermediateStation<<' '<<intermediateTime<<endl;
				}		
			}				
						
						  	
					
		
		}
		
		else if(strcmp(queryType , "QUERY_STATION") == 0)
		{
			//Taking input station from file
			char station[32];
			input >> station;
			float startTime;
			input >> startTime;
			
			//Getting list of trains which start at that station
			vector<struct Journey*> upcomingTrains = D.get(station);
			
			//If list is empty
			if(upcomingTrains.empty())
			{
				output <<"No trains available at the moment! Try again tomorrow.  :)\n";
			}
			// Else print departure time and destination of train for each element in the list
			else
			{
				vector<struct Journey*>::iterator itr;
				
				for(itr = upcomingTrains.begin(); itr!=upcomingTrains.end() ; itr++)
				{
					if((*itr)->departure >= startTime) output << (*itr)->departure << ' ' << (*itr)->destination << endl;
				}
			}
				
		}
		
		else if(strcmp(queryType , "EXIT" ) == 0) 
		{
			break;
		}
		
		else 
		{
			output << "INVALID QUERY\n";
			continue;
		}
	}
	
	input.close();
	output.close();
	return;
}		


