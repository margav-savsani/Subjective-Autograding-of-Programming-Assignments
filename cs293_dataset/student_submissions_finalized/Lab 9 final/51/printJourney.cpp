#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"


#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"


#endif
#include <queue>
using namespace std;
// used bds on all nodes from source
// used queue to keep track of nodes and update queue after checking bds for that node
namespace qu
{
	queue<int> q; //stores indices on which bds is to be applied i.e the bds array
	queue<int> l; //contains journey codes  of trains coming from source source
	int count = 0; // dummy variable to update l
	listOfObjects<TrainInfoPerStation*> *direcJourList; // list of trains that have a direct journey from source to destination
  int no_of_direcs = 0; // no of distinct trains with a direct journey
	int print = 0; // dummy variable used to print
}

// returns pointer of the last train in the list whose next is null
listOfObjects<TrainInfoPerStation*> *get_poi(listOfObjects<TrainInfoPerStation*> *direcJourList, int no_of_direcs)
{
	if (no_of_direcs == 1)
	{
		return direcJourList;
	}
	else
	{
		return get_poi(direcJourList->next, no_of_direcs - 1);
	}
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
	int ind1 = stnNameToIndex.get(srcStnName)->value;
	int ind2 = stnNameToIndex.get(destStnName)->value;
	listOfObjects<StationConnectionInfo*> *gStations = adjacency[ind1].toStations; // creating a copy so if can reuse the orginal again
	while (gStations != NULL)
	{
		if (gStations->object->trains != NULL)
		{
			listOfObjects<TrainInfoPerStation*> *currTrain = gStations->object->trains;
			while (currTrain != NULL)
			{
				queue<int> dum = qu::q;
				int dum_count = 0;
				while (!dum.empty())
				{
					int alp = dum.front();
					dum.pop();
					if (alp == gStations->object->adjacentStnIndex)
					{
						dum_count++;
					}
				}

				if (dum_count == 0)
				{
					qu::q.push(gStations->object->adjacentStnIndex);
				}
        //storing the neighbour indices of source
				if (qu::count == 0)
				{
					qu::l.push(currTrain->object->journeyCode);
				}
        // if there exists a journey to destination searching if it orgiated from source by using l
				if (gStations->object->adjacentStnIndex == ind2)
				{
					queue<int> indices = qu::l;
					while (!indices.empty())
					{
						if (currTrain->object->journeyCode == indices.front())
						{
							if (qu::no_of_direcs == 0)
							{
								qu::direcJourList = new listOfObjects<TrainInfoPerStation*> (currTrain->object);
							}
							else
							{
								get_poi(qu::direcJourList, qu::no_of_direcs)->next = new listOfObjects<TrainInfoPerStation*> (currTrain->object);
							}

							qu::no_of_direcs++;
						}

						indices.pop();
					}
				}
        //between 2 adjacent stations checking all the trains
				currTrain = currTrain->next;
			}
		}
    //checking all the stations
		gStations = gStations->next;
	}

	qu::count++;

  //using recursion to to apply printdirectjourney in eveery node of bds
  //and updating the queue after bds
 
	if (!qu::q.empty())
	{
		int ind3 = qu::q.front();
		qu::q.pop();
		qu::print++;
		printDirectJourneys(stnNameToIndex.getKeyAtIndex(ind3), destStnName);
	}

 //printing the list only once using dummy int print
	if (qu::print > 0)
	{
		printStationInfo(qu::direcJourList);
		qu::print = 0;
	}
 // updating count and no_of direcs after printing to zeroes
	qu::count--;
	qu::no_of_direcs = 0;
	while (!qu::l.empty())
	{
		qu::l.pop();
	}

	// Get the list of journeys as a listOfObjects<TrainInfoPerStation*>
	// for the source station and then we can print it out by invoking
	// printStationInfo that we had used in Lab 7.
	// printStationInfo is a private member function of the Planner class
	// It is declared in planner.h and implemented in planner.cpp
	return;
}


#endif