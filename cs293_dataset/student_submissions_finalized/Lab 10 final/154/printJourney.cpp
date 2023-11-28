#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;


int to_mins(int t){
	// converts from 24hrs format to minutes
	return (t/100)*60 + t%100;
}
int to_24hrs(int t){
	// converts from minutes to 24hrs format
	return (t/60)*100 + t%60;
}

int transit_time(int t_arr, int d_arr, int t_dep, int d_dep){
	// calculate the transit time and returns in 24 hrs format
	// t_arr = time at which the person arrives at that station by prev train
	// t_dep = time at which the person departs from that station by new train
	// similarly d_dep, d_arr denotes respective day

	return to_24hrs(to_mins(t_dep) - to_mins(t_arr) + ((d_dep-d_arr + 7)%7)*24*60);
}

struct jrnyedge{
	// struct to store the inter-station travel details, also a node for jrnystack
	TrainInfoPerStation* srcstninfo;
	TrainInfoPerStation* endstninfo;
	int srcstnidx;
	int endstnidx;
	int daysrc;
	int dayend;
	
	jrnyedge *next, *prev;

	jrnyedge(TrainInfoPerStation* srcstninfo, TrainInfoPerStation* endstninfo, int srcstnidx, int endstnidx, int daysrc, int dayend, jrnyedge* next, jrnyedge* prev){
		this->srcstninfo = srcstninfo;
		this->endstninfo = endstninfo;
		this->srcstnidx = srcstnidx;
		this->endstnidx =endstnidx;
		this->daysrc = daysrc;
		this->dayend = dayend;
		this->next = next;
		this->prev = prev;
	}
};

struct jrnystack{
	// A simple stack of jrnyedge, used here to store the current path of dfs
	jrnyedge *head;
	jrnyedge *tail;
public:
	jrnystack(){
		head = tail = nullptr;
	}
	void insert(TrainInfoPerStation* srcstninfo, TrainInfoPerStation* endstninfo, int srcstnidx, int endstnidx, int daysrc, int dayend){
		if(head==nullptr){
			head = new jrnyedge(srcstninfo, endstninfo, srcstnidx, endstnidx, daysrc, dayend, nullptr, nullptr);
			tail = head;
			return;
		}

		head->prev = new jrnyedge(srcstninfo, endstninfo, srcstnidx, endstnidx, daysrc, dayend, head, nullptr);
		head = head->prev;
	}
	jrnyedge* pop(){
		jrnyedge* temp = head;
		head = head->next;
		if (head!= nullptr) head->prev = nullptr;
		else tail = nullptr;
		return temp;
	}
	bool isEmpty(){
		return (head == nullptr);
	}
	void print(Dictionary<int> *stnNameToIndex){
		// prints stack in a nice format
		string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
		jrnyedge* curr = tail;

		cout <<"\nJourney:\n" << RESET;
		cout<< BLUE << "Station: "<<stnNameToIndex->getKeyAtIndex(curr->srcstnidx)<<"\n";
		while(curr != nullptr){
			cout<< GREEN << "Train JourneyCode: " << curr->srcstninfo->journeyCode << "\t";
			cout<< RED<<"Departs: "<<days[curr->daysrc]<<", " <<curr->srcstninfo->depTime<<"\t";
			cout<<RED <<"Arrives: "<<days[curr->dayend]<<", " <<curr->endstninfo->arrTime<<"\n";
			cout<<BLUE <<"Station: "<<stnNameToIndex->getKeyAtIndex(curr->endstnidx);
			if(curr->prev != nullptr && curr->srcstninfo->journeyCode != curr->prev->srcstninfo->journeyCode){
				cout<< GREEN<<" with Transit time: "
				<< transit_time(curr->endstninfo->arrTime, curr->dayend, curr->prev->srcstninfo->depTime, curr->prev->daysrc);
			}
			cout<<"\n"<<RESET;
			curr = curr->prev;
		}
	}
	~jrnystack(){
		if(head==nullptr) return;
		auto curr = head->next;
		while(curr != nullptr){
			delete curr->prev;
			curr = curr->next;
		}
		delete tail;
	}
};

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
	// prints the journeys in a nice format using jrnystack::print() function

	/*Basic idea: 
		maintain a stack while running dfs and when we reach the end station print that info
	
		push an edge in the queue
		do recursive call
		pop that edge
	*/

	static jrnystack jrnys; // a stack used here to store the current path of dfs
	static int reclvl = -1; 
	static bool found = false; // any path found or not

	reclvl++;

	if(srcStnName == destStnName){ // print the journey stored in stack
		if(jrnys.isEmpty()){
			// case if we enter the same station as source and destination
			cout<<RED<<"\nNO JOURNEYS FOUND \n"<<RESET;
		}
		else{
			jrnys.print(&stnNameToIndex);
			found = true;
		}
		reclvl--;
		return;
	}

    auto srcstnidx = stnNameToIndex.get(srcStnName)->value;

	auto adjstn = adjacency[srcstnidx].toStations; // adjacent stations to source

	while(adjstn!=nullptr){
		auto adjtrain = adjstn->object->trains; // trains at this edge, has info wrt current station
		while(adjtrain != nullptr){
			for(int i=0; i<7; i++){ // trains arriving curr station on i'th day

				if(!adjtrain->object->daysOfWeek[i]) continue; // train doesn't run on that day

				auto nextstninfo = stationInfo[adjstn->object->adjacentStnIndex]; // info wrt the connected station
				while(nextstninfo != nullptr){
					if (nextstninfo->object->journeyCode == adjtrain->object->journeyCode){
						break;
					}
					nextstninfo = nextstninfo->next;
				}

				int d_arr_end = i; // arrival day at end/connected station of new edge
				if(adjtrain->object->arrTime > nextstninfo->object->arrTime) d_arr_end = (i+1)%7;

				int t_dep_src = adjtrain->object->depTime; 
				int d_dep_src = i; // departure day at curr station of new edge
				if(adjtrain->object->arrTime > adjtrain->object->depTime) d_dep_src = (i+1)%7;

				if(jrnys.isEmpty()){ // adding first edge to the jrnys
					jrnys.insert(adjtrain->object, nextstninfo->object, srcstnidx, adjstn->object->adjacentStnIndex, d_dep_src, d_arr_end);
					printPlanJourneys(stnNameToIndex.getKeyAtIndex(adjstn->object->adjacentStnIndex), destStnName, maxStopOvers, maxTransitTime);
					delete jrnys.pop();
				}

				else if(jrnys.head->endstninfo->journeyCode == adjtrain->object->journeyCode){
					// adding edge with same train (didn't change train physically)
					if(jrnys.head->dayend == i){
						jrnys.insert(adjtrain->object, nextstninfo->object, srcstnidx, adjstn->object->adjacentStnIndex, d_dep_src, d_arr_end);
						printPlanJourneys(stnNameToIndex.getKeyAtIndex(adjstn->object->adjacentStnIndex), destStnName, maxStopOvers, maxTransitTime);
						delete jrnys.pop();
					}
				}
				// else if(jrnys.head->endstninfo->journeyCode == adjtrain->object->journeyCode && jrnys.head->dayend == i){
				// 	jrnys.insert(adjtrain->object, nextstninfo->object, srcstnidx, adjstn->object->adjacentStnIndex, d_dep_src, d_arr_end);
				// 	printPlanJourneys(stnNameToIndex.getKeyAtIndex(adjstn->object->adjacentStnIndex), destStnName, maxStopOvers, maxTransitTime);
				// 	delete jrnys.pop();
				// }
				else if(maxStopOvers > 0){
					// if the person have stopovers left

					int t_arr_curr = jrnys.head->endstninfo->arrTime; // arrival time at currstation of prev edge
					int d_arr_curr = jrnys.head->dayend; 
					int waitime = transit_time(t_arr_curr, d_arr_curr, t_dep_src, d_dep_src);
					if(waitime >0 && to_mins(waitime) <= maxTransitTime*60){
						jrnys.insert(adjtrain->object, nextstninfo->object, srcstnidx, adjstn->object->adjacentStnIndex, d_dep_src, d_arr_end);
						printPlanJourneys(stnNameToIndex.getKeyAtIndex(adjstn->object->adjacentStnIndex), destStnName, maxStopOvers - 1, maxTransitTime);
						delete jrnys.pop();
					}
				}
				
			}
			adjtrain = adjtrain->next;
		}
		adjstn = adjstn->next;
	}
	reclvl--;
	if(reclvl == -1){
		if(!found){
			cout<<RED<<"\nNO JOURNEYS FOUND \n"<<RESET;
		}
		found = false;
	}
}

#endif
