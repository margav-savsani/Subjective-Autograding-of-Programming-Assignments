#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct Train{
  TrainInfoPerStation *A;
  int jCode;
  int aTm;
  int dTm;
  string Start;
  string Stop;

  Train(TrainInfoPerStation *B, string str, string stp){
    A = B;
    jCode = B->journeyCode;
    int i;
    for(i=0; i<7; i++){
      if(B->daysOfWeek[i]){
        break;
      }
    }
    //now i contains the index of day on which the train leaves
    aTm = (2400*i) + B->arrTime;
    dTm = (2400*i) + B->depTime;
    Start = str;
    Stop = stp;
  }
};

struct Journey{
  listOfObjects<Train *> *trains;
  Train *last;
  int stops;
  int transit; //transit time

  Journey(){
    trains = nullptr;
    last = nullptr;
    stops = 0;
    transit = 0;
  }

  void insert(Train* A){
    if(trains == nullptr){
      trains = new listOfObjects<Train*>(A);
      last = A;
      // cout << "If\n";
    }
    else{
      listOfObjects<Train *> *curr = trains;
      while(curr->next != nullptr){
        curr = curr->next;
      }
      if(curr->object->jCode != A->jCode){
        transit = A->dTm-curr->object->aTm;
        if(transit >= 0){
          curr->next = new listOfObjects<Train*>(A);
          last = A;
          stops++;
        }
        // curr->next = new listOfObjects<Train*>(A);
        // last = A;
      }
      else{
        curr->object->aTm = A->aTm;
        curr->object->dTm = A->dTm;
        curr->object->Stop = A->Stop;
        last = curr->object;
      }
      // cout << "Else\n";
    }
  }

};

void printAllJourneys(listOfObjects<Journey *> *toprint, int maxTransitTime, string destStn){
  if(toprint == nullptr){
    cout << "No train available\n";
    return;
  }
  while(toprint!=nullptr){
    // cout << "Hey\n";
    Journey *currJourney = toprint->object;
    if(currJourney->last->Stop == destStn && currJourney->transit < maxTransitTime){
      listOfObjects<Train *> *trains = currJourney->trains;
      Train *first = trains->object;
      // cout << "Jcode: " << first->jCode << "\n";
      for(int i=0; i<7; i++){
        if(first->A->daysOfWeek[i]){
          if(i==0) cout << "On" << GREEN << " Sunday:\n" << RESET;
          if(i==1) cout << "On" << GREEN << " Monday:\n" << RESET;
          if(i==2) cout << "On" << GREEN << " Tuesday:\n" << RESET;
          if(i==3) cout << "On" << GREEN << " Wednessday:\n" << RESET;
          if(i==4) cout << "On" << GREEN << " Thursday:\n" << RESET;
          if(i==5) cout << "On" << GREEN << " Friday:\n" << RESET;
          if(i==6) cout << "On" << GREEN << " Saturday:\n" << RESET;
          cout<< RED << "Train Code " << RESET <<first->jCode<< RED << ": Starts at " << RESET <<first->Start<< RED << " at " << RESET <<first->aTm%2400<< RED <<  " reaches " << RESET <<first->Stop<< RED << " at " << RESET <<first->dTm%2400<<"\n";
          while(trains->next!=nullptr){
            trains=trains->next;
            cout<<"Change to-"<<"\n";
            Train *first = trains->object;
            cout<< RED << "Train Code " << RESET <<first->jCode<< RED << ": Starts at " << RESET <<first->Start<< RED << " at " << RESET <<first->aTm%2400<< RED <<  " reaches " << RESET <<first->Stop<< RED << " at " << RESET <<first->dTm%2400<<"\n";
          }
          cout<<"Total transit time in the jouney is "<<currJourney->transit<<"\n";
        }
      }
    }
    toprint=toprint->next;
  }
  return;
}


void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  int srcStn = stnNameToIndex.get(srcStnName)->value;
  int destStn = stnNameToIndex.get(destStnName)->value;
  listOfObjects<StationConnectionInfo* > *toStations = adjacency[srcStn].toStations;
  static listOfObjects<Journey*>* alltrains = nullptr;
  
  if(srcStn == destStn){
    printAllJourneys(alltrains, maxTransitTime, destStnName);
  }
  else{
    while(toStations != nullptr){
      int currStn = toStations->object->adjacentStnIndex;
      listOfObjects<Journey*>* currJourney = alltrains;
      if(alltrains == nullptr){
        Train* A = new Train(toStations->object->trains->object, srcStnName, stnNameToIndex.getKeyAtIndex(currStn));
        Journey* J = new Journey();
        J->insert(A);
        alltrains = new listOfObjects<Journey*>(J);
      }
      while(currJourney != nullptr){
        Train* A = new Train(toStations->object->trains->object, srcStnName, stnNameToIndex.getKeyAtIndex(currStn));
        currJourney->object->insert(A);
        currJourney = currJourney->next;
      }
      
      printPlanJourneys(stnNameToIndex.getKeyAtIndex(currStn), destStnName, maxStopOvers, maxTransitTime);
      
      toStations = toStations->next;
    }
  }

  // cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
