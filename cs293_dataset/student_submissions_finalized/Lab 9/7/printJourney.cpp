#ifndef PLANNER_H
#include "planner.h"
#endif

#ifnded STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

    int srcIndex;
    
    for(int i = 0; i < stnNameToIndex.numFilled; i++){
        if(srcStnName == stnNameToIndex.A[i].key){
            srcIndex = stnNameToIndex.A[i].value;
        }
    }
    
    for(int i = 0; i < ; i++){
        if(destStnName == stnNameToIndex.A[i].key){
            destIndex = stnNameToIndex.A[i].value;
        }
    }
    
    if(srcIndex <= DICT_SIZE){
        StationAdjacencyList src = adjacency[srcIndex];
    }
    
    if(destIndex <= DICT_SIZE){
        StationAdjacencyList dest = adjacency[destIndex];
    }
    
    while(){
        
    }
    
  // insert your code here
  
  //cout << "This function is to be implemented by you." << endl;
    
  return;
}
