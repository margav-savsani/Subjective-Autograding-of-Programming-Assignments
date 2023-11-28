#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

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

  // First thing: Print the adjacency list
	for(int i=0; i<DICT_SIZE; i++){
		if(adjacency[i].toStations != nullptr || adjacency[i].fromStations != nullptr){
			cout << "Station: " << stnNameToIndex.getKeyAtIndex(i) << "::::::::::"<< endl;

			cout << "to-List\n";

			auto currNode = adjacency[i].toStations;
			while(currNode != nullptr){
				cout << "---" << endl;
				cout << stnNameToIndex.getKeyAtIndex(currNode->object->adjacentStnIndex) << endl;
				auto iNode = currNode->object->trains;
				while(iNode != nullptr){
					cout << iNode->object->journeyCode << ", " << iNode->object->arrTime << ", " << iNode->object->depTime << endl;
					iNode = iNode->next;
				}
				cout << "---" << endl;
				currNode = currNode->next;
			}

			cout << "\nfrom-List\n";
			currNode = adjacency[i].fromStations;
			while(currNode != nullptr){
				cout << "---" << endl;
				cout << stnNameToIndex.getKeyAtIndex(currNode->object->adjacentStnIndex) << endl;
				auto iNode = currNode->object->trains;
				while(iNode != nullptr){
					cout << iNode->object->journeyCode << ", " << iNode->object->arrTime << ", " << iNode->object->depTime << endl;
					iNode = iNode->next;
				}
				cout << "---" << endl;
				currNode = currNode->next;
			}

			cout << "\n\n\n" << endl; 
		}
	}


  
  return;
}

#endif
