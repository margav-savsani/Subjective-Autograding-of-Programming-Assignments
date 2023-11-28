#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include "planner.h"

using namespace std;


  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  int srcStnIndex = stnNameToIndex.get(srcStnName)->value;

	// index of destination station in dictionary
	int destStnIndex = stnNameToIndex.get(destStnName)->value;

	bool isJourneyPresent = false;
	listOfObjects<StationConnectionInfo *> *journiesFromSrc = adjacency[srcStnIndex].toStations;

	listOfObjects<int> *jrnyCodes = nullptr;

	while (journiesFromSrc != nullptr)
	{
		listOfObjects<TrainInfoPerStation *> *ptr = journiesFromSrc->object->trains;

		while (ptr != nullptr)
		{

			int val = ptr->object->journeyCode;

			listOfObjects<int> *temp = jrnyCodes;
			bool flag = true;

			// checking whether this journey code is already present in our linked list
			while (temp != nullptr)
			{
				if (temp->object == val)
				{
					flag = false;
					break;
				}
				temp = temp->next;
			}

			if (flag)
			{
				if (jrnyCodes == nullptr)
				{
					jrnyCodes = new listOfObjects<int>(val);
				}
				else
				{
					listOfObjects<int> *t = jrnyCodes;
					jrnyCodes = new listOfObjects<int>(val);
					jrnyCodes->next = t;
					t->prev = jrnyCodes;
				}
			}
			ptr = ptr->next;
		}

		journiesFromSrc = journiesFromSrc->next;
	}


	listOfObjects<int> *jrnyTemp = jrnyCodes;

	// iterating over each jouneyCode originating from source station
	while (jrnyTemp != nullptr)
	{
		// here is a normal BFS as we would do on any graph

		// queue
		Q q;

		// jouney code of present journey
		int jrnyCode = jrnyTemp->object;

		// array to store distance
		int *d = new int[DICT_SIZE];

		// array to store color denoting visited or not
		int *color = new int[DICT_SIZE];
		// 0 - white
		// 1 - gray
		// 2 - black

		// initializing the above arrays
		for (int i = 0; i < DICT_SIZE; ++i)
		{
			color[i] = 0;
			d[i] = INF;
		}

		// setting for the source station
		color[srcStnIndex] = 1;
		d[srcStnIndex] = 0;
		q.push(srcStnIndex);

		// same as in a normal BFS
		// we do this until queue is empty
		while (q.empty() != true)
		{
			// getting the element at the head of queue
			int currStnIndex = q.front();

			// stations adjacent to current station
			listOfObjects<StationConnectionInfo *> *currTo = adjacency[currStnIndex].toStations;

			// iterating over adjacent nodes to determine connectedness
			while (currTo != nullptr)
			{
				listOfObjects<TrainInfoPerStation *> *currJournies = currTo->object->trains;

				while (currJournies != nullptr)
				{
					// journey code
					int val = currJournies->object->journeyCode;

					// if unvisited
					if (color[currTo->object->adjacentStnIndex] == 0)
					{
						// if connected
						if (val == jrnyCode)
						{

							int indx = currTo->object->adjacentStnIndex;
							// setting appropriate color
							color[indx] = 1;
							// setting distance
							d[indx] = d[currStnIndex] + 1;
							// pushing station in queue
							q.push(indx);
							break;
						}
					}
					currJournies = currJournies->next;
				}

				currTo = currTo->next;
			}
			// pop the station
			q.pop();
			// set color to black
			color[currStnIndex] = 3;
		}

		// if connected
		if (d[destStnIndex] < INF)
		{	
			
			// formatted printing 

			isJourneyPresent = true;

			listOfObjects<StationConnectionInfo *> *journiesFromSrc = adjacency[srcStnIndex].toStations;
			

	return;
}

#endif
