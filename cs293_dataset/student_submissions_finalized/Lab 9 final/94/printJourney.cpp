#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// appends the second linked to first linked list
void append(listOfObjects<TrainInfoPerStation *>*s,listOfObjects<TrainInfoPerStation*>*p){ 
  listOfObjects<TrainInfoPerStation *> *temp1=s;
  while(temp1->next!=NULL){ // iterating until we get last element
    temp1=temp1->next;
  }
  listOfObjects<TrainInfoPerStation*>*temp2=p;
  while(temp2!=NULL){ // adding until we get last eleement
    temp1->next=new listOfObjects<TrainInfoPerStation*>(temp2->object);
    temp1->next->prev=temp1; // equating prev
    temp2=temp2->next;
    temp1=temp1->next;
  }

}

// searches the given TrainInfoperstation* in linked list
bool searchinlist(TrainInfoPerStation* t, listOfObjects<TrainInfoPerStation*>*p){
  listOfObjects<TrainInfoPerStation*>*temp=p;
  while(temp!=NULL){ // searches until the last element in list
    if(temp->object->journeyCode==t->journeyCode) return true;
    temp=temp->next;
  }
  return false;
}

// recursive search with a special condtion for a train
void searchwithTrain(TrainInfoPerStation*t ,int sindex,int dindex,listOfObjects<TrainInfoPerStation*>*direct,StationAdjacencyList*adjacency){
  //list of adjacent trains for a given source
  listOfObjects<StationConnectionInfo*>*to=adjacency[sindex].toStations;
  
  // searches in all adjacent nodes for a given source
  while(to!=NULL){
    int s=to->object->adjacentStnIndex;
    // leaves the current node if the condition is not met(train code)
    if(!searchinlist(t,to->object->trains)) { to=to->next;continue;}

    // appends it into a list if it matches for destination
    if(to->object->adjacentStnIndex==dindex) {
      listOfObjects<TrainInfoPerStation*>*a=new listOfObjects<TrainInfoPerStation*>(t);
      append(direct,a);
    }
    // recursively searches in all its adjacent nodes
    else searchwithTrain(t,s,dindex,direct,adjacency);

    to=to->next;
  }

  return;
}


void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int s=stnNameToIndex.get(srcStnName)->value; // source index
  int d=stnNameToIndex.get(destStnName)->value;// destination index
  
  // added a dummy element so that null pointer is not passed in functions
  TrainInfoPerStation *dummy=new TrainInfoPerStation(0,0,0,0);
  //the final list which is to be printed
  listOfObjects<TrainInfoPerStation*>*direct=new listOfObjects<TrainInfoPerStation*>(dummy);

  // adjacency list of source
  listOfObjects<StationConnectionInfo *> *to=adjacency[s].toStations;

  // searching without any condition(no train name)
  while(to!=NULL){
    int sindex=to->object->adjacentStnIndex;
    if(to->object->adjacentStnIndex==d){
      append(direct,to->object->trains); // appends if destination is found
    }
    else{ // iterates over every train and every adjacent node
      listOfObjects<TrainInfoPerStation*>*ite=to->object->trains;
      while(ite!=NULL){
        searchwithTrain(ite->object,sindex,d,direct,adjacency);
        ite=ite->next;
      }
    }
    to=to->next;
  }
  // prints without the dummy elemenet
  if(direct->next==NULL){cout<<"No Direct Trains found"<<endl;}

  printStationInfo(direct->next);
  
  return;
}

#endif
