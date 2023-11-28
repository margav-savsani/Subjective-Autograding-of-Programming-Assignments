#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

//#include<vector>
using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  //cout << "This function is to be implemented by you." << endl;
  /*Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
  Entry<int> *dstStnIndexEntry = stnNameToIndex.get(dstStnName);
  int srcStnIndex=srcStnIndexEntry->value;
  int dstStnIndex=dstStnIndexEntry->value;
  while(adjacency[srcStnIndex]->toStations!=nullptr){
    
  }*/

  Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
  Entry<int> *destStnIndexEntry = stnNameToIndex.get(destStnName);
  int srcStnIndex=srcStnIndexEntry->value;
  int destStnIndex=destStnIndexEntry->value;

  //listOfObjects<TrainInfoPerStation *> *temp = new listOfObjects<TrainInfoPerStation *>(adjacency[srcStnIndex].toStations->object->trains->object);
  
    
    //for(adjacency[temp].toStations->object->trains->object->journeyCode)
  //}
  // Queue q[DICT_SIZE];
  // Queue path;
  //TrainInfoPerStation* src =  new TrainInfoPerStation(stationInfo[srcStnIndex]->object->journeyCode,stationInfo[srcStnIndex]->object->stopSeq,stationInfo[srcStnIndex]->object->arrTime,stationInfo[srcStnIndex]->object->stopSeq);

  listOfObjects<StationConnectionInfo *> *next= adjacency[srcStnIndex].toStations->next;
  listOfObjects<listOfObjects<TrainInfoPerStation *>*> *q;
  listOfObjects<TrainInfoPerStation *> *temp = new listOfObjects<TrainInfoPerStation*>(adjacency[srcStnIndex].toStations->object->trains->object);
  listOfObjects<TrainInfoPerStation *> *temp3 = temp;
  listOfObjects<TrainInfoPerStation *> *temp2 = adjacency[srcStnIndex].toStations->object->trains;
  
  //q = new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(path);

  while(temp2!=nullptr){
    temp3->next=temp2;
    temp2 = temp2->next;
    temp3 = temp3->next;
  }
  q = new listOfObjects<listOfObjects<TrainInfoPerStation *>*>(temp); //list of list of trains starting from source
  //cout<<q->object->object->journeyCode<<endl;
  int idx = next->object->adjacentStnIndex;
  listOfObjects<TrainInfoPerStation *> *temp4 = new listOfObjects<TrainInfoPerStation *>(next->object->trains->object);
  listOfObjects<TrainInfoPerStation *> *temp5 = temp4;
  //listOfObjects<TrainInfoPerStation *> *temp6 = temp4;
  while(next!=nullptr){
    temp5->next = next->object->trains;
    temp5 = temp5->next;
    next=next->next;
  }
  q->next->object = temp4;
  int index = adjacency[srcStnIndex].toStations->object->adjacentStnIndex;

  //I dont understand how to complete my code altough everything is in my mind i am not able to implment it because of like 10 different data structures
  

  //cout<<q->next->object->object->journeyCode<<endl;
  // cout<<src->journeyCode<<endl;
  // cout<<path->object->journeyCode<<endl;
  // cout<<q->object->object->journeyCode<<endl;
  listOfObjects<TrainInfoPerStation *> *ans ;

  
  // listOfObjects<listOfObjects<StationConnectionInfo *> *>*q= new listOfObjects<listOfObjects<StationConnectionInfo *> *>(adjacency[srcStnIndex].toStations);
  // listOfObjects<StationConnectionInfo *> *path;
  // StationConnectionInfo * src = adjacency[srcStnIndex]->object;
  // while(q->object!=nullptr){
  //   cout<<1<<endl;
  //   path = q->object;
  //   listOfObjects<TrainInfoPerStation *> *del = q->object;
  //   q->object = q->object->next;
  //   del =nullptr;
  //   listOfObjects<TrainInfoPerStation *> *trav = path;
  //   while(trav->next!=nullptr){
  //     trav = trav->next;
  //   }
  //   cout<<trav->object->journeyCode << endl;
  // }
  return;
}

// class Queue{
//   public:
//     int front=0;
//     int rear=0;
//     int queue[DICT_SIZE];
    
//     void insert(int index){
//       queue[rear] = index;
//     }

//     void remove(int index){
//       if(front==rear){
//         return;
//       }
//       else{
//         for(int i = 0;i< rear - 1;i++) {
//           queue[i] = queue[i+1];
//         }
//         rear--;
//       }
//       return;
//     }

// };
  // int color[DICT_SIZE];
  // int d[DICT_SIZE];
  //for(int i=0 ; i<DICT_SIZE ; i++){
    // color[i] = 0;
    // d[i] = 999999;
    //q[i] = nullptr;
  //}

  // color[srcStnIndex] = 1;
  // d[srcStnIndex]=0;
  //vector<int> queue;
  //vector<int> trns;
  //queue.push_back(srcStnIndex);
  //while(queue.size() > 0){
    //int temp = queue.front();
   // queue.erase(queue.begin());