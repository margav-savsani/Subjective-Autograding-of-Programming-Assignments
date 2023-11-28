#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

/**
 * @brief Pretty prints out a list of direct journeys between two given stations 
 * 
 * @param src Name of the source station
 * @param dest Name of the destination station
 */
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  // cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
    /*
    TODO:
    - Consider that the BFS need not strictly start from the src
        - Even if src and dest are intermediate stops in the complete journey, the journey is still a direct one
        - BFS can stop at dest, but it can start from somewhere before src
    - Implement a loop performing BFS
        - loop over all the possible trains that leave the source
        - in every run of the loop, perform BFS on the specific train
        - At every new node found for a given journey code, print that pair out
    */

    Entry<int> *src_entry =  this->stnNameToIndex.get(src);
    if(src_entry == nullptr) return;
    int src_ind = src_entry->value;

    StationAdjacencyList *src_adj = this->adjacency[src_ind];

    return;
}

#endif
