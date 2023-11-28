#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

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
  
  cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  listOfObjects<TrainInfoPerStation *> *listhead = nullptr;
  listOfObjects<TrainInfoPerStation *> *listtail = nullptr;

  //each entry to adjacency array is pointer to object of type StationAdjacencyList
  //each object of StationAdjacencyList has two lists "toStations" and "fromStations"
  //each of these is a list of pointers to objects of class StationConnectionInfo
  //Each object of class StationConnectionInfo has a station index (recall all station 
  //names are mapped to unique indices through the dictionary stnNameToIndex in the 
  //class Planner (see planner.h), and a list of pointers to TrainInfoPerStation

  int srcindex = stnNameToIndex.get(srcStnName)->value;
  int destindex = stnNameToIndex.get(destStnName)->value;

  listOfObjects<TrainInfoPerStation *> *queuehead = nullptr;
  listOfObjects<TrainInfoPerStation *> *queuetail = nullptr;

  listOfObjects<int> *stncodeshead = nullptr;
  listOfObjects<int> *stncodestail = nullptr;

  static int alpha = 1;
  static int beta = 1;
  static int gamma = 1;
  static int check = 1;
 

  int fromjourneycodes[512];
  int count = 0;

  listOfObjects<StationConnectionInfo *> *y = adjacency[destindex].fromStations;            //storing all journeycodes of trains reaching destination in an array
  while(y != nullptr){
    listOfObjects<TrainInfoPerStation *> *trs = y->object->trains;
    while(trs != nullptr){
      fromjourneycodes[count] = trs->object->journeyCode;
      count++;
      trs = trs->next;
    }
    y = y->next;
  }

  listOfObjects<StationConnectionInfo *> *x = adjacency[srcindex].toStations;                //contains(fromjourneycodes, temp->object->journeyCode)

  while(x != nullptr){
    listOfObjects<TrainInfoPerStation *> *temp = x->object->trains;
    while(temp != nullptr){
      if(std::find(fromjourneycodes, fromjourneycodes + 512, temp->object->journeyCode) != fromjourneycodes + 512){                            //as if array doesnt contain the journey code then the train wont reach dest at all so we don't include it in the queue
        if(alpha==1){
          queuehead = new listOfObjects<TrainInfoPerStation *>(temp->object);
          //queuehead->object = temp->object;
          stncodeshead = new listOfObjects<int>(x->object->adjacentStnIndex);
          queuetail = queuehead;
          stncodestail = stncodeshead;
          alpha++;
        }
        else{
          //queuetail->object = temp->object;
          queuetail->next = new listOfObjects<TrainInfoPerStation *>(temp->object);
          stncodestail->next = new listOfObjects<int>(x->object->adjacentStnIndex);
          //stncodestail->object = x->object->adjacentStnIndex;
          queuetail = queuetail->next;
          stncodestail = stncodestail->next;
        }
      }
      temp = temp->next;
    }
    x = x->next;
  }

  while(queuehead != nullptr){
    //queuehead->object is the pointer to train
    if(stncodeshead->object == destindex){
      bool done = false;
      // int var = queuehead->object->journeyCode;
      // listOfObjects<StationConnectionInfo *> *fromsource = adjacency[srcindex].fromStations;            //storing all journeycodes of trains reaching destination in an array
      //     while(fromsource != nullptr && check == 1){
      //       listOfObjects<TrainInfoPerStation *> *trs = fromsource->object->trains;
      //       while(trs != nullptr){
      //         if(trs->object->journeyCode == var){
      //           if(beta == 1){
      //           listhead = new listOfObjects<TrainInfoPerStation *>(trs->object);
      //           listtail = listhead;
      //           queuehead = queuehead->next;
      //           stncodeshead = stncodeshead->next;
      //           check++;
      //           beta++;
      //           break;;
      //           }
      //           else{
      //             listtail->next = new listOfObjects<TrainInfoPerStation *>(trs->object);
      //             listtail = listtail->next;
      //             queuehead = queuehead->next;
      //             stncodeshead = stncodeshead->next;
      //             check++;
      //             break;
      //           }
      //         }
      //         trs = trs->next;
      //       }
      //       fromsource = fromsource->next;
      //   }
      int var = queuehead->object->journeyCode;
      listOfObjects<TrainInfoPerStation *> *trs = stationInfo[srcindex];
      while(trs != nullptr){
        if(trs->object->journeyCode == var){
            if(beta == 1){
              listhead = new listOfObjects<TrainInfoPerStation *>(trs->object);
              listtail = listhead;
              queuehead = queuehead->next;
              stncodeshead = stncodeshead->next;
              beta++;
              done = true;
              break;
            }
            else{
                listtail->next = new listOfObjects<TrainInfoPerStation *>(trs->object);
                listtail = listtail->next;
                queuehead = queuehead->next;
                stncodeshead = stncodeshead->next;
                done = true;
                break;

            }
        }
      }
      if(done) continue;


    }

    if(adjacency[stncodeshead->object].toStations == nullptr){
      queuehead = queuehead->next;
      stncodeshead = stncodeshead->next;
      continue;
    }

    listOfObjects<StationConnectionInfo *> *z = adjacency[stncodeshead->object].toStations;

    while(z != nullptr){
      listOfObjects<TrainInfoPerStation *> *temp = z->object->trains;
      while(temp != nullptr){
        //queuetail->object = temp->object;
        queuetail->next = new listOfObjects<TrainInfoPerStation *>(temp->object);
        queuetail = queuetail->next;
        //stncodestail->object = z->object->adjacentStnIndex;
        stncodestail->next = new listOfObjects<int>(z->object->adjacentStnIndex);
        stncodestail = stncodestail->next;
        temp = temp->next;
      }
      z = z->next;
    }
    
    queuehead = queuehead->next;
    stncodeshead = stncodeshead->next;

  }
  if(listhead == nullptr){
    cout<<"NO Direct Journeys Available"<<endl;
  }
  else{
    printStationInfo(listhead);
  }
  alpha = 1;
  beta = 1;
  gamma = 1;
  
  return;
}

#endif
