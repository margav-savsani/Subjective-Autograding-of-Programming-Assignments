#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


void add(listOfObjects<int> * ptr,int k){
  //cout << "1" << endl;
  if(ptr->object==-1){
    //cout << "2" << endl;
    //cout <<"lal" << endl;
    ptr->object = k;
    return;
  }
  while(ptr->next!=NULL){
    //cout << "3" << endl;
    ptr = ptr->next;
  }
  //cout << "4" << endl;
  ptr->next = new listOfObjects<int>(k);
  //cout << "5" << endl;
  return;
}

void addifpresent(listOfObjects<int> *ptr, int k, listOfObjects<int> *fromstart){
  bool b = false;
  if(ptr->object==-1){
     b = true;
  }
  while(ptr->next!=NULL){
    ptr = ptr->next;
  }
  while(fromstart!=NULL){
    if(fromstart->object==k){
      if(b){
        ptr->object = k;
      }
      else
        ptr->next = new listOfObjects<int>(k);
      break;
    }
    fromstart = fromstart->next;
  }
  return;
}

void removehead(listOfObjects<int>* &quee){
  quee = quee->next;
}

void doBFS(int start, listOfObjects<int> * JCfromsource[DICT_SIZE], StationAdjacencyList adjacency[512]){
  listOfObjects<int> *quee = new listOfObjects<int>(start);
  while(quee!=NULL){
    int ind = quee->object;
    StationAdjacencyList curradjList = adjacency[ind];
    if(curradjList.toStations==NULL || JCfromsource[ind]->object==-1 && ind!=start){
      return;
    }
    if(JCfromsource[ind]->object==-1){
      listOfObjects<StationConnectionInfo *> *adjstn = adjacency[ind].toStations;
      while(adjstn!=NULL){
        int adjstnInd = adjstn->object->adjacentStnIndex;
        listOfObjects<TrainInfoPerStation *> *adjstnCnnList = adjstn->object->trains;
        while(adjstnCnnList!=NULL){
          add(JCfromsource[adjstnInd], adjstnCnnList->object->journeyCode);
          adjstnCnnList = adjstnCnnList->next;
        }
        add(quee,adjstnInd);
        adjstn = adjstn->next;
      }
    }
    else{
      listOfObjects<StationConnectionInfo *> *adjstn = adjacency[ind].toStations;
      while(adjstn!=NULL){
        int adjstnInd = adjstn->object->adjacentStnIndex;
        listOfObjects<TrainInfoPerStation *> *adjstnCnnList = adjstn->object->trains;
        while(adjstnCnnList!=NULL){
          addifpresent(JCfromsource[adjstnInd], adjstnCnnList->object->journeyCode, JCfromsource[ind]);
          adjstnCnnList = adjstnCnnList->next;
        }
        add(quee,adjstnInd);
        adjstn = adjstn->next;
      }
    }
    removehead(quee);
  }  

}

  // listOfObjects<StationConnectionInfo *> *adjstn2= adjacency[start].toStations;
  //   while(adjstn2!=NULL){
  //     cout << "up" << endl;
  //     int adjstnInd2 = adjstn2->object->adjacentStnIndex;
  //     doBFS(adjstnInd2, JCfromsource, adjacency);
  //     cout << "down" << endl;
  //     adjstn2 = adjstn2->next;
  //   }
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here

  int start = (stnNameToIndex.get(srcStnName))->value;
  int dest = (stnNameToIndex.get(destStnName))->value;

  listOfObjects<int> *JCfromsource[DICT_SIZE];
  for(int i=0; i<DICT_SIZE; i++){
    JCfromsource[i] = new listOfObjects<int>(-1);
  }
  doBFS(start,JCfromsource,adjacency);
  listOfObjects<int>* jcodes = JCfromsource[dest];
  if(jcodes->object==-1){
    cout << "No direct journeys available" << endl;
  }
  else{
    listOfObjects<TrainInfoPerStation *> *Info = stationInfo[start];
    listOfObjects<TrainInfoPerStation *> *js;
    TrainInfoPerStation t(0,0,0,0);
    js = new listOfObjects<TrainInfoPerStation *>(&t); 
    while(jcodes!=NULL){
      int code = jcodes->object;
      while(true){
        if(Info==NULL){
          break;
        }
        if(Info->object->journeyCode){
          js->next = Info;
          js = js->next;
        }
        Info = Info->next;
      }
      jcodes = jcodes->next;
    }
    printStationInfo(js);
  }

  return;
}