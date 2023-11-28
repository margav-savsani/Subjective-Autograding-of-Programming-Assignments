#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  
  // insert your code here
  cout << "This function is to be implemented by you." << endl;
  
  //Let's make an array of DICT_SIZE, in which we store the number of times that stations has been reached using  a breadth first search
  static int *multiplier_array = new int [DICT_SIZE];
  int index_src = stnNameToIndex.get(srcStnName);
  listOfObjects<typename T> *iterator = adjacency[index_src].toStations;
  while (iterator!=nullptr){
    multiplier_array[iteartor->object->adjacentStnIndex]++;
    printDirectJourneys( stnNameToIndex.getKeyAtIndex(iterator->object->adjacentStnIndex)  , destStnName)
    iteartor=iterator->next; 
  }
  
  //I'll expand this idea further to finally find, all the valid jounreys

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
