#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
//The below function returns an array which stores the values of 1's and 0's, here 1 represents that the train will travel on that given day of the week.
int* find(TrainInfoPerStation*arb){
  int* arr;
  arr=new int[7];
  for(int j=0;j<7;j++){
    if(arb->daysOfWeek[j]==true){
      arr[j]=1;
    }
    else{
      arr[j]=0;
    }
  }
  return arr;
}
//This function returns whether it is possible to reach the destination from the given station address.
bool possible(listOfObjects<StationConnectionInfo*>* stop,int w,StationAdjacencyList* adjacency){
  listOfObjects<StationConnectionInfo*>*stop1=stop;
  while(stop1!=nullptr){
    if(stop1->object->adjacentStnIndex==w){
      return true;
    }
    else{
      if(possible(adjacency[stop1->object->adjacentStnIndex].toStations,w,adjacency)){
        return true;
      }//This returns true here if there is a chance to reach the destination from here through some possible way.
      else{
        stop1=stop1->next;
      }
    }
  }
  return false;
}
//This function is used to check whether the given two trains have a time gap of travel below the given time limit or above it.
bool valid1(TrainInfoPerStation*a,TrainInfoPerStation*b,listOfObjects<TrainInfoPerStation*>* ls,int maxt){
  int* aroa=find(a);
  int* arob=find(b);
  int dep1=a->depTime;
  int tcode1=a->journeyCode;
  int dep2=b->depTime;
  listOfObjects<TrainInfoPerStation*>* ls1=ls;
  while(ls1->object->journeyCode!=tcode1){
    ls1=ls1->next;
  }//this loop helps to find the train's address whose journey code matches with the 1st trains journey code in the station info of given station.
  int arr2=ls1->object->arrTime;
  int y=0;
     while(aroa[y]!=1){
       y=y+1;
     }//This loop finds the 1st day of the week on which the train will be travelling between the stations.
   if(arr2>dep1){
     int j=0;
     for( j=0;j<7;j++){
       if(arob[j]==1){
         if(y==j || y+1==j){
           break;
         }
       }
     }//This loop helps to identify the day on which the first train reaches the 2nd station.
     if(y==j){
       if(dep2>arr2){
         if(dep2-arr2<(100*maxt)){
           return true;
         }
         else{
           return false;
         }
       }//This condition gives the info about the possibility of changing the trains at the given station.
       else{
         return false;
       }
     }
     else{
       if(dep2>arr2){
         if(2400-(dep2-arr2)<=(100*maxt)){
           return true;
         }
         else{
           return false;
         }
       }//This condition helps to check whether the time constraint is satisfied or not at the given station.
       else{
         if(2400-(arr2-dep2)<=(100*maxt)){
           return true;
         }
         else{
           return false;
         }
       }
     }
   }//This branch is implemented when the first train reaches on the same day which it started to the given station.
   else{
     int z=y+1;
     int j=0;
     for( j=0;j<7;j++){
       if(arob[j]==1){
         if(z==j || z+1==j){
           break;
         }
       }
     }//This loop helps to identify the day on which the first train reaches the 2nd station.
     if(z==j){
       if(dep2>arr2){
         if(dep2-arr2<(100*maxt)){
           return true;
         }
         else{
           return false;
         }
       }//This condition gives the info about the possibility of changing the trains at the given station.
       else{
         return false;
       }
     }
     else{
       if(dep2>arr2){
         if(2400-(dep2-arr2)<=(100*maxt)){
           return true;
         }
         else{
           return false;
         }
       }//This condition checks whether the time constraint is satisfied by the given two trains or not.
       else{
         if(2400-(arr2-dep2)<=(100*maxt)){
           return true;
         }
         else{
           return false;
         }
       }
     }
   }//This branch is implemented when the first train reaches on the next day which it started to the given station.
}
//This function is used to print the journeys using the list of objects given as the parameter, this prints  pattern to seperate two different types of journeys between given stations.
void printStations(listOfObjects<TrainInfoPerStation *> *stnInfoList,Dictionary<int> stnNameToIndex)
{
	cout <<endl;
  listOfObjects<TrainInfoPerStation *> *currList, *expandedList,*result;
  TrainInfoPerStation *currInfo;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  currList = stnInfoList;
  expandedList = nullptr;
  int listLength = 0;
  while (currList != nullptr) {
    currInfo = currList->object;
    if (currInfo != nullptr) {
      // Make as many copies of currInfo as the total count of days in the week
      // when this train runs from/to this station
      int jCode = currInfo->journeyCode;
      int stSeq = currInfo->stopSeq;
      int arrTime = currInfo->arrTime;
      int depTime = currInfo->depTime;
      for (int i=0; i < 7; i++) {
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
  while (currList != nullptr) {
    currInfo = currList->object;
    if (currInfo != nullptr) {
		if(currInfo->journeyCode==0)
		{
			cout <<"----------------------------DIFFERENT WAY TO DESTINATION-------------------------------"<<endl;//This pattern is used to seperate two different ways of journey between given stations.
			currList=currList->next;
			continue;
		}
		
      cout << GREEN << "Day(s): " << RESET;
      for (int i=0; i<7; i++) {
	if (currInfo->daysOfWeek[i]) cout << days[i] << " ";
      }
      cout << endl;
      cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
      cout << RED << "Arr: " << RESET;
      if (currInfo->arrTime == -1) {
	cout << "Starts";
      }
      else {
	cout << currInfo->arrTime;
      }
      cout << RED << " Dep: " << RESET;
      if (currInfo->depTime == -1) {
	cout << "Ends";
      }
      else {
	cout << currInfo->depTime;
      }
      cout << endl;
    }
    currList = currList->next;
  }
  cout << endl;
}
//This function recursively works and returns a list of trains that travel between given source and destination which also obeys the given time and number of stations constraints. This searches for the destiination and stores the trains list through which it is reached.
listOfObjects<TrainInfoPerStation*>* New(listOfObjects<StationConnectionInfo*>*tl,int check,int iod,int maxs,int maxt,int count,TrainInfoPerStation* temp,int mid,StationAdjacencyList*adjacency,listOfObjects<TrainInfoPerStation *>**stationInfo){
  listOfObjects<StationConnectionInfo*>*tl1=tl;
  listOfObjects<StationConnectionInfo*>*tl2=tl;
  TrainInfoPerStation* dum=new TrainInfoPerStation(0,0,0,0);//dummy element created at the start of the list of the stations
  listOfObjects<TrainInfoPerStation*>* store=new listOfObjects<TrainInfoPerStation*>(dum);//list of the trains which should be returned at the end of the function.
  listOfObjects<TrainInfoPerStation*>*store1=store;
  while(tl1!=nullptr){//This loop is executed if there are adjacent stations to the given source.
    listOfObjects<TrainInfoPerStation*>* list=tl1->object->trains;
    if(tl1->object->adjacentStnIndex!=iod){//This condition will be entered if the destination station is not in the immediate adjacent to the given source.
      if(possible(tl2,iod,adjacency)){
        while(list!=nullptr){
          int x=tl1->object->adjacentStnIndex;
          if(check==0){//This check=0 indicates that the list of stations we are checking are immediately adjacent to the original source station.
            count=0;
            listOfObjects<TrainInfoPerStation*>* arb=New(adjacency[tl1->object->adjacentStnIndex].toStations,list->object->journeyCode,iod,maxs,maxt,count,list->object,x,adjacency,stationInfo);
            if(arb!=nullptr){//Here arb will not be null if we reach destination in the called recursion.
              store1->next=new listOfObjects<TrainInfoPerStation*>(list->object);
              store1=store1->next;
              while(arb!=nullptr){
                while(arb->object->journeyCode!=0){//This loop is continues until a dummy element is reached in the arb list.
                  store1->next=new listOfObjects<TrainInfoPerStation*>(arb->object);
                  store1=store1->next;
                  arb=arb->next;
                  if(arb==nullptr){
                    break;
                  }
                }
                if(arb!=nullptr){//This condition will be true and implemented if the arb list is not null.
                  store1->next=new listOfObjects<TrainInfoPerStation*>(arb->object);
                  store1=store1->next;
                  arb=arb->next;
                }
                if(arb!=nullptr){//This condition will be true and implemented until the arb list is not null
                  store1->next=new listOfObjects<TrainInfoPerStation*>(list->object);
                  store1=store1->next;
                }
              }
              list=list->next;
            }
            else{
              list=list->next;
            }
          }
          else{//this is implemented if the check value is not equal to 0
            if(check!=list->object->journeyCode){
              if(valid1(temp,list->object,stationInfo[mid],maxt)){
                count=count+1;
                if(count<=maxs){
                  listOfObjects<TrainInfoPerStation*>*arb1=New(adjacency[tl1->object->adjacentStnIndex].toStations,list->object->journeyCode,iod,maxs,maxt,count,list->object,x,adjacency,stationInfo);
                  if(arb1!=nullptr){//Here arb will not be null if we reach destination in the called recursion.
                    store1->next=new listOfObjects<TrainInfoPerStation*>(list->object);
                    store1=store1->next;
                    while(arb1!=nullptr){
                      while(arb1->object->journeyCode!=0){//This loop is continues until a dummy element is reached in the arb list.
                        store1->next=new listOfObjects<TrainInfoPerStation*>(arb1->object);
                        store1=store1->next;
                        arb1=arb1->next;
                        if(arb1==nullptr){
                          break;
                        }
                      }
                      if(arb1!=nullptr){//This condition will be true and implemented until the arb list is not null.
                        store1->next=new listOfObjects<TrainInfoPerStation*>(arb1->object);
                        store1=store1->next;
                        arb1=arb1->next;
                      }
                      if(arb1!=nullptr){//This condition will be true and implemented until the arb list is not null
                        store1->next=new listOfObjects<TrainInfoPerStation*>(list->object);
                        store1=store1->next;
                      }
                    }
                    list=list->next;
                  }
                  else{
                    list=list->next;
                  }
                }
                count=count-1;
                if(count>=maxs){
                  list=list->next;
                }
              }
              else{
                list=list->next;
              }
            }//the above condition works if the previous train code and the train code we afre observing are not equal
            else{
              listOfObjects<TrainInfoPerStation*>* arb2=New(adjacency[tl1->object->adjacentStnIndex].toStations,list->object->journeyCode,iod,maxs,maxt,count,list->object,x,adjacency,stationInfo);
              if(arb2!=nullptr){//Here arb will not be null if we reach destination in the called recursion.
                store1->next=new listOfObjects<TrainInfoPerStation*>(list->object);
                store1=store1->next;
                while(arb2!=nullptr){
                  while(arb2->object->journeyCode!=0){//This loop is continues until a dummy element is reached in the arb list.
                    store1->next=new listOfObjects<TrainInfoPerStation*>(arb2->object);
                    store1=store1->next;
                    arb2=arb2->next;
                    if(arb2==nullptr){
                      break;
                    }
                  }
                  if(arb2!=nullptr){//This condition will be true and implemented until the arb list is not null.
                    store1->next=new listOfObjects<TrainInfoPerStation*>(arb2->object);
                    store1=store1->next;
                    arb2=arb2->next;
                  }
                  if(arb2!=nullptr){//This condition will be true and implemented until the arb list is not null.
                    store1->next=new listOfObjects<TrainInfoPerStation*>(list->object);
                    store1=store1->next;
                  }
                }
                list=list->next;
              }
              else{
                list=list->next;
              }
            }//the above condition works if the previous train code and the train code we afre observing are equal
          }
        }
        tl1=tl1->next;
      }
      else{
        tl1=tl1->next;
      }
    }
    else{//This condition is implemented if the destination is present in the immediate adjacent stations of the present source station.
      if(check==0){//This condition indicates that the destination is present in the adjacent stations of the origibal source station.
        count=0;
        while(list!=nullptr){
          store1->next=new listOfObjects<TrainInfoPerStation*>(list->object);
          store1=store1->next;
          store1->next=new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(0,0,0,0));
          store1=store1->next;
          list=list->next;
        }
        tl1=tl1->next;
      }
      else{
        while(list!=nullptr){
          if(check==list->object->journeyCode){
            store1->next=new listOfObjects<TrainInfoPerStation*>(list->object);
            store1=store1->next;
            store1->next=new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(0,0,0,0));
            store1=store1->next;
            list=list->next;
          }
          else{
            if(valid1(temp,list->object,stationInfo[mid],maxt)){
              count=count+1;
              if(count<=maxs){
                store1->next=new listOfObjects<TrainInfoPerStation*>(list->object);
                store1=store1->next;
                store1->next=new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(0,0,0,0));
                store1=store1->next;
                list=list->next;
              }
              count=count-1;
              if(count>=maxs){
                list=list->next;
              }
            }
            else{
              list=list->next;
            }
          }
        }
        tl1=tl1->next;
      }
    }
  }
  return store->next;
}
  
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  int si=stnNameToIndex.get(srcStnName)->value;
  int di=stnNameToIndex.get(destStnName)->value;
  listOfObjects<StationConnectionInfo*>* stl=adjacency[si].toStations;
  TrainInfoPerStation* dum=new TrainInfoPerStation(0,0,0,0);
  listOfObjects<TrainInfoPerStation*>* set=New(adjacency[si].toStations,0,di,maxStopOvers,maxTransitTime,0,dum,0,adjacency,stationInfo);
  printStations(set,stnNameToIndex);

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
