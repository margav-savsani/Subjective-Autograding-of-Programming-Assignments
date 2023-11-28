#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include<list>
using namespace std;



void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;
    // get entries of source and destination stations by using given strings
    Entry<int> *src = stnNameToIndex.get(srcStnName);
    Entry<int> *dest = stnNameToIndex.get(destStnName);
    // get indices of the source and destination stations
    int srcindex = src->value;
    int destindex = dest->value;
    // a list of TrainInfoPerStation objects created to print at last which will print the direct journeys
    list<TrainInfoPerStation *> toprint = new listOfObjects<TrainInfoPerStation>(srcindex, 0, 0, 0);
    // a bool array created which denotes if each node is visited or not
    bool visited;
    visited = new bool[DICT_SIZE];
    // array initially initialised to false
    for (int i = 0; i < DICT_SIZE; i++)
        visited[i] = false;
    // queue created to implement bfs
    list<StationAdjacencyList> queue;
    // the source station is marked visited
    visited[adjacency[srcindex]] = true;
    // source pushed into the queue
    queue.push_back(adjacency[srcindex]);
    listOfObjects<int>::iterator i;
    // modified bfs implemented
    while (!queue.empty()) {
        StationAdjacencyList currVertex = queue.front();
        // cout << "Visited " << currVertex << " ";
        queue.pop_front();
        // adjacent vertices of the currVertex are traversed and checked
        for (i = adjacency[currVertex->toStations->object->adjacentStnIndex].begin(); i != adjacency[currVertex.toStations->object->adjacentStnIndex].end(); ++i) {
            int adjVertex = *i;
            if (!visited[adjVertex]) {
                // if adjacent vertex is the destination station then push it into the list and brak the loop 
                if(currVertex.toStations.adjacentStnIndex == destindex){
                    toprint.push_back(dest->value->toStations->trains->object);
                    break;
                }
                if(currVertex->toStations.adjacentStnIndex == adjVertex){
                    visited[adjVertex] = true;
                    queue.push_back(adjVertex);
                    toprint.push_back((currVertex.toStations)->trains->object);
                }
                else{
                    visited[adjVertex] = true;
                    queue.push_back(adjVertex);
                }
            }
        }
    }
    // printStationInfo function called on toprint list of TrainInfoPerStation object to print direct journeys
    printStationInfo(toprint);
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
