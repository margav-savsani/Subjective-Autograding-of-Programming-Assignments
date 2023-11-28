#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class info{
public:
    TrainInfoPerStation* arrivingTrain;
    TrainInfoPerStation* depaturingTrain;
    int arrTime;
    int deptTime;
    int stationIndex;
    int Nchildren;
    listOfObjects<info*>* next;
    info* prev;
    bool found;

    info(TrainInfoPerStation* aT, TrainInfoPerStation* depT, int aTime, int dTime, int si){
        arrivingTrain = aT;
        depaturingTrain = depT; 
        arrTime = aTime;
        deptTime = dTime;
        stationIndex = si;
        Nchildren=0;
        next = nullptr;
        prev=NULL;
        found = false;
    }
    info(){arrivingTrain=NULL; depaturingTrain=NULL; stationIndex=-1; found = false; arrTime = -1; deptTime = -1; Nchildren=0; next=NULL; prev=NULL;}
};


  listOfObjects<info*>* finalAnsList = NULL;
  listOfObjects<info*>* finalAnsListHEAD = NULL;


// void printStations(listOfObjects<TrainInfoPerStation *> *stnInfoList)
// {
//   listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
//   TrainInfoPerStation *currInfo;
//   string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

//   // Expanding information in stnInfoList to get a list of train info
//   // in which each element of the list refers to a single day of the
//   // week.  This is the list that has to be finally sorted using
//   // quicksort.

//   currList = stnInfoList;
//   expandedList = nullptr;
//   int listLength = 0;
//   while (currList != nullptr) {
//     currInfo = currList->object;
//     if (currInfo != nullptr) {
//       // Make as many copies of currInfo as the total count of days in the week
//       // when this train runs from/to this station
//       int jCode = currInfo->journeyCode;
//       int stSeq = currInfo->stopSeq;
//       int arrTime = currInfo->arrTime;
//       int depTime = currInfo->depTime;
    
//       for (int i=0; i < 7; i++) {
// 	if (currInfo->daysOfWeek[i]) {
// 	  TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
// 	  if (newExpandedElement == nullptr) {
// 	    continue;
// 	  }
// 	  newExpandedElement->setDayOfWeek(i);

// 	  listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *> (newExpandedElement);
// 	  if (newExpandedListElement == nullptr) {
// 	    continue;
// 	  }

// 	  if (expandedList == nullptr) {
// 	    expandedList = newExpandedListElement;
// 	  }
// 	  else {
// 	    newExpandedListElement->next = expandedList;
// 	    expandedList->prev = newExpandedListElement;
// 	    expandedList = newExpandedListElement;
// 	  }
// 	  listLength++;
// 	}
//       }
//     }
//     currList = currList->next;
//   }

// //   Quicksort(expandedList);
//   // QuicksortSimple(expandedList, 0, listLength-1);
  
//   currList = expandedList;
//   while (currList != nullptr) {
//     currInfo = currList->object;
//     if (currInfo != nullptr) {
//       cout << GREEN << "Day(s): " << RESET;
//       for (int i=0; i<7; i++) {
// 	if (currInfo->daysOfWeek[i]) cout << days[i] << " ";
//       }
//       cout << endl;
//       cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
//       cout << RED << "Arr: " << RESET;
//       if (currInfo->arrTime == -1) {
// 	cout << "Starts";
//       }
//       else {
// 	cout << currInfo->arrTime;
//       }
//       cout << RED << " Dep: " << RESET;
//       if (currInfo->depTime == -1) {
// 	cout << "Ends";
//       }
//       else {
// 	cout << currInfo->depTime;
//       }
//       cout << endl;
//     }
//     currList = currList->next;
//   }
//   cout << endl;
// }

void printStations(listOfObjects<info*>* list){
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    cout << "Journey:\n";
    while(list->next!=NULL){
        cout << "Station: " << list->object->stationIndex << endl;
        int Dday = list->object->deptTime%2400;
        int Dtime = list->object->deptTime - Dday*2400;
        int Aday = list->object->arrTime%2400;
        int Atime = list->object->arrTime - Dday*2400;
        if(list->object->depaturingTrain != NULL){
            cout << "Train Journey Code: " << list->object->depaturingTrain->journeyCode; 
            //cout << "  Arrives: " << days[Aday] << ", " << Atime << "    Departs: " << days[Dday] << ", " << Dtime <<  endl;
        }
        else{
            cout << "Destination Reached!\n "; 
            
        }
        cout<<endl;
        list = list->next;
    }
    cout << endl;
}

 void printThings(listOfObjects<info*>* ele){

      while(ele != NULL){
        listOfObjects<info*>* list = nullptr;
        listOfObjects<info*>* listHEAD = nullptr;
        info* var = ele->object;
        list = new listOfObjects<info*>(var);
        listHEAD = list;
        var = var->prev;
        while(var != NULL){
            listHEAD->prev = new listOfObjects<info*>(var);
            listHEAD->prev->next = listHEAD;
            listHEAD = listHEAD->prev;
            var = var->prev;
        }
        // listHEAD->prev = new listOfObjects<info*>(var);
        // listHEAD->prev->next = listHEAD;
        // listHEAD = listHEAD->prev;
      
        printStations(listHEAD);
        cout << endl;
        ele = ele->next;
        
        }
 }

//        info* currInfo = ele->object;
//         if (currInfo != nullptr) {
//             cout << GREEN << "Day(s): " << RESET;
//             for (int i=0; i<7; i++) {
// 	            if (currInfo->daysOfWeek[i]) cout << days[i] << " ";
//             }
//             cout << endl;
//             cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
//             cout << RED << "Arr: " << RESET;
//             if (currInfo->arrTime == -1) {
//                 cout << "Starts";
//             }
//             else {
//                 cout << currInfo->arrTime;
//             }
//             cout << RED << " Dep: " << RESET;
//             if (currInfo->depTime == -1) {
//                 cout << "Ends";
//             }
//             else {
//                 cout << currInfo->depTime;
//             }
//             cout << endl;
//         }
//     ele = ele->next;
//   }
//   cout << endl;
    



TrainInfoPerStation* returnSameDepatureTrain(int source_index, int con_stat_index, TrainInfoPerStation* a_train, StationAdjacencyList adjacency[]){
    listOfObjects<StationConnectionInfo*>* from_a_stat = adjacency[con_stat_index].fromStations;

    while(from_a_stat!=NULL){
        if(from_a_stat->object->adjacentStnIndex == source_index){
            listOfObjects<TrainInfoPerStation*>* con_train = from_a_stat->object->trains;
            while(con_train != NULL){
                if(con_train->object->journeyCode == a_train->journeyCode){
                    return con_train->object;
                }
                con_train = con_train->next;
            }
        }
        from_a_stat = from_a_stat->next;
    }
    return nullptr;
}



//  returns the wait time
int returnWaitTime(int dT, int dD, int aT, int aD){

    int ans = (dD-aD)*2400 + dT-aT;
    ans = ans/100;
    ans = ((ans%168)+168)%168;
    // cout << ans << endl;
    return ans;

//     int ftime = 0;
//     for(int i=0; i<7; i++){
//         if(from->daysOfWeek[i]){
//             ftime = 2400*i;
//             cout << "dhdjnj" << "       ";
//         }
//     }
//     cout << endl;
//     ftime += from->arrTime; 
//     int ttime = 0;
//     for(int i=0; i<7; i++){
//         if(To->daysOfWeek[i]){
//             ttime = 2400*i;
//             break; 
//         }
//     }
//     ttime += To->depTime;
//     return (ttime-ftime)/100;
}


// returns the increment values to be added for train when it reaches to station
int getIncrementofDayrequired(TrainInfoPerStation* fS, TrainInfoPerStation* tS){
    for(int ans=0; ans<7; ans++){
        bool done = true;
        for(int i=0; i<7; i++){
            // cout << fS->journeyCode << ":" << fS->daysOfWeek[i] << ", " << tS->journeyCode << ":" << tS->daysOfWeek[i] << ":" << ans << endl; 
            if(fS->daysOfWeek[i] != tS->daysOfWeek[(i+ans)%7]){
                done = false;
                break;
            }
        }
        // cout << endl;
        if(done){
            // cout << ans << endl;
            return ans;
        }
    }
    return 0; // not possible if inputs are right
}


// the main fuction
void doit(int si, int di, int remStops, int waitTime, TrainInfoPerStation* on_train, int day, StationAdjacencyList adjacency[], listOfObjects<TrainInfoPerStation *> *stationInfo[], info* newInfo){
    if(remStops == -1){
        return;
    }

    listOfObjects<StationConnectionInfo *>* connected_station = adjacency[si].toStations;
    while(connected_station != NULL){
        int con_stat_index = connected_station->object->adjacentStnIndex;
        if(con_stat_index == di){
        //****** got journies! *********
            listOfObjects<TrainInfoPerStation*>* a_train_btw_thesestats = connected_station->object->trains;
            while(a_train_btw_thesestats!=NULL){
           // going through a while loop
                TrainInfoPerStation* at_stat_train = a_train_btw_thesestats->object;//returnSameDepatureTrain(si, con_stat_index, a_train_btw_thesestats->object, adjacency);
                int dep_time_ofThisTrain = at_stat_train->depTime;
                int arriving_time_ofArrTrain = on_train->arrTime;
                TrainInfoPerStation* toFinalStationTrain = returnSameDepatureTrain(si, con_stat_index, a_train_btw_thesestats->object, adjacency);
                int incrementOfDay = getIncrementofDayrequired(at_stat_train, toFinalStationTrain);
                
                // if journy codes are equal
                if(at_stat_train->journeyCode == on_train->journeyCode && remStops >=0){
                    for(int i=0; i<7; i++){
                        if(at_stat_train->daysOfWeek[i]){
                            if(returnWaitTime(at_stat_train->depTime, i, arriving_time_ofArrTrain, day) <= waitTime){
                                
                                // ****** got journey! ****
                                info* new_info = new info(toFinalStationTrain, NULL, ((i+incrementOfDay)%7)*2400+toFinalStationTrain->arrTime, -1 ,con_stat_index);
                                new_info->prev = newInfo;
                                new_info->found = true;
                                // the storing DS which literally stores evverything
                                if(newInfo->next == NULL){
                                    newInfo->next = new listOfObjects<info*>(new_info);
                                    newInfo->Nchildren = 1;                            
                                }
                                else{
                                    listOfObjects<info*> *curr = newInfo->next;
                                    while(curr->next!=NULL){
                                        curr = curr->next;
                                    }
                                    curr->next = new listOfObjects<info*>(new_info);
                                    newInfo->Nchildren ++;
                                }
                                // cout << at_stat_train->journeyCode << ", day:" << i << ", " << dep_time_ofThisTrain << endl;
                                // to store the values at final list
                                if(finalAnsList==NULL){
                                    finalAnsList = new listOfObjects<info*>(new_info);
                                    finalAnsListHEAD = finalAnsList;
                                }
                                else{
                                    finalAnsList->next = new listOfObjects<info*>(new_info);
                                    finalAnsList = finalAnsList->next;
                                }                            
                            
                            }
                        } 
                    }
                }
                // if the train is different one
                else if(remStops > 0){
                    for(int i=0; i<7; i++){
                        if(at_stat_train->daysOfWeek[i]){
                            if(returnWaitTime(at_stat_train->depTime, i, arriving_time_ofArrTrain, day) <= waitTime){
                                // ****** got journey! ****
                                info* new_info = new info(toFinalStationTrain, NULL, ((i+incrementOfDay)%7)*2400+toFinalStationTrain->arrTime, -1 ,con_stat_index);
                                new_info->prev = newInfo;
                                new_info->found = true;
                                if(newInfo->next == NULL){
                                    newInfo->next = new listOfObjects<info*>(new_info);
                                    newInfo->Nchildren = 1;                            
                                }
                                else{
                                    listOfObjects<info*> *curr = newInfo->next;
                                    while(curr->next!=NULL){
                                        curr = curr->next;
                                    }
                                    curr->next = new listOfObjects<info*>(new_info);
                                    newInfo->Nchildren ++;
                                }
                                // cout << at_stat_train->journeyCode << ", day:" << i << ", " << dep_time_ofThisTrain << endl;
                                if(finalAnsList==NULL){
                                    finalAnsList = new listOfObjects<info*>(new_info);
                                    finalAnsListHEAD = finalAnsList;
                                }
                                else{
                                    finalAnsList->next = new listOfObjects<info*>(new_info);
                                    finalAnsList = finalAnsList->next;
                                }
                            }
                        }
                    }
                }
                a_train_btw_thesestats = a_train_btw_thesestats->next;
            }
        }

        // even after getting the journey, we need to find all possible ways, so, else is omitted
        listOfObjects<TrainInfoPerStation*>* a_train_btw_thesestats = connected_station->object->trains;
        while(a_train_btw_thesestats!=NULL){
            TrainInfoPerStation* at_stat_train = a_train_btw_thesestats->object;//returnSameDepatureTrain(si, con_stat_index, a_train_btw_thesestats->object, adjacency);
            int dep_time_ofThisTrain = at_stat_train->depTime;
            int arriving_time_ofArrTrain = on_train->arrTime;
            int incrementOfDay = getIncrementofDayrequired(at_stat_train, returnSameDepatureTrain(si, con_stat_index, a_train_btw_thesestats->object, adjacency));

             // this is if journy codes matches   
            if(at_stat_train->journeyCode == on_train->journeyCode){
                for(int i=0; i<7; i++){
                    if(at_stat_train->daysOfWeek[i])
                        if(returnWaitTime(at_stat_train->depTime, i, arriving_time_ofArrTrain, day) <= waitTime){
                            doit(con_stat_index, di, remStops, waitTime, a_train_btw_thesestats->object, i+incrementOfDay, adjacency, stationInfo, newInfo);
                        }
                }

            }
            else{ // if journy codes are not matching
                for(int i=0; i<7; i++){
                    if(at_stat_train->daysOfWeek[i]){
                        if(returnWaitTime(at_stat_train->depTime, i, arriving_time_ofArrTrain, day) <= waitTime){
                            info* new_info = new info(on_train, a_train_btw_thesestats->object, 2400*day+arriving_time_ofArrTrain, 2400*i+at_stat_train->depTime, con_stat_index);
                            new_info->prev = newInfo;
                            if(newInfo->next == NULL){
                                newInfo->next = new listOfObjects<info*>(new_info);
                                newInfo->Nchildren = 1;                            
                            }
                            else{
                                listOfObjects<info*> *curr = newInfo->next;
                                while(curr->next!=NULL){
                                    curr = curr->next;
                                }
                                curr->next = new listOfObjects<info*>(new_info);
                                newInfo->Nchildren ++;
                            }
                            doit(con_stat_index, di, remStops-1, waitTime,  a_train_btw_thesestats->object, i+incrementOfDay, adjacency, stationInfo, new_info);
                        }
                    }
                }
            }
            a_train_btw_thesestats = a_train_btw_thesestats->next;
        }

        connected_station = connected_station->next;
    }
}



void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  info* thisprob = new info();

  
  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  int source_index = stnNameToIndex.hashValue(srcStnName);
  while(true)
  { // finding index by probing
    if(srcStnName == stnNameToIndex.getKeyAtIndex(source_index))
      break;
    source_index = (source_index+1)%DICT_SIZE;
  }
  
  int dest_index = stnNameToIndex.hashValue(destStnName);
  while(true)
  { // finding index by probing
    if(destStnName == stnNameToIndex.getKeyAtIndex(dest_index))
      break;
    dest_index = (dest_index+1)%DICT_SIZE;
  }

  if(source_index == dest_index){
    cout<<"No journies" << endl;
    return;
  }

// doing base case here
  listOfObjects<StationConnectionInfo *>* connected_station = adjacency[source_index].toStations;
  while(connected_station != NULL){
    int con_stat_index = connected_station->object->adjacentStnIndex;
    if(con_stat_index == dest_index){
        //**********got the journey!***************
        listOfObjects<TrainInfoPerStation*>* a_train_btw_thesestats = connected_station->object->trains;
        while(a_train_btw_thesestats!=NULL){
            TrainInfoPerStation* returnedTrain = returnSameDepatureTrain(source_index, connected_station->object->adjacentStnIndex, a_train_btw_thesestats->object, adjacency);
            int incrReq = getIncrementofDayrequired(a_train_btw_thesestats->object, returnedTrain); 
            for(int i=0; i<7; i++){
                if(returnedTrain->daysOfWeek[i]){
                    info* new_info = new info(NULL, a_train_btw_thesestats->object, -1, (((i-incrReq)%7+(i-incrReq))%7)*2400+a_train_btw_thesestats->object->depTime, source_index);
                    thisprob->next = new listOfObjects<info*>(new_info);
                    new_info->prev = thisprob;
                    thisprob->Nchildren = 1;
                    new_info->found =true;
                    // cout << a_train_btw_thesestats->object->journeyCode << ", day:"<< i << ", " << returnedTrain->arrTime << endl;
                    
                    if(finalAnsList==NULL){
                        finalAnsList = new listOfObjects<info*>(new_info);
                        finalAnsListHEAD = finalAnsList;
                    }
                    else{
                        finalAnsList->next = new listOfObjects<info*>(new_info);
                        finalAnsList = finalAnsList->next;
                    }
                }
            }
            a_train_btw_thesestats = a_train_btw_thesestats->next;
        }    
    }
    // even after getting the journey, we need to find all possible ways, so, else is omitted
    listOfObjects<TrainInfoPerStation*>* a_train_btw_thesestats = connected_station->object->trains;
    while(a_train_btw_thesestats!=NULL){
        TrainInfoPerStation* returnedTrain = returnSameDepatureTrain(source_index, connected_station->object->adjacentStnIndex, a_train_btw_thesestats->object, adjacency);
        int incrReq = getIncrementofDayrequired(a_train_btw_thesestats->object, returnedTrain); 
        for(int i=0; i<7; i++){
            // for all days
            if(returnedTrain->daysOfWeek[i]){
                info* new_info = new info(NULL, a_train_btw_thesestats->object, -1, (((i-incrReq)%7+(i-incrReq))%7)*2400+a_train_btw_thesestats->object->depTime, source_index);
                thisprob->next = new listOfObjects<info*>(new_info);
                new_info->prev = thisprob;
                thisprob->Nchildren = 1;
                doit(con_stat_index, dest_index, maxStopOvers, maxTransitTime,  returnedTrain, i, adjacency, stationInfo, new_info);
            }
        }
        a_train_btw_thesestats = a_train_btw_thesestats->next;
    }
    connected_station = connected_station->next;
  }

    printThings(finalAnsListHEAD);
}

#endif

// The code is  incomplete and better code could be done if given some more time