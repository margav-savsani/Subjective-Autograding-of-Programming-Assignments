#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
/*
listOfObjects<TrainInfoPerStation* > * BFS(int jrnycode,int sourceIndex,int destIndex,StationAdjacencyList*adjacency){
      listOfObjects<TrainInfoPerStation* > *route = new listOfObjects<TrainInfoPerStation* >(nullptr);
      int stnindex ;
      while(stnindex!=destIndex){
        stnindex = path(jrnycode,stnindex,adjacency,route);
        if(stnindex ==-1) return nullptr;
        }
      return route->next; 
}
*/
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{ int src_index ;
  int dest_index ;
 // int src_code ;
 // int dest_code ;
  int count = 0 ;   // count is the number of Journeys which goes from source station to destination station .
  src_index = stnNameToIndex.get(srcStnName)->value ;  // Index value of the source station in the dictionary .
  dest_index = stnNameToIndex.get(destStnName)->value ;  // Index value of the destination station in the dictionary .
  int *array ;
  array = new int[512] ;   // Integer array which stores the the Journey codes of the journeys between source station to destination station .
  
 listOfObjects<TrainInfoPerStation *> *required_list ;  // This list stores the pointers whose journeys are between source stn and destination stn .
 listOfObjects<StationConnectionInfo *> *d = adjacency[src_index].toStations ; // contains the list of journeys going from src station . 
 listOfObjects<StationConnectionInfo *> *e = adjacency[dest_index].fromStations ; // contains the list of journeys coming to dest station .
 /*
     I am comparing the list of journeys going from source station and the list of journeys coming to destination station ,
     if there is any journey code matching between them then i am storing all those journeys into another list named required_list
     and storing all those journey codes into the integer array .
 */
 
 while(d != nullptr){
 // cout<<"1"<<endl;
  listOfObjects<TrainInfoPerStation *> *d1 = d->object->trains ;
    while(e != nullptr){
       // cout<<"2"<<endl;
        //listOfObjects<TrainInfoPerStation *> *d1 = d->object->trains ;
        listOfObjects<TrainInfoPerStation *> *e1 = e->object->trains ;
        while(d1 != nullptr){
        //   cout<<"3"<<endl;
           // listOfObjects<TrainInfoPerStation *> *e1 = e->object->trains ;
            while(e1 != nullptr){
              //  cout<<"4"<<endl;
                if(d1->object->journeyCode == e1->object->journeyCode){
                   // cout<<"5"<<endl;
                    required_list->object = d1->object ;
                    required_list = required_list->prev ;
                    array[count] = d1->object->journeyCode ;
                    count = count + 1 ;
                }
                e1 = e1->next ;
            }
            d1 = d1->next ;
        }
        e = e->next ;
    }
    d = d->next ;
 }
  required_list = required_list->next ;

  if(count == 0){
    cout << "No direct journeys available from "<<srcStnName<<" to "<<destStnName << endl ;
  }
  else {
    /*cout<<"____LIST OF JOURNEYS____"<<endl;
    cout<<endl;
    cout<<endl;
    int i = 0 ;
    while(i<final_list.size()){
      cout<<"             __ROUTE__("<<i+1<<")"<<endl;
      listOfObjects<int> *dummy = final_list[i];
      while(dummy != nullptr){
        if(dummy->object==dest_i) {
          cout<<stnNameToIndex.getKeyAtIndex(dummy->object);
          break;
        }
        cout<<stnNameToIndex.getKeyAtIndex(dummy->object)<<" -> ";
        dummy = dummy->next;
      }
      cout<<endl;
      cout<<endl;
      cout<<"     ____AVAILABLE TRAIN FOR THIS ROUTE____"<<endl;
      cout << endl ;
      for(int j=0; j<list_jc[i].size(); j++){
        cout<<"JOURNEY CODE("<<j+1<<"): "<<list_jc[i][j]<<endl;
      }
      i++ ;
    }*/
    cout << "      ___LIST OF JOURNEYS___" << endl ;  // start of the print function .
    cout<<endl;
    cout<<"      The List of Journeys from "<<srcStnName<<" to "<<destStnName<<" are :-";
    cout<<endl;
    int i = 0 ;
    while(i<count){
      cout<<"  "<<i+1<<" )"<<" Journey with Journeycode : "<<array[count]<<endl ; // prints the journeys between the two journeys .
      i++ ;
    }
  }
  

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
