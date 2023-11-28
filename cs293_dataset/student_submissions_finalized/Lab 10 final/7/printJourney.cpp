#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include<vector>



using namespace std;


// tr: train travelling from stn to the toStation of stn

void helper_function1(vector< vector<int> > &s, vector<int> q, vector< vector<TrainInfoPerStation *> > &i, vector<TrainInfoPerStation *> j, int k, int maxTime, int maxStop, TrainInfoPerStation *tr, StationConnectionInfo *stn, StationAdjacencyList *adjacency, int destIndex){
   

    //bool jCodeFound = false;  // arriving journeycode found

    vector<TrainInfoPerStation *> m;
    m = j;
    listOfObjects<TrainInfoPerStation *> *tr1;  // arriving train
    vector<int> x;
    x = q;
    //tr1 = stn->trains;
    //tr1 = adjacency[stn->adjacentStnIndex].toStations->
    listOfObjects<TrainInfoPerStation *> *tr2;  // departing train
    listOfObjects<StationConnectionInfo *> *toStn = adjacency[stn->adjacentStnIndex].toStations;
    listOfObjects<TrainInfoPerStation *> *tr3;
    //check here id toStation index is same as destination station
    // if yes then store the j in i
    if(stn->adjacentStnIndex == destIndex){
        
        //-----if stn is destStn then-----
        i.push_back(j);
        s.push_back(q);
        return;
        
    }
    
    else{
        
        while(toStn != nullptr){ // toStation of recently passed stationConnectionInfo
            //tr1 = nullptr;
            tr1 = toStn->object->trains; // ariving train
            
            while(tr1 != nullptr){
                
                if(tr1->object->journeyCode == tr->journeyCode){  // checking whether that train is arriving to toStation or not
                    //jCodeFound = true;
                    while(toStn->object->trains->prev != nullptr){
                            toStn->object->trains = toStn->object->trains->prev;
                    }
                    tr2 = toStn->object->trains; // departing train
                    while(tr2 != nullptr){   // if tr is arriving in toStation then tr1 is keeping track of departing train.
                        // tr1,stn->object
                        
                        if(tr1->object == tr2->object){ // when there is no change of train
                            if(k <= maxStop){
                            j.push_back(tr2->object);
                            q.push_back(toStn->object->adjacentStnIndex);
                            helper_function1(s, q, i, j, k, maxTime, maxStop, tr2->object, toStn->object, adjacency, destIndex);
                            j = m;
                            q = x;
                            }
                        }
                        
                        else{  // when there is change of train
                            
                            if(k<maxStop){
                                
                                for(int p = 0; p<7; p++){
                                    
                                    if(tr1->object->daysOfWeek[p] == true && tr2->object->daysOfWeek[p] == true){
                                        
                                        //---check departure time is greater than arriving time---
                                        if(k < maxTime){
                                        
                                        if(tr2->object->depTime - tr1->object->arrTime  <= maxTime){
                                            
                                            j.push_back(tr2->object);
                                            q.push_back(toStn->object->adjacentStnIndex);
                                            helper_function1(s, q, i, j, k+1, maxTime, maxStop, tr2->object, toStn->object, adjacency, destIndex);
                                            j = m;
                                            q = x;
                                        }
                                        }
                                    }
                                    else if(p<6){
                                        if(tr1->object->daysOfWeek[p] == true && tr2->object->daysOfWeek[p+1] == true){
                                            
                                            //-----check whether works or not-----
                                            if(k < maxTime){
                                            if(2400 + tr2->object->depTime - tr1->object->arrTime  <= maxTime){
                                                j.push_back(tr2->object);
                                                q.push_back(toStn->object->adjacentStnIndex);
                                                helper_function1(s, q, i, j, k+1, maxTime, maxStop, tr2->object, toStn->object, adjacency, destIndex);
                                                j = m;
                                                q = x;
                                            }
                                            }
                                        }
                                    }
                                    else if(p == 6){
                                        if(tr1->object->daysOfWeek[p] == true && tr2->object->daysOfWeek[0] == true){
                                            if(k < maxTime){
                                            if(2400 + tr2->object->depTime - tr1->object->arrTime  <= maxTime){
                                                j.push_back(tr2->object);
                                                q.push_back(toStn->object->adjacentStnIndex);
                                                helper_function1(s, q, i, j, k+1, maxTime, maxStop, tr2->object, toStn->object, adjacency, destIndex);
                                                j = m;
                                                q = x;
                                            }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        tr2 = tr2->next;
                    }
                    break;
                }
                tr1 = tr1->next;
            }
            toStn = toStn->next;
        }
    }
    return;
    
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  //cout << "This function is to be implemented by you." << endl;
    int k=0;
    
    int srcIndex = (stnNameToIndex.get(srcStnName))->value;
    int destIndex = (stnNameToIndex.get(destStnName))->value;

    StationAdjacencyList src = adjacency[srcIndex];
    StationAdjacencyList dest = adjacency[destIndex];
    listOfObjects<StationConnectionInfo *> *stn;
    stn = adjacency[srcIndex].toStations;
    
    
    
    listOfObjects<TrainInfoPerStation *> *train;
    train = stationInfo[srcIndex];
    vector< vector<TrainInfoPerStation *> > i;
    vector<TrainInfoPerStation *> j;
    vector< vector<int> > s;
    vector<int> q;
    vector<int> x;
    x = x;
    vector<TrainInfoPerStation *> m;
    m = j;
    listOfObjects<TrainInfoPerStation *> *tr;
    listOfObjects<TrainInfoPerStation *> *tr1;
    
    
    //-----train list of source station------
    while(train != nullptr){
        
        //------toStation list of source station-----
        while(stn != nullptr){  // changed stn to stn->object
            
            //---check whether the toStation is destination station or not-----
            
            //if(stn->object != nullptr){
            tr = stn->object->trains; // arriving train
            
            //-----train list of toStation of source station----
            while(tr != nullptr){
                
                if(tr->object->journeyCode == train->object->journeyCode){  // checking whether that train is arriving to toStation or not
                    //jCodeFound = true;
                    tr1 = stn->object->trains; // departing train
                    while(tr1 != nullptr){   // if tr is arriving in toStation then tr1 is keeping track of departing train.
                        // tr1,stn->object
                        
                        if(tr->object == tr1->object){ // when there is no change of train
                            
                            j.push_back(tr->object);
                            q.push_back(srcIndex);
                            j.push_back(tr1->object);
                            q.push_back(stn->object->adjacentStnIndex);
                            helper_function1(s, q, i, j, 0, maxTransitTime, maxStopOvers, tr1->object, stn->object, adjacency, destIndex);
                            j = m;
                            q = x;
                        }
                        
                        else{  // when there is change of train
                            
                            if(k<maxStopOvers){
                                
                                for(int p = 0; p<7; p++){
                                    
                                    if(tr->object->daysOfWeek[p] == true && tr1->object->daysOfWeek[p] == true){
                                        
                                        //---check departure time is greater than arriving time---
                                        
                                        if(tr1->object->depTime - tr->object->arrTime  <= maxTransitTime){
                                            j.push_back(tr->object);
                                            q.push_back(srcIndex);
                                            j.push_back(tr1->object);
                                            q.push_back(stn->object->adjacentStnIndex);
                                            helper_function1(s, q, i, j, 1, maxTransitTime, maxStopOvers, tr1->object, stn->object, adjacency, destIndex);
                                            j = m;
                                            q = x;
                                        }
                                    }
                                    else if(p<6){
                                        if(tr->object->daysOfWeek[p] == true && tr1->object->daysOfWeek[p+1] == true){
                                            
                                            //-----check whether works or not-----
                                            
                                            if(2400 + tr1->object->depTime - tr->object->arrTime  <= maxTransitTime){
                                                j.push_back(tr->object);
                                                q.push_back(srcIndex);
                                                j.push_back(tr1->object);
                                                q.push_back(stn->object->adjacentStnIndex);
                                                helper_function1(s, q, i, j, 1, maxTransitTime, maxStopOvers, tr1->object, stn->object, adjacency, destIndex);
                                                j = m;
                                                q = x;
                                            }
                                        }
                                    }
                                    else if(p == 6){
                                        if(tr->object->daysOfWeek[p] == true && tr1->object->daysOfWeek[0] == true){
                                            
                                            if(2400 + tr1->object->depTime - tr->object->arrTime  <= maxTransitTime){
                                                j.push_back(tr->object);
                                                q.push_back(srcIndex);
                                                j.push_back(tr1->object);
                                                q.push_back(stn->object->adjacentStnIndex);
                                                helper_function1(s, q, i, j, 1, maxTransitTime, maxStopOvers, tr1->object, stn->object, adjacency, destIndex);
                                                j = m;
                                                q = x;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        tr1 = tr1->next;
                    }
                }
                tr = tr->next;
            }
            //}
            stn = stn->next;
        }
        train = train->next;
    }
    
    listOfObjects<TrainInfoPerStation *> *l;
    listOfObjects<TrainInfoPerStation *> *l1;
    int g1 = 0;

    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    for(int d1=0; d1<i.size(); d1++){
        cout << "Journey:" << endl;
        for(int d2=0; d2<i[d1].size(); d2++){

            cout << GREEN << "Station Name: " << stnNameToIndex.getKeyAtIndex(s[d1][d2]) << RESET << endl;
            cout << RED << "Available days of week: ";
            for(int a = 0; a<7; a++){
                if(i[d1][d2]->daysOfWeek[a]){
                    cout << days[a] << "; ";
                }
            }
            cout << RESET << endl;
            cout << BLUE << "Train Journey Code: " << i[d1][d2]->journeyCode << " Arrival Time: "<< i[d1][d2]->arrTime << " Departure Time: " << i[d1][d2]->depTime << RESET << endl;;
        }
        
    }
 

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
