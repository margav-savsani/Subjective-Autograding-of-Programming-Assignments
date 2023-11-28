#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif


using namespace std;



// This function will return the array of journey code present in the linked list of trains.
// The first element of array will store the total number of journeys available in that station and the rest of the array stores the journey code.
int* Planner::listTojCode(listOfObjects<TrainInfoPerStation *> *list){
    int totalTrain = 0;
    listOfObjects<TrainInfoPerStation *> *tr;
    tr = list;
    while(tr != nullptr){
        tr = tr->next;
        totalTrain++;
    }

    int *JC = new int[totalTrain+1]; // first index 0 will store the total number of journey code.
    int b=1;
    tr = list;
    JC[0] = totalTrain;
    while(tr != nullptr){
        
        JC[b] = tr->object->journeyCode;
        tr = tr->next;
        b++;
    }

    return JC;

}



// This function has 3 arguments indexA(index of a station through which we are supposed to check whether journey code jCode is available or not) destIndex(index of the destination station we check jCode whether it is available or not throuch the node till the destination station) if we fail to reach the destination station then i return 0 else if we succeed to reach destination station through jCode then we return jCode.
// This function will traverse throught the all the nodes of station in recursion and will check whether the journey code is present in the list od trains of all the traversed node and if it is able to reach the destination it will return
// IndexA is the index of all toStation that we pass in recursive call.
int Planner::JCode(int indexA, int destIndex, int jCode){
    int* a;  // will store the array returned by listTojCode
    
    
    int len;  // will store the length of all jerney code available
    
    if(indexA == destIndex){ // if indexA is same as destIndex then we return the jCode.
        
        a = listTojCode(stationInfo[indexA]);
        
        len = a[0];
        for(int i = 1; i<len+1; i++){  // index starts from 1 since index 0 stores total number of trains available.
            if(a[i] == jCode){
                // if jCode found in list of trains then we return jCode.
                return jCode;
                break;
            }
        }
        return 0;
    }
    else {  // if indexA is not same as destIndex
        listOfObjects<StationConnectionInfo *> *c;// will handle the list of toStation of indexA.
        c = adjacency[indexA].toStations;
        while(c != nullptr){

            a = listTojCode(c->object->trains);  // will store the list of trains of current toStation.
            len = a[0];  // number of total journeys
            for(int i = 1; i<len+1; i++){   // index starts from 1 since index 0 stores total number of trains available.
                if(a[i] == jCode){ // If the jCode is present in that to station train list then we don't need to check for the other toStations since 1 train can only travell between source station and any one of the toStation.
                    if(c->object->adjacentStnIndex == destIndex){  // if toStation is the destination Station then we return the index
                        return jCode;
                    }
                    return JCode(c->object->adjacentStnIndex, destIndex, jCode);
                }
            }

            c = c->next;
        }

    }

    return 0;
}



void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

    
    int srcIndex; // Index of source station
    int destIndex; // Index of destination station
    Entry<int> *a;
    a = stnNameToIndex.get(srcStnName);
    srcIndex = a->value;
    a = stnNameToIndex.get(destStnName);
    destIndex = a->value;

    
    
    StationAdjacencyList srcStn = adjacency[srcIndex];
    
    
    
    StationAdjacencyList destStn = adjacency[destIndex];
    
    int o;

    // Finding total number of trains available from source station 
    int totalTrain = 0;
    listOfObjects<TrainInfoPerStation *> *tr;
    tr = stationInfo[srcIndex];
    while(tr != nullptr){
        tr = tr->next;
        totalTrain++;
    }

    int *JC = new int[totalTrain];
    int b=0;
    tr = stationInfo[srcIndex];
    while(tr != nullptr){
        
        JC[b] = tr->object->journeyCode;
        tr = tr->next;
        b++;
    }

    listOfObjects<TrainInfoPerStation *> *final_list;// This list will store all the TrainInfoPerStation of source station that are available from source station to destination station which we checked through traversing through the toStation nodes of source station in recursion.
    final_list = new listOfObjects<TrainInfoPerStation *>(nullptr);
    int q = 0;
    listOfObjects<StationConnectionInfo *> *c;
    
    // will traverse through the toStations and call the function JCode to check whether jCode is a valid Journey or not
    
    
    listOfObjects<TrainInfoPerStation *> *tr1; // for final list
    tr1 = final_list;
    for(int i=0; i<totalTrain; i++){
        c = srcStn.toStations;
        while(c != nullptr){
            o = JCode(c->object->adjacentStnIndex, destIndex, JC[i]);
            if(o != 0){
                listOfObjects<TrainInfoPerStation *> *tr; // for stationInfo[srcIndex]
                tr = stationInfo[srcIndex];
                
                while(tr != nullptr){  // will search for o journeycode in list of trains of source station and will add the TrainInfoPerStation.
                    if(o == tr->object->journeyCode){
                        
                        
                        if(q == 0){
                            final_list = new listOfObjects<TrainInfoPerStation *>(tr->object);
                            tr1 = final_list;
                            tr = tr->next;
                            q++;
                        }
                        
                        else{
                            tr1->next = new listOfObjects<TrainInfoPerStation *>(tr->object);
                            tr1 = tr1->next;
                            tr = tr->next;
                        }
                        
                        
                        break;
                    }
                }
                
//
            }
            c = c->next;
        }
    }

    printStationInfo(final_list);
    
    
  // insert your code here
  
  //cout << "This function is to be implemented by you." << endl;
    
  return;
}

#endif
