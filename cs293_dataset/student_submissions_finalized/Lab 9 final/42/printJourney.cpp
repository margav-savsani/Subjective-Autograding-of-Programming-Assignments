#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef VECTOR_H
#include <vector>
#include <algorithm>
#endif

#ifndef UTILITY_H
#include <utility>
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int src_index = stnNameToIndex.get(srcStnName)->value;
  int dest_index = stnNameToIndex.get(destStnName)->value;
  if (srcStnName == destStnName){
    cout<<"The source and destination are the same"<<endl;
    return;
  }
  int queue_index = 0;
  vector<vector<pair<int,int> > > bfs_queue;

  vector<int> vec_codes;

  listOfObjects<StationConnectionInfo*> * a = adjacency[src_index].toStations;
  vector<pair<int,int> > vec;
  while (a!=nullptr){
    StationConnectionInfo* b = a->object;
    listOfObjects<TrainInfoPerStation *> * c = b->trains;
    while(c!=nullptr){
      vec.push_back(pair<int,int>(src_index,c->object->journeyCode));
      c = c->next;
    }
    a = a->next;
  }


  bfs_queue.push_back(vec);
  int len = 0;
  while (bfs_queue.size() > len){
    /*for(int i=0;i<bfs_queue.size();i++){
      for(int j=0;j<bfs_queue[i].size();j++){
        cout<<i<<" : "<<bfs_queue[i][j].first<<" "<<bfs_queue[i][j].second<<endl;
      }
    }*/
    len = bfs_queue.size();
    while (queue_index < len){
      vector<pair<int,int> > vec1 = bfs_queue[queue_index];
      int stn_index = vec1[0].first;
      if (stn_index == dest_index){
        for(int i=0;i<vec1.size();i++){
          vec_codes.push_back(vec1[i].second);
        }
        queue_index++;
        continue;
      }
      listOfObjects<StationConnectionInfo*> * a = adjacency[stn_index].toStations;

      while (a!=nullptr){
        StationConnectionInfo* b = a->object;
        int to_index = b->adjacentStnIndex;
        vector<pair<int,int> > vec = bfs_queue[queue_index];
        vector<pair<int,int> > vec4;

        listOfObjects<TrainInfoPerStation *> * c = b->trains;
        while(c!=nullptr){
          pair<int,int> pair1 = pair<int,int>(stn_index,c->object->journeyCode);
          pair<int,int> pair2 = pair<int,int>(to_index,c->object->journeyCode);
          bool found = false;
          if ((find(vec.begin(),vec.end(),pair1) != vec.end())) {
            for(int j = 0;j<bfs_queue.size();j++){
              vector<pair<int,int> > vec3 = bfs_queue[j];
              if ((find(vec3.begin(),vec3.end(),pair2) != vec3.end())){
                found = true;
              }
            }
            if (!found) {
              vec4.push_back(pair2);
            }
          }
          c = c->next;
        }
        if (vec4.size() != 0) bfs_queue.push_back(vec4);
        a = a->next;
      }
      queue_index++;
    }
  }

  /*for (int i=0;i<vec_codes.size();i++){
    cout<<vec_codes[i]<<endl;
  }*/

  if (vec_codes.size() == 0){
    cout<<"No direct journeys available"<<endl;
    return;
  }

  listOfObjects<TrainInfoPerStation*> * print_info = nullptr;
  listOfObjects<TrainInfoPerStation*> * trav = print_info;
  listOfObjects<TrainInfoPerStation*> * prnt = nullptr;
  listOfObjects<TrainInfoPerStation *> *stnInfo = stationInfo[src_index];
  while(stnInfo != nullptr){
    int exp_jcode = stnInfo->object->journeyCode;
    if (find(vec_codes.begin(),vec_codes.end(),exp_jcode) != vec_codes.end()){
      print_info = new listOfObjects<TrainInfoPerStation*>(stnInfo->object);
      print_info->next = trav;
      trav = print_info;
    }
    stnInfo = stnInfo->next;
  }
  printStationInfo(print_info);

  return;
}
