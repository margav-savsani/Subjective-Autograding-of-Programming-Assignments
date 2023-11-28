#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

using namespace std;
//queue implementation with given linked list listofobjects
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

struct trainlet{ // information required for BFS queue
	TrainInfoPerStation* journey; // Train info corresponding to start details of train
	int stnindex;// index of station travelling to
	int jcode;//journey code
	trainlet(){
		journey=nullptr;
		stnindex=jcode=-1;
	}// constructors
	trainlet(TrainInfoPerStation* journey_,int stnindex_,int jcode_){
		journey = journey_;
		stnindex = stnindex_;
		jcode = jcode_;
	}
};
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
	int srcindex = stnNameToIndex.get(srcStnName)->value, destindex = stnNameToIndex.get(destStnName)->value; //indices in the adjacency list
	linkedQueue<trainlet> BFSQ; // Queue used in breadthfirstsearch
	//	here we initialise on stationInfo instead o adjacency list as we want to print the dep/arrival on the source station
	listOfObjects<TrainInfoPerStation*>* srcstn = stationInfo[srcindex];//trains starting from src
	if (srcstn==nullptr) return;// safe
	for (listOfObjects<TrainInfoPerStation*>* totrain = srcstn; totrain!=nullptr; totrain=totrain->next){
		BFSQ.insert(new listOfObjects<trainlet>(trainlet(totrain->object,srcindex,totrain->object->journeyCode)));//
	}
	linkedQueue<TrainInfoPerStation *> valid_journeys;// queue containing valid journeys as traininfopertation
	while (!BFSQ.isEmpty()){
		listOfObjects<trainlet>* current= BFSQ.pop();
		if(current->object.stnindex==destindex){//reached the destination
			valid_journeys.insert(new listOfObjects<TrainInfoPerStation*>(current->object.journey));
			delete current;
			continue;
		}
		bool found=0;// keep going until a match is found, break at the point to optimise
		for(listOfObjects<StationConnectionInfo*>* nstn = adjacency[current->object.stnindex].toStations;nstn!=nullptr;nstn=nstn->next){ //inside next station
			for (listOfObjects<TrainInfoPerStation*>* tr = nstn->object->trains; tr!=nullptr; tr=tr->next){
				if (tr->object->journeyCode==current->object.jcode){ // looking at journeys to those stations
					current->object.stnindex=nstn->object->adjacentStnIndex;
					BFSQ.insert(current);
					found=1;
					break;
				}
			}
			if (found) break;
		}
		if (!found) delete current;
	}
	if (valid_journeys.isEmpty()){ //when the valid journeys are empty
		cout<<RED<<"\nSorry! No Journeys Present."<<RESET<<endl;
	}
	printStationInfo(valid_journeys.gethead());// print info received
	
	return;
}