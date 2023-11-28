#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

listOfObjects<TrainInfoPerStation *> * recursion(int jc,string srcStnName,string destStnName,listOfObjects<TrainInfoPerStation *> *final,Dictionary<int> stnNameToIndex,StationAdjacencyList* adjacency){

      Entry<int> *p = stnNameToIndex.get(srcStnName);
      listOfObjects<StationConnectionInfo *> * m  = adjacency[p->value].toStations;
      
      if(srcStnName == destStnName){
        return final;
      }
      else{
        while(m != nullptr){
          listOfObjects<TrainInfoPerStation *> *trains = m->object->trains;
          string st = stnNameToIndex.getKeyAtIndex(m->object->adjacentStnIndex);
          while(trains != nullptr){
            if(trains->object->journeyCode == jc){
              listOfObjects<TrainInfoPerStation*> *p = final;
              while(p->next != nullptr){
                p = p->next;
              }
              listOfObjects<TrainInfoPerStation*> * q = new listOfObjects<TrainInfoPerStation*>(trains->object);
              p->next = q;
              q->prev = p;
              return recursion(jc,st,destStnName,final,stnNameToIndex,adjacency);
            }
            trains = trains->next;
          }
          m = m->next;
        }
        return nullptr;
      }
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  Entry<int> *p = stnNameToIndex.get(srcStnName);
  
  listOfObjects<TrainInfoPerStation *> *final = nullptr;
  
  int f = 1;
  listOfObjects<StationConnectionInfo *> * m1 = adjacency[p->value].toStations;
  while(m1 != nullptr){
      int adin = m1->object->adjacentStnIndex;
      string st = stnNameToIndex.getKeyAtIndex(adin);
      listOfObjects<TrainInfoPerStation *> *trains2 = m1->object->trains;
      while(trains2 != nullptr){
        final = new listOfObjects<TrainInfoPerStation*>(trains2->object);
        final = recursion(trains2->object->journeyCode,st,destStnName,final,stnNameToIndex,adjacency) ;
        if(final != nullptr){
          int b = 1;
          cout<<"Journey "<<f<<":"<<endl;
          while(final != nullptr){
            cout<< "Station "<< b <<" to"<<endl;
            listOfObjects<TrainInfoPerStation*>*p = new listOfObjects<TrainInfoPerStation *>(final->object);
            printStationInfo(p);
            final = final->next;
            cout<<"Station "<<b+1<<endl;
            cout<<""<<endl;
            b++;
          }
          f++;
        }
        trains2 = trains2->next;
      }
      m1 = m1->next;
  }
  
  if(f == 1){
    cout<< "No direct journeys available" <<endl;
  }
  
  return;
}


#endif
