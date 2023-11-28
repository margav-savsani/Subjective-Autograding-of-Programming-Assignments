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
  template<typename T>
Dictionary<T>::Dictionary(){
    N = DICT_SIZE;
    numFilled = 0;
    A = new Entry<T>[N];
    if (A == nullptr) {
      cout << "Memory allocation failure." << endl;
    }
    else {
      Entry<T> init_object;
      for(int i = 0; i < N; i++){
	A[i] = init_object;
      }
    }
};

template<typename T>
int Dictionary<T>::hashValue(string key){
  int size = key.length();

  int hashValue = 0;
  int x = 33;
  for(int i = size - 1; i >= 0; i--){
    int val = (int)(key.at(i));
    hashValue = (val + x * hashValue) % N;
  }
  return hashValue;
}
  cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
