#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  for(int i = 0 ;i < DICT_SIZE ;i++){
    //cout << "here...." << endl;
    StationAdjacencyList* temp = &adjacency[i];
    
    listOfObjects<StationConnectionInfo *> *from = temp->fromStations;
    while(from != nullptr){
      cout <<"here" << endl;
      if(stnNameToIndex.getKeyAtIndex(from->object->adjacentStnIndex) == srcStnName){
        cout << "source station = " << from->object->trains->object->journeyCode << endl;
      }
    }
  }
  
  cout << "This function is to be implemented by you." << endl;
  
  return;
}
