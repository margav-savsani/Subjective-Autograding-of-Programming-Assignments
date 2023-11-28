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
  Entry<int> start=stnNameToIndex.get(srcStnName);
  int index_start = start.value;
  x= stnNameToIndex.getKeyAtIndex(index_start);
  cout << "This function is to be implemented by you." << endl;
  /* Idea  of the solution:
    Going to keep all journey codes of srcStnName adajcent stations.
    Using different varient of BFS( Going to visit node multiple time ) it will keep track of journey codes which joins srcStnName and destStnName
    Remaining journey codes will get popped out from the vector when algorithm founds that journey with that journey code will end at some oint which does not include the destStnName

  */
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
