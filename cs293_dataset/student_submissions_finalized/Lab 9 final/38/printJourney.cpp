#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

listOfObjects<TrainInfoPerStation *> *printvalue;

bool check(listOfObjects<StationConnectionInfo *> *adjacent_stations, int jorney_code)
{
	bool Ans = false;
	listOfObjects<TrainInfoPerStation *> *Train = adjacent_stations->object->trains;
	while(Train != nullptr)
	{
		if (Train->object->journeyCode == jorney_code) 
		{
			printvalue = Train;
			Ans = true;
			break;
		}
		Train = Train->next;
	}
	return Ans;
}

int next_station(int present_station_index, int journey_code, StationAdjacencyList* adjacency)
{
	int Ans = -1;
	listOfObjects<StationConnectionInfo *> *adjacent_stations = adjacency[present_station_index].toStations;
	while(adjacent_stations != nullptr)
	{
		adjacent_stations->object->trains->object;
		if (check(adjacent_stations, journey_code))
		{
			Ans = adjacent_stations->object->adjacentStnIndex;
			break;
		}
		adjacent_stations = adjacent_stations->next;
	}
	return Ans;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
	// insert your code here

	int scrStnIdx = stnNameToIndex.get(srcStnName)->value;
	int destStnIdx = stnNameToIndex.get(destStnName)->value;

	listOfObjects<StationConnectionInfo *> *adjacent_stations = adjacency[scrStnIdx].toStations;
	

	// listOfObjects<int> *JOURNEYCODES;

	int journeycodes[100];
	int no_of_trains = 0;

	while(adjacent_stations != nullptr)
	{
		listOfObjects<TrainInfoPerStation *> *train = adjacent_stations->object->trains;

		while(train != nullptr)
		{
			int x = train->object->journeyCode;
			journeycodes[no_of_trains] = x;
			no_of_trains++;
			// listOfObjects<int> *y = new listOfObjects(x);
			// y->next = JOURNEYCODES;
			// JOURNEYCODES->prev = y;
			// JOURNEYCODES = y;
			train = train->next;
		}

		adjacent_stations = adjacent_stations->next;
	}

	bool journey_found = false;

	listOfObjects<TrainInfoPerStation *> *FOUND_TRAINS;	

	// while(JOURNEYCODES != nullptr)
	for (int i = 0; i < no_of_trains; i++)
	{
		int present_station_index = scrStnIdx;
		// int x = JOURNEYCODES->object;
		int x = journeycodes[i];
		while(present_station_index != -1)
		{
			present_station_index = next_station(present_station_index, x, adjacency);
			if (present_station_index == destStnIdx)
			{
				journey_found = true;
				printStationInfo(printvalue);
				break;
			}
		}
		// JOURNEYCODES = JOURNEYCODES->next;
	}
	if (!(journey_found))
	{
		cout << "No direct journeys available\n";
	}

	// while(JOURNEYCODES != nullptr)
	// {
	// 	int present_station_index = scrStnIdx;
	// 	adjacent_stations = adjacency[present_station_index].toStations;
	// 	while(adjacent_stations != nullptr)
	// 	{
	// 		bool train_found = false;
	// 		if (adjacent_stations->object->adjacentStnIndex == destStnIdx)
	// 		{
	// 			listOfObjects<TrainInfoPerStation *> *train = adjacent_stations->object->trains;
	// 			while(train != nullptr)
	// 			{
	// 				if (train->object->journeyCode == JOURNEYCODES->object)
	// 				{
	// 					if (FOUND_TRAINS == nullptr)
	// 					{
	// 						FOUND_TRAINS = new listOfObjects(train->object);
	// 					}
	// 					else 
	// 					{
	// 						listOfObjects<TrainInfoPerStation *> *TRAIN = new listOfObjects(train->object);
	// 						TRAIN->next = FOUND_TRAINS;
	// 						// FOUND_TRAINS->prev = TRAIN;
	// 						FOUND_TRAINS = TRAIN;
	// 					}
	// 					train_found = true;
	// 					journey_found = true;
	// 					break;
	// 				}
	// 				train = train->next;
	// 			}
	// 		}
	// 		else 
	// 		{
	// 			listOfObjects<TrainInfoPerStation *> *train = adjacent_stations->object->trains;
	// 			while(train != nullptr)
	// 			{
	// 				if (train->object->journeyCode == JOURNEYCODES->object)
	// 				{
	// 					present_station_index = adjacent_stations->object->adjacentStnIndex;
	// 					train_found = true;
	// 					break;
	// 				}
	// 				train = train->next;
	// 			}
				
	// 		}
	// 		if (train_found) break;
	// 		adjacent_stations = adjacent_stations->next;
	// 	}
	// }

	// if (journey_found) 
	// {
	// 	while(FOUND_TRAINS != nullptr)
	// 	{
	// 		printStationInfo(FOUND_TRAINS);
	// 	}
	// }
	// else
	// {
	// 	cout << "No direct journeys available\n";
	// }

	// Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
	// for the source station and then we can print it out by invoking
	// printStationInfo that we had used in Lab 7.
	// printStationInfo is a private member function of the Planner class
	// It is declared in planner.h and implemented in planner.cpp

	return;
}

#endif
