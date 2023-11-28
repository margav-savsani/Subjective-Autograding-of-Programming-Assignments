#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#ifndef PLANNER_H
#include "planner.h"
#endif
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;
bool start_check(int startt,int endd,int journey_code, StationAdjacencyList adjacency[]){
    int j=0;
    int i=0;
    int index_adj;
    if(startt==endd){return true;}
    else if (startt==-1){return false;}
    else{
        listOfObjects<StationConnectionInfo *> *station = adjacency[startt].toStations;
        while(station!=nullptr){
            //cout<<"first while"<<endl;
            index_adj = station->object->adjacentStnIndex;
            listOfObjects<TrainInfoPerStation *> *X = station->object->trains;
            while(X!=nullptr){
                //cout<<"second while loop"<<endl;
                if(X->object->journeyCode == journey_code){
                    //cout<<"2"<<endl;
                    j++;
                    break;
                }
                else{X=X->next;/*cout<<"hgf"<<endl;*/}
            }
            //cout<<"outof second while loop"
            if(j>0){i++;/*cout<<"kjhg"<<endl;*/break;}
            else{/*cout<<"YYY"<<endl;*/station=station->next;}
        }
        //cout<<"outof while loop"<<endl;
        if(i>0){return(start_check(index_adj,endd,journey_code,adjacency));}
        else{return false;}
    }
}
void Planner::printDirectJourneys(string srcStnName, string destStnName){
    bool Q = false;
    int srcStnIndex = stnNameToIndex.get(srcStnName)->value;
    int destStnIndex = stnNameToIndex.get(destStnName)->value;
    TrainInfoPerStation * cons = new TrainInfoPerStation(0,0,0,0);
    listOfObjects <TrainInfoPerStation *> *directjourney = new listOfObjects <TrainInfoPerStation *> (cons);
    listOfObjects <StationConnectionInfo * > *adj_tostations = adjacency[srcStnIndex].toStations;
    while(adj_tostations!=nullptr){
        srcStnIndex =  adj_tostations->object->adjacentStnIndex;
        listOfObjects <TrainInfoPerStation *> *trainslist = adj_tostations->object->trains;
        while(trainslist!=nullptr){
            //cout<<"rrrrrrrrrr"<<endl;
            int code = trainslist->object->journeyCode;
            if(start_check(srcStnIndex,destStnIndex,code,adjacency)){
                //cout<<"zz"<<endl;
                Q = true;
                listOfObjects <TrainInfoPerStation *> *T =  directjourney;
                while(T->next!=nullptr){/*cout<<"entered"<<ednl;*/T = T->next;}
                T->next = new listOfObjects <TrainInfoPerStation *>(trainslist->object);
            }
            trainslist = trainslist->next;
            //cout<<"n"<<endl;
        }
        //cout<<"adj_tostations..null"<<endl;
        adj_tostations = adj_tostations->next;
    }
    printStationInfo(directjourney);
if(Q==false){cout << "No journeys are available" << endl;}
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  return;
}
#endif
