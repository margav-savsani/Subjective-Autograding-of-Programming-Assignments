#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

/** One very simple solution exists, without BFS, :
 * make a list of all journey codes from source station that depart from there
 * make a list of all journey codes from destination station that arrive there
 * take intersection of the lists and print them
 * 
 * But of course, since the lab is about BFS, a different approach:
 * make a list of all trains that leave source. Start moving in BFS way and at each station check whether the journey codes in our list are present or not
 * if not, delete them, if present, continue in those paths
 */



void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int source = stnNameToIndex.get(srcStnName)->value;
  int dest = stnNameToIndex.get(destStnName)->value;

  listOfObjects<TrainInfoPerStation*> A = nullptr;
  listOfObjects<StationConnectionInfo*> *B = adjacency[source].toStations;


  
  cout << "This function is to be implemented by you." << endl;
  
  return;
}
