#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

class BFS_Station{
    public:
    int index;
    listOfObjects<int> *valid;
    
    BFS_Station(int ind){
        index=ind;
        valid=nullptr;
    }
    
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{   
    //cout<<"Dest: "<<stnNameToIndex.hashValue(destStnName)<<endl;
    TrainInfoPerStation * ans1 = new TrainInfoPerStation(-1 ,-1, -2, -2);
    listOfObjects<TrainInfoPerStation *> *ans = new listOfObjects<TrainInfoPerStation *>(ans1);
    listOfObjects<TrainInfoPerStation *> *ans3=ans;
    listOfObjects<StationConnectionInfo*> *curr=adjacency[stnNameToIndex.hashValue(srcStnName)].toStations;
    while(curr!=nullptr){//Looping through the toStation list of srcStnName
        listOfObjects<TrainInfoPerStation*> *temp=curr->object->trains;
        //cout<<"MainJCode"<<temp->object->journeyCode<<endl;
        listOfObjects<StationConnectionInfo*> *curr1=curr;
        while(temp!=nullptr){//Looping through each train going to the toStation
            curr1=curr;
            while(curr1!=nullptr){//Searching along the journey of the train
                listOfObjects<StationConnectionInfo*> *curr2=curr1;
                bool check=false;
                while(curr2!=nullptr){//Checking the next station with the same train
                    bool check1=false; 
                    listOfObjects<TrainInfoPerStation*> *temp1=curr2->object->trains;
                    //cout<<stnNameToIndex.getKeyAtIndex(curr2->object->adjacentStnIndex)<<endl;
                    while(temp1!=nullptr){//Searching for the same train in the list of trains
                        //cout<<"JCode"<<temp1->object->journeyCode<<endl;
                        if(temp1->object->journeyCode==temp->object->journeyCode){
                            if(curr2->object->adjacentStnIndex == stnNameToIndex.hashValue(destStnName)){
                                listOfObjects<TrainInfoPerStation *> *t = stationInfo[stnNameToIndex.hashValue(srcStnName)];
                                while(t!=nullptr){
                                    if(t->object->journeyCode==temp->object->journeyCode){
                                        ans3->object=temp->object;
                                        break;
                                    }
                                    t=t->next;
                                }
                                ans3->next=new listOfObjects<TrainInfoPerStation *>(ans1);
                                ans3=ans3->next;
                                check1=true;
                                //cout<<"Here"<<endl;
                                break;
                            }
                            //cout<<"Hmm"<<stnNameToIndex.getKeyAtIndex(curr1->object->adjacentStnIndex)<<endl;
                            curr1=adjacency[curr2->object->adjacentStnIndex].toStations;
                            
                            check1=true;
                            check=true;
                            break;
                        }
                        temp1=temp1->next;
                    }
                    if(check1==true){
                        break;
                    }
                    curr2=curr2->next;
                }
                if(check==false){
                    break;
                }
            }
            temp=temp->next;
            //cout<<(temp==nullptr)<<endl;
        }
        curr=curr->next;
    }
    ans3=ans;
    while(ans3->object->journeyCode!=-1){
        printStationInfo(ans3);
        ans3=ans3->next;
    }

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
