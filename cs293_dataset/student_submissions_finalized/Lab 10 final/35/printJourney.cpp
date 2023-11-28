#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <vector>
using namespace std;

// Train information per station with added public member StationName
class MyTrainInfoPerStationClass {
public:
  int journeyCode; // same as train number
  unsigned short stopSeq; // sequence of this station's stop in
                          // itinerary of train, i.e. 1st stop in journey
                          // or 2nd stop in journey or ...
  bool daysOfWeek[7]; // Days of week when this train travels
                      // to/from this station
  int arrTime;  // Arrival time at station; -1 if train starts from here
  int depTime;  // Departure time from station; -1 if train ends here
  string StationName;
  MyTrainInfoPerStationClass(int jCode, unsigned short stpSq, int aTm, int dTm, string StnNAME){
    journeyCode = jCode;
    stopSeq = stpSq;
    arrTime = aTm;
    depTime = dTm;
    for (int i = 0; i < 7; i++) { daysOfWeek[i] = false;}
    StationName = StnNAME;
  }
  ~MyTrainInfoPerStationClass() {;}
  void setDayOfWeek(int i) { if ((0 <= i) && (i < 7)) daysOfWeek[i] = true; }
  void resetDayOfWeek(int i) { if ((0 <= i) && (i < 7)) daysOfWeek[i] = false; }
    
};

//Train with different days in a week will be expanded into several trains s.t. each train has only 1 day
//Func from previous lab
listOfObjects<TrainInfoPerStation *> * ExpandTrain(listOfObjects<TrainInfoPerStation *> *Trn){
  listOfObjects<TrainInfoPerStation *> *temp = Trn;
  listOfObjects<TrainInfoPerStation *> *ExpandedTrain = nullptr;
  while(temp != nullptr){
    int JrnyCode = temp->object->journeyCode;
    int StSeq = temp->object->stopSeq;
    int ArrTime = temp->object->arrTime;
    int DepTime = temp->object->depTime;
    int i=0;
    while (i<7){
      if(temp->object->daysOfWeek[i]){
        TrainInfoPerStation * NewTrain = new TrainInfoPerStation(JrnyCode,StSeq,ArrTime,DepTime);
        NewTrain->setDayOfWeek(i);
        if(ExpandedTrain == nullptr){
          ExpandedTrain = new listOfObjects<TrainInfoPerStation *>(NewTrain);
        }
        else{
          //
          listOfObjects<TrainInfoPerStation *> *ExpandedTrainElement = new listOfObjects<TrainInfoPerStation *>(NewTrain);
          ExpandedTrainElement->next = ExpandedTrain;
          ExpandedTrain->prev = ExpandedTrainElement;
          ExpandedTrain = ExpandedTrainElement;
        }
      }
      i++;
    }
  temp = temp->next;
  }
  return ExpandedTrain;
}

//Returns the transit time given the train details as input parameters
int TransitTime(MyTrainInfoPerStationClass *Train2, TrainInfoPerStation *Train1){
  if (Train2->StationName == "DUMMY"){
    return -1;
  }
  int Train2D, Train1D;
  for (int i = 0; i < 7; i++){
    if (Train2->daysOfWeek[i]){
      Train2D = i;
    }
    if (Train1->daysOfWeek[i]){
      Train1D = i;
    }
  }
  int tT = Train2->depTime - Train1->arrTime + 2400 * (Train2D - Train1D);
  return tT;
}

//Returns the entire paths possible after considering the conditions from the question
vector<listOfObjects<MyTrainInfoPerStationClass *> *> DFS(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime, StationAdjacencyList *adjacency, Dictionary<int> stnNameToIndex){
  vector<listOfObjects<MyTrainInfoPerStationClass *> *> paths;
  if(srcStnName == destStnName){
    //Creating a dummy element for the base
    MyTrainInfoPerStationClass * res = new MyTrainInfoPerStationClass(-100,-100,-100,-100,"DUMMY");
    res->setDayOfWeek(0);
    listOfObjects<MyTrainInfoPerStationClass*>*path = new listOfObjects<MyTrainInfoPerStationClass *>(res);
    paths.push_back(path);
  }
  else{
    listOfObjects<StationConnectionInfo *> *AdjNeighbours = adjacency[stnNameToIndex.get(srcStnName)->value].toStations;
    while (AdjNeighbours != NULL){
      listOfObjects<StationConnectionInfo *> *temp = adjacency[AdjNeighbours->object->adjacentStnIndex].fromStations;
      listOfObjects<TrainInfoPerStation *> *Trn = nullptr;
      listOfObjects<TrainInfoPerStation *> *ExpTrn = nullptr;
      while (temp != NULL){
        if(stnNameToIndex.get(srcStnName)->value == temp->object->adjacentStnIndex){
          Trn = temp->object->trains;
          ExpTrn = ExpandTrain(Trn);
          break;
        }
        temp = temp->next;
      }
      string stopStation = stnNameToIndex.getKeyAtIndex(AdjNeighbours->object->adjacentStnIndex);
      vector<listOfObjects<MyTrainInfoPerStationClass *>*> halfPaths = DFS(stopStation,destStnName,maxStopOvers,maxTransitTime,adjacency,stnNameToIndex);
      listOfObjects<TrainInfoPerStation *> *ExpCurr = ExpTrn;
      while(ExpCurr != NULL){
        for(auto i : halfPaths){
          int tT = TransitTime(i->object,ExpCurr->object);
          if( tT <= maxTransitTime && tT>=0 || i->object->StationName == "DUMMY" ){
            listOfObjects<TrainInfoPerStation *> *curr = Trn;
            while(curr != NULL){
              if(curr->object->journeyCode == ExpCurr->object->journeyCode){
                break;
              }
              curr = curr->next;
            }
            listOfObjects<TrainInfoPerStation *> *Trn2 = AdjNeighbours->object->trains;
            listOfObjects<TrainInfoPerStation *> *curr2 = Trn2;
            while(curr2 != NULL){
              if(curr2->object->journeyCode == curr->object->journeyCode){
                break;
              }
              curr2 = curr2->next;
            }
            int JT; // Journey Time
            int StrtD,EndD;
            for(int j=0; j<7; j++){
              if(curr->object->daysOfWeek[j]){
                StrtD = j;
              }
              if(curr2->object->daysOfWeek[j]){
                EndD = j;
              }
            }
            JT = curr2->object->arrTime - curr->object->depTime + 2400*(EndD - StrtD);
            listOfObjects<TrainInfoPerStation *> *ExpTrn2 = ExpandTrain(Trn2);
            listOfObjects<TrainInfoPerStation *> *tempTrain = ExpTrn2;
            while(tempTrain != NULL){
              int JT2; // Journey Time
              int StrtD2,EndD2;
              for(int j=0; j<7; j++){
                if(ExpCurr->object->daysOfWeek[j]){
                  StrtD2 = j;
                }
                if(tempTrain->object->daysOfWeek[j]){
                  EndD2 = j;
                }
              }
              JT2 = tempTrain->object->arrTime - ExpCurr->object->depTime + 2400*(EndD2 - StrtD2);
              if(tempTrain->object->journeyCode == ExpCurr->object->journeyCode && JT2 == JT){
                int JrnyCode = tempTrain->object->journeyCode;
                int StSeq = tempTrain->object->stopSeq;
                int ATime = tempTrain->object->arrTime;
                int DTime = tempTrain->object->depTime;

                MyTrainInfoPerStationClass * startJrny = new MyTrainInfoPerStationClass(JrnyCode, StSeq, ATime, DTime,srcStnName);
                for(int j=0; j<7; j++){
                  if(tempTrain->object->daysOfWeek[j]){
                    startJrny->setDayOfWeek(j);  
                  }
                }
                listOfObjects<MyTrainInfoPerStationClass *> *path = new listOfObjects<MyTrainInfoPerStationClass *>(startJrny);
                JrnyCode = ExpCurr->object->journeyCode;
                StSeq = ExpCurr->object->stopSeq;
                ATime = ExpCurr->object->arrTime;
                DTime = ExpCurr->object->depTime;
                MyTrainInfoPerStationClass * Jrny = new MyTrainInfoPerStationClass(JrnyCode, StSeq, ATime, DTime,stopStation);
                for(int j=0; j<7; j++){
                  if(ExpCurr->object->daysOfWeek[j]){
                    Jrny->setDayOfWeek(j);
                  }
                } 
                listOfObjects<MyTrainInfoPerStationClass *> *pathContinued = new listOfObjects<MyTrainInfoPerStationClass *>(Jrny);
                path->next = pathContinued;
                pathContinued->next = i;
                int stops=0;
                listOfObjects<MyTrainInfoPerStationClass *> *PREV = path;
                listOfObjects<MyTrainInfoPerStationClass *> *CURRENT = PREV->next->next;
                while(CURRENT->object->StationName != "DUMMY"){
                  if(PREV->object->journeyCode != CURRENT->object->journeyCode){
                    stops++;
                  }
                  PREV = CURRENT;
                  CURRENT = CURRENT->next->next;
                }
                if(stops <= maxStopOvers){
                  paths.push_back(path);
                }
                break;
              }
              tempTrain = tempTrain->next;
            }
          }        
        }
        ExpCurr = ExpCurr->next;
      }
      AdjNeighbours = AdjNeighbours->next;
    }
  }
  return paths;
}
void MyPrint(vector<listOfObjects<MyTrainInfoPerStationClass *> *> paths ){
  int N = 0;
  cout << "===================================================================================\n";
  for (auto path : paths){
    cout << BLUE << "Path " <<RESET <<N+1<< endl;
    listOfObjects<MyTrainInfoPerStationClass *> *pathI;
    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    pathI = path;
    int i=0;
    while (pathI->object->StationName != "DUMMY"){
      i++;
      cout << GREEN << "Day: " << RESET;
      for (int k = 0; k < 7; k++){
        if (pathI->object->daysOfWeek[k])
          cout << days[k] << "\t";
      }
      cout << BLUE << "JourneyCode: " << RESET <<  pathI->object->journeyCode <<"\t";
      cout << RED << "Arr: " << RESET;  
      if (pathI->object->arrTime == -1){
        cout << "Starts"<< "\t";
      }
      else{
        cout << pathI->object->arrTime << "\t";
      }
      cout << RED << "Dep: " << RESET;
      if (pathI->object->depTime == -1){
        cout << "Ends"<< "\t";
      }
      else{
        cout << pathI->object->depTime<< "\t";
      }
      cout<<" " << GREEN << pathI->object->StationName << RESET << endl;
      if (pathI->object->StationName == pathI->next->object->StationName){
        if (pathI->object->journeyCode == pathI->next->object->journeyCode){
          cout << GREEN <<"No Change of Train" <<RESET << endl;
        }
        else{
          cout <<GREEN<< "Train change from " << RESET << pathI->object->journeyCode << " to " << pathI->next->object->journeyCode << "\t";
          int jCode = pathI->object->journeyCode;
          int stSeq = pathI->object->stopSeq;
          int arrTime = pathI->object->arrTime;
          int depTime = pathI->object->depTime;
          TrainInfoPerStation *newent = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
          for (int k = 0; k < 7; k++){
            if (pathI->object->daysOfWeek[k]){
              newent->setDayOfWeek(k);
            }
          }
          cout << GREEN << "Transit time: " << RESET << TransitTime(pathI->next->object, newent)<<endl;
        }
      }
      pathI = pathI->next;
    }
    N++;
    cout << "===================================================================================\n";
  }
  cout << BLUE <<"Total number of possible journeys are :" << RESET << N << endl;
}
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  // USING DFS FUNCTION I CAN GET ALL THE POSSIBLE PATHS WHICH MATCH THE REQUIRED
  // CONDITIONS AND I WILL RETURN THEM
  // USING MYPRINT FUNCTION WE CAN PRINT THE PATHS.
  vector< listOfObjects<MyTrainInfoPerStationClass *> *> paths = DFS(srcStnName,destStnName,maxStopOvers,maxTransitTime,adjacency,stnNameToIndex);
  MyPrint(paths);
  return;
}

#endif