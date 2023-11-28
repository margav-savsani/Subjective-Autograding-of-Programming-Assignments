#ifndef PLANNER_H
#include "planner.h"
#endif

#ifnded STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
    int srci=stnNameToIndex.hashValue(srcStnName);
    int desti=stnNameToIndex.hashValue(destStnName);

    bool visited[DICT_SIZE];
    visited[srci]=true;
    vector<int> p;
    p.push_back(srci);
    while(p.size!=0){
      int x=p.pop();
      listOfobjects<StationConnectionInfo> *src_=adjacency[x].toStations;
      while(src!=NULL){
        listOfobjects<TrainInfoPerStation> *tra=src_->object->trains;
        p.push_back(tra);
      }
    } 
  
  // insert your code here
  //PriorityQueue<TrainInfoPerStation> *x = new PriorityQueue<T>((o1,o2)->(srcStnName-destStnName));
  
  //cout << "This function is to be implemented by you." << endl;
  
  return;
}
