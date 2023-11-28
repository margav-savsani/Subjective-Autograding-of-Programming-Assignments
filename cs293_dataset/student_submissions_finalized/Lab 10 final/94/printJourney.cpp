#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#include<cmath>
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// mycustom print function
void myprintStationInfo(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
	cout <<endl;
  listOfObjects<TrainInfoPerStation *> *currList, *expandedList,*result;
  TrainInfoPerStation *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  currList = stnInfoList; // takes a copy of given input
  expandedList = nullptr;
  int listLength = 0;
  while (currList != nullptr) { // iterating through the list
    currInfo = currList->object;
    if (currInfo != nullptr) {
      // Make as many copies of currInfo as the total count of days in the week
      // when this train runs from/to this station
      int jCode = currInfo->journeyCode;
      int stSeq = currInfo->stopSeq;
      int arrTime = currInfo->arrTime;
      int depTime = currInfo->depTime;
      for (int i=0; i < 7; i++) { // seperates the train into many trains by bool days of week:partitioning the list
		if (currInfo->daysOfWeek[i]||(i==6&& currInfo->journeyCode==0)) {
	  TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
	  newExpandedElement->setDayOfWeek(i);

	  listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);
	  if (expandedList == nullptr) {
	    expandedList = newExpandedListElement;
		result = expandedList;
	  }
	  else {
	    expandedList->next = newExpandedListElement;
	    expandedList = expandedList->next;
	  }
	  listLength++;
	}
	
      }
    }
    currList = currList->next;
  }
  
  currList = result;
  while (currList != nullptr) { // printtin the trains list
    currInfo = currList->object;
    if (currInfo != nullptr) {
		if(currInfo->journeyCode==0) // does not print the dummy element
		{
			cout <<"------------------NEXT POSSIBLE WAY-----------------------------------------"<<endl;
			currList=currList->next;
			continue;
		}
		
      cout << GREEN << "Day(s): " << RESET;
      for (int i=0; i<7; i++) { // prints the train info
	if (currInfo->daysOfWeek[i]) cout << days[i] << " ";
      }
      cout << endl;
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      if (currInfo->arrTime == -1) {
	cout << "Starts";
      }
      else {
	cout << currInfo->arrTime; // arrival time
      }
      cout << RED << " Dep: " << RESET;
      if (currInfo->depTime == -1) {
	cout << "Ends";
      }
      else {
	cout << currInfo->depTime; // departure time
      }
      cout << endl;
    }
    currList = currList->next;
  }
  cout << endl;
}

//appends the second linked list to first list
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

// checks whether there is possible journey if there is train change
bool checktime(TrainInfoPerStation*a,TrainInfoPerStation*b,int time,listOfObjects<StationConnectionInfo*>*fr){
  bool changeday=false; // checks whether the first train has changed day from A to B
  int jc=a->journeyCode;
  int arrB=0; // arrival time of train1 at B
  int deptB=0;// depature time of train1 at B
  listOfObjects<StationConnectionInfo*>*temp=fr; // from stations to B
  bool done=false;
  // checking the journey code of train1 in fromstations at B
  while(fr!=NULL && !done){
    listOfObjects<TrainInfoPerStation*>*t=fr->object->trains;
    while(t!=NULL){
      if(t->object->journeyCode==jc){
        arrB=t->object->arrTime;
        deptB=t->object->depTime;
        done=true;
        break;
      }
      t=t->next;
    }
    fr=fr->next;
  }
  if(arrB<a->depTime) changeday=true; // assigning changeday to its value

  for(int i=0;i<7;i++){
    if(a->daysOfWeek[i]){
      int start=i+changeday;
      if(b->daysOfWeek[start]){ // if bool days of week is true in A
        if(b->depTime-arrB>=0 && b->depTime-arrB<=100*time) return true; // checking whther if there is possibility in same day
      }
      if(b->daysOfWeek[(start+1)%7]){
        if(2400-abs(arrB-b->arrTime)<=100*time) return true; // checking whther train is possible in next day or not
      }
    }
  }
  
  return false;

}

// recursive search with a special condtion for a train
listOfObjects<TrainInfoPerStation*>* searchwithTrain(TrainInfoPerStation*t ,int sindex,int dindex,StationAdjacencyList*adjacency,int c,int time,int stops){
  //list of adjacent trains for a given source
  TrainInfoPerStation *waste=new TrainInfoPerStation(-1,-1,-1,-1);
  listOfObjects<TrainInfoPerStation*>*direct=new listOfObjects<TrainInfoPerStation*>(waste);
  
  listOfObjects<StationConnectionInfo*>*to=adjacency[sindex].toStations;
  listOfObjects<StationConnectionInfo*>*fr=adjacency[sindex].fromStations;

  if(c>stops) return NULL;
  // searches in all adjacent nodes for a given source
  while(to!=NULL){
    listOfObjects<TrainInfoPerStation*>*lt=to->object->trains;
    while(lt!=NULL){
      if(lt->object->journeyCode==t->journeyCode){  // if it is same train 
        if(to->object->adjacentStnIndex==dindex){ // if it is destination
          // append a dummy elment indicating a complte journey
          TrainInfoPerStation *dum1=new TrainInfoPerStation(0,0,0,0);
          listOfObjects<TrainInfoPerStation*>*dum2=new listOfObjects<TrainInfoPerStation*>(dum1);
          append(direct,dum2); // appends if destination is found

        }
        else{ // if it is not destination
          if(searchwithTrain(t,to->object->adjacentStnIndex,dindex,adjacency,c,time,stops)!=NULL){
            // append list recursively
            append(direct,searchwithTrain(t,to->object->adjacentStnIndex,dindex,adjacency,c,time,stops));
          }
          
        }
      }
      else{ // checking time if train is changed
        if(checktime(t,lt->object,time,fr)){
          if(to->object->adjacentStnIndex==dindex){
            if(c<stops){ // checking no of stopovers
              listOfObjects<TrainInfoPerStation*>*add=new listOfObjects<TrainInfoPerStation*>(lt->object);
              append(direct,add);
              TrainInfoPerStation *dum1=new TrainInfoPerStation(0,0,0,0);
              listOfObjects<TrainInfoPerStation*>*dum2=new listOfObjects<TrainInfoPerStation*>(dum1);
              append(direct,dum2); // appends if destination is found
            }
          }
          else{
            int d=c+1;
            if(searchwithTrain(lt->object,to->object->adjacentStnIndex,dindex,adjacency,d,time,stops)!=NULL){
              listOfObjects<TrainInfoPerStation*>*add=new listOfObjects<TrainInfoPerStation*>(lt->object);
              append(direct,add); // adding train2
              append(direct,searchwithTrain(lt->object,to->object->adjacentStnIndex,dindex,adjacency,d,time,stops));// adding recursively
              listOfObjects<TrainInfoPerStation*>*dtemp=direct->next;
              // adding train2 recursively
              while(dtemp!=NULL){
                if(dtemp->object->journeyCode==0 && dtemp->next!=NULL){
                listOfObjects<TrainInfoPerStation*>*store=dtemp->next;
                dtemp->next=new listOfObjects<TrainInfoPerStation*>(lt->object);
                dtemp->next->next=store;
              }
              dtemp=dtemp->next;    
              }
            }
          }

        }
        
      }
      lt=lt->next;
      }
    to=to->next; 
    }

  return direct->next; 
  }




  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  int s=stnNameToIndex.get(srcStnName)->value; // source index
  int d=stnNameToIndex.get(destStnName)->value;// destination index
  
  // added a dummy element so that null pointer is not passed in functions
  TrainInfoPerStation *dummy=new TrainInfoPerStation(0,0,0,0);
  //the final list which is to be printed
  listOfObjects<TrainInfoPerStation*>*direct=new listOfObjects<TrainInfoPerStation*>(dummy);
  // stores the list of trains if destination is adjacent to source
  listOfObjects<TrainInfoPerStation*>*adj=new listOfObjects<TrainInfoPerStation*>(dummy);

  // adjacency list of source
  listOfObjects<StationConnectionInfo *> *to=adjacency[s].toStations;

  // searching without any condition(no train name)
  while(to!=NULL){
    int sindex=to->object->adjacentStnIndex;
    if(to->object->adjacentStnIndex==d){
      append(adj,to->object->trains);
    }
    else{ // iterates over every train and every adjacent node
      listOfObjects<TrainInfoPerStation*>*ite=to->object->trains;
      while(ite!=NULL){
        int c=0;
        if(searchwithTrain(ite->object,sindex,d,adjacency,c,maxTransitTime,maxStopOvers)!=NULL){
          
          
      
          TrainInfoPerStation*dum1=ite->object;
          listOfObjects<TrainInfoPerStation*>*dum2=new listOfObjects<TrainInfoPerStation*>(dum1);
          append(direct,dum2);
          append(direct,searchwithTrain(ite->object,sindex,d,adjacency,c,maxTransitTime,maxStopOvers));
          
          listOfObjects<TrainInfoPerStation*>*dtemp=direct->next;
          while(dtemp!=NULL){
            if(dtemp->object->journeyCode==0 && dtemp->next!=NULL){
              listOfObjects<TrainInfoPerStation*>*store=dtemp->next;
              dtemp->next=new listOfObjects<TrainInfoPerStation*>(dum1);
              dtemp->next->next=store;
            }
            dtemp=dtemp->next;    
          }

        }
        ite=ite->next;
      }
    }
    to=to->next;
  }
  // prints without the dummy elemenet
  if(direct->next==NULL && adj->next==NULL){cout<<"No Matches Found"<<endl;}
  if(direct->next!=NULL){
    // printing elements in list
    listOfObjects<TrainInfoPerStation*>*print=direct->next;
    myprintStationInfo(print);
  }
  if(adj->next!=NULL){
    
    myprintStationInfo(adj);
    cout <<"------------------NEXT POSSIBLE WAY-----------------------------------------"<<endl;
  }
  
  
  return;
}

#endif
