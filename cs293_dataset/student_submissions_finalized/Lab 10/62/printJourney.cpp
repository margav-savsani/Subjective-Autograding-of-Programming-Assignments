#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
template <typename T>
class linkedQueue{ // FIFO
	listOfObjects<T>* head;
	listOfObjects<T>* tail;
	bool isempty; // true if empty
	public:
		linkedQueue(){//def constructor
			head = tail = nullptr;
			isempty = true;
		}
		//insert element into queue
		bool insert(listOfObjects<T>* element){
			if (element==nullptr) return false;//invalid
			if (isempty){ // first insert to empty queue
				head = tail = element;
				head -> next = head->prev = nullptr;
				isempty = false;
				return true;
			}
			tail->next = element; //regular insertion
			element->prev = tail;
			tail = element;
			return true;
		}
		//check if queue is empty, reqs for bfs loop
		bool isEmpty() {
			return isempty;
		}
		// return ll starting at head, required for printing
		listOfObjects<T>* gethead(){
			return this->head;
		}
		// remove and return element of queue
		listOfObjects<T>* pop(){ // they shall deal with the memory
			if (isempty) return nullptr;//invalid
			listOfObjects<T>* curr = head;
			head = head->next;
			if (head==nullptr) isempty = true;// check if popper list empty
			curr->next = nullptr;
			return curr;
		}
};

struct journey{
	private:
	linkedQueue<TrainInfoPerStation*> edges;
	unsigned int wait_time;
	unsigned int intermediate_stops;
	
	public:
	bool addtime(int time){
		if (time<=0) return false;
		wait_time += time;
		return true;
	}
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
