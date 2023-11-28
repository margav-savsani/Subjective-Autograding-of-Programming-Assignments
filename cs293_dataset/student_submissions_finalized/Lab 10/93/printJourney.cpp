#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
#include <functional>
// #include <queue>

using namespace std;
namespace my_ds{
//implementation of a single ended queue
	template <typename T>
	class queue_node{
	public:
		queue_node<T>* next;
		T object;
	};
	template <typename T> 
	class queue{
		queue_node<T>* start = NULL;
		queue_node<T>* end = NULL;
	public:
		void push(T obj){
			if(!start){
				start = end = new queue_node<T>{NULL, obj};
				return;
			}
			end->next = new queue_node<T>{NULL, obj};
			end = end->next;
		}
		T front(){
			return start->object;
		}
		void pop(){
			if(!start) return;
			auto temp = start;
			start = start->next;
			delete temp;
			if(!start)
				end = NULL;
		}
		bool empty(){
			return !start;
		}
	};
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

	// insert your code here
	
	cout << "This function is to be implemented by you." << endl;

	// Whenever you need to print a journey, construct a
	// listOfObjects<TrainInfoPerStation *> appropriately, and then
	// use printStationInfo that we had used in Lab 7.
	// printStationInfo is a private member function of
	// the Planner class. It is declared in planner.h and implemented in
	// planner.cpp

	
	return;
}

#endif
