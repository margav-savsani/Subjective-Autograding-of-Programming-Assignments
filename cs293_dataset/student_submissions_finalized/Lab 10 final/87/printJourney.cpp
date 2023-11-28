#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  Entry<int> *srcstation = stnNameToIndex.get(srcStnName);
  Entry<int> *deststation = stnNameToIndex.get(destStnName);

  bool bool_1 = ((srcstation == nullptr) || (srcstation->value == -1));
  bool bool_2 = ((deststation == nullptr) || (deststation->value == -1));
  if (bool_1){
    cout << "Couldn't find " << srcStnName << "in data" << endl;
    return;
  }
  if (bool_2){
    cout << "Couldn't find " << destStnName << "in data" << endl;
    return;
  }

  listOfObjects<StationConnectionInfo *> *toS = adjacency[srcstation->value].toStations;
  listOfObjects<TrainInfoPerStation *> *jrnyList0 = toS->object->trains;
  listOfObjects<TrainInfoPerStation *> *jrnyList = new  listOfObjects<TrainInfoPerStation *> ((stationInfo[(toS->object)->adjacentStnIndex])->object);
  listOfObjects<TrainInfoPerStation *> *lip = new listOfObjects<TrainInfoPerStation *>(stationInfo[srcstation->value]->object); 
  


  //listOfObjects<StationConnectionInfo *> *curr = toS;
  // while (curr != nullptr){
    bool found = false;
    for (listOfObjects<StationConnectionInfo *> *curr = toS; (curr != nullptr && found == false); curr = curr->next){
      listOfObjects<TrainInfoPerStation *> *prnstn = (curr->object)->trains;
      printStationInfo(prnstn);
      // listOfObjects<TrainInfoPerStation *> *fistn = adjacency[curr->object->adjacentStnIndex].toStations;
    }
      //printStationInfo(curr->object->trains);
      // curr = curr->next;
  //}
  
  // Entry<int> *station = stnNameToIndex.get("BHILAI JUNCTION");
  // cout << BLUE << station->value << RESET << endl;
  // printStationInfo(stationInfo[station->value]);
  // station = stnNameToIndex.get("HOWRAH JUNCTION");
  // cout << BLUE << station->value << RESET << endl;
  // station = stnNameToIndex.get("ROURKELA JUNCTION");
  // cout << BLUE << station->value << RESET << endl;


  // insert your code here
  
  //cout << "No journey is possible" << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

// bool Planner::printJrny(int srcStnkey, int destStnkey, listOfObjects<TrainInfoPerStation *> tbr, bool fo){
//   tbr = tbr->next;
//   tbr = stationInfo[srcStnkey];
//   if (srcStnkey == destStnkey){ return true;  }
//   else {
//     listOfObjects<StationConnectionInfo *> *toStns = adjacency[srcStnkey].toStations;
//     for (listOfObjects<StationConnectionInfo *> *cur = toS; (cur != nullptr && fo == false); cur = cur->next){
//       bool f = printJrny(curr->object->adjacentStnIndex, destStnkey, tbr, );
//     }
//   }
//   return false;
// }

#endif
