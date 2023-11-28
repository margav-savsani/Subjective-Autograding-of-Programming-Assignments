#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct BFSNode{ //  a node for the BFSQueue
	int stnidx;
	TrainInfoPerStation* traininfo;
	BFSNode* next;

	BFSNode(){}
	BFSNode(int stnidx, TrainInfoPerStation* traininfo, BFSNode* next)  {
		this->stnidx = stnidx;
		this->traininfo = traininfo;
		this->next = next;
	}
};

class BFSQueue{ 
	// A simple Queue of BFSNode
	BFSNode *head;
	BFSNode *tail;
public:
	BFSQueue(){
		head = tail = nullptr;
	}
	void insert(int stnidx, TrainInfoPerStation* traininfo){
		if(head==nullptr){
			head = tail = new BFSNode(stnidx, traininfo, nullptr);
			return;
		}
		tail->next = new BFSNode(stnidx, traininfo, nullptr);
		tail = tail->next;
	}
	BFSNode* pop(){
		BFSNode* temp = head;
		head = head->next;
		return temp;
	}
	bool isEmpty(){
		return (head == nullptr);
	}
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

    // insert your code here
    
    // cout << "This function is to be implemented by you." << endl;

    // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
    // for the source station and then we can print it out by invoking
    // printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of the Planner class
    // It is declared in planner.h and implemented in planner.cpp

	// first get the station indices from the station names
    auto srcstnidx = stnNameToIndex.get(srcStnName)->value;
    auto deststnidx = stnNameToIndex.get(destStnName)->value;

	// initalise the directjrnys object meant to store the direct journey codes
	listOfObjects<TrainInfoPerStation *> *directjrnys = new listOfObjects<TrainInfoPerStation *>(new TrainInfoPerStation(0,0,0,0)); // garbage value initialisation, will be removed at the end
	auto currdjrny = directjrnys; // iterator

	BFSQueue bfsq; // BFS Queue
	{ 	// initialise the  bfs queue
		auto adjstn = adjacency[srcstnidx].toStations; // adjacent satations to source
		while(adjstn!=nullptr){
			auto adjtrain = adjstn->object->trains; // trains at this edge
			while(adjtrain != nullptr){
				// insert to queue
				bfsq.insert(adjstn->object->adjacentStnIndex, adjtrain->object);
				adjtrain = adjtrain->next;
			}
			adjstn = adjstn->next;
		}
	}

	// do BFS
	while(!bfsq.isEmpty()){
		auto currnode =  bfsq.pop(); // get first element of the queue
		if(currnode->stnidx == deststnidx){
			// if destination, then add to directjourneys linked list
			currdjrny->next = new listOfObjects<TrainInfoPerStation *>(currnode->traininfo);
			currdjrny->next->prev = currdjrny;
			currdjrny = currdjrny->next;
		}
		else{
			// add the next edge of that journey to queue

			auto adjstn = adjacency[currnode->stnidx].toStations; // adjacent satations to curr (next possible edge)
			auto currjrnycode = currnode->traininfo->journeyCode; // current journey code

			bool found = false; // var to break from double while loop
			while(adjstn !=nullptr){
				auto adjtrain = adjstn->object->trains; // trains at this edge
				while(adjtrain != nullptr){
					if (adjtrain->object->journeyCode == currjrnycode){
						// if found the next edge, add to queue
						bfsq.insert(adjstn->object->adjacentStnIndex, adjtrain->object);
						found = true;
						break;
					}
					adjtrain = adjtrain->next;
				}
				if(found) break;
				adjstn = adjstn->next;
			}
		}
	}

	// delete the garbage head of directjrnys
	{
		auto temp = directjrnys;
		directjrnys = directjrnys->next;
		delete temp;
	}

	if(directjrnys == nullptr){
		cout<<"No direct journeys available"<<endl; return;
	}
	
	directjrnys->prev == nullptr;

	// now change the TrainStationInfo in accordance with the departure arrival time at source
	currdjrny = directjrnys; // iterator
	while(currdjrny != nullptr){
		auto currtrains = stationInfo[srcstnidx]; // trains from/to source
		auto currjrnycode = currdjrny->object->journeyCode; // journey code required

		while(currtrains!= nullptr){
			if(currtrains->object->journeyCode == currjrnycode){
				// when found, break out of the loop
				break;
			}
			currtrains = currtrains->next;
		}
		// now update to new value
		currdjrny->object = currtrains->object;
		currdjrny = currdjrny->next;
	}

	// now call printStationInfo
	printStationInfo(directjrnys);
    return;
}


// ************************ DFS approach ********************************** //
// since we want all journeys bfs has no advantage than dfs
// dfs is actually better than the bfs which is meant to be used as dfs uses less space(no queue required)
// this implementation is iterative dfs as we know that each journey is a path
// so just path traversal

/*
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

    // insert your code here
    
    // cout << "This function is to be implemented by you." << endl;

    // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
    // for the source station and then we can print it out by invoking
    // printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of the Planner class
    // It is declared in planner.h and implemented in planner.cpp

    auto srcstnidx = stnNameToIndex.get(srcStnName)->value;
    auto deststnidx = stnNameToIndex.get(destStnName)->value;

	auto currtrain = stationInfo[srcstnidx];

	listOfObjects<TrainInfoPerStation *> *directjrnys = new listOfObjects<TrainInfoPerStation *>(new TrainInfoPerStation(0,0,0,0));
	auto currdjrny = directjrnys;

	while(currtrain!=nullptr){
		if(currtrain->object->depTime != -1){
			auto currjrnycode = currtrain->object->journeyCode;
			auto currstnidx = srcstnidx;
			while (true){
				if(currstnidx == deststnidx){
					currdjrny->next = new listOfObjects<TrainInfoPerStation *>(currtrain->object);
					currdjrny->next->prev = currdjrny;
					currdjrny = currdjrny->next;
					break;
				}
				auto adjstn = adjacency[currstnidx].toStations;

				bool found = false;
				while(adjstn!=nullptr){
					auto adjtrain = adjstn->object->trains;
					while(adjtrain != nullptr){
						if (adjtrain->object->journeyCode == currjrnycode){
							currstnidx = adjstn->object->adjacentStnIndex; 
							found = true;
							break;
						}
						adjtrain = adjtrain->next;
					}
					if(found) break;
					adjstn = adjstn->next;
				}
				if(!found) break;
			}
		}
		currtrain = currtrain->next;
	}
	printStationInfo(directjrnys);
    return;
}
*/

#endif
