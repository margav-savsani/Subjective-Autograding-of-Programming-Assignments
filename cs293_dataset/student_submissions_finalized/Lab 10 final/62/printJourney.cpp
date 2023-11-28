#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#ifndef CODES_H
#include "codes.h"
#endif

using namespace std;
  
template <typename T>
class Deque{ //Deque wrapper over list of objects
	listOfObjects<T>* head;
	listOfObjects<T>* tail;
	bool isempty; // true if empty
	public:
		Deque(){//def constructor
			head = tail = nullptr;
			isempty = true;
		}
		//insert element into queue
		bool push(listOfObjects<T>* element){
			if (element==nullptr) return false;//invalid
			if (isempty){ // first insert to empty queue
				head = tail = element;
				head -> next = head->prev = nullptr;
				isempty = false;
				return true;
			}
			tail->next = element; //regular insertion
			element->prev = tail;
			element->next = nullptr;
			tail = element;
			return true;
		}
		bool push(T element){ // push with different signature
			return push(new listOfObjects<T>(element));
		}
		//check if queue is empty, reqs for bfs loop
		bool isEmpty() {
			return isempty;
		}
		// return ll starting at head, required for printing
		listOfObjects<T>* getHead(){
			return this->head;
		}// return tail node 
		listOfObjects<T>* getTail(){
			return this->tail;
		}
		// remove head and return element, queue-like
		listOfObjects<T>* popAtHead(){ // they shall deal with the memory
			if (isempty) return nullptr;//invalid
			listOfObjects<T>* curr = head;
			head = head->next;
			if (head==nullptr) isempty=true;
			else head->prev=nullptr;
			curr->next = nullptr;
			return curr;
		}
		//remove tail and return it, stack-like
		listOfObjects<T>* popAtTail(){
			if (isempty) return nullptr;//invalid
			listOfObjects<T>* curr = tail;
			tail = tail->prev;
			if (tail==nullptr) isempty = true;// check if popper list empty
			else tail->next = nullptr;
			curr->prev = nullptr;
			return curr;
		}
};


struct journey{ // struct containing the important info of the journey
	
	TrainInfoPerStation* current; // traininfoperstation corresponding to that journey
	int fromstnindex; // index of station travelling from
	int tostnindex;// index of station travelling to
	unsigned int intermediate_stops; // no of intermediate stops until that point
	int jcode;// journeycode

	journey(){
		current = nullptr;
		intermediate_stops=0;
		jcode=tostnindex= fromstnindex = -1;
	}
	journey(TrainInfoPerStation* _current, int _tostnindex,int _fromstnindex ,  unsigned int _intermediate_stops){
		current=_current;
		tostnindex=_tostnindex;
		fromstnindex=_fromstnindex;
		intermediate_stops=_intermediate_stops;
		jcode=current->journeyCode;
	}
	~journey(){
		delete current;
	}
};

//split train into multiple days - required for calculating times
Deque<TrainInfoPerStation*>* SplitStationInfo(TrainInfoPerStation *jInfo)
{
	Deque<TrainInfoPerStation*>* expandedq = new Deque<TrainInfoPerStation*>();
	
	if (jInfo != nullptr) {
		// Make as many copies of jInfo as the total count of days in the week
		// when this train runs from/to this station
		int jCode = jInfo->journeyCode;
		int stSeq = jInfo->stopSeq;
		int arrTime = jInfo->arrTime;
		int depTime = jInfo->depTime;
		
		for (int i=0; i < 7; i++) {
			if (jInfo->daysOfWeek[i]) {		
				TrainInfoPerStation* newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);		
				newExpandedElement->setDayOfWeek(i);
				expandedq->push(newExpandedElement);
			}
		}
	}
	return expandedq;
}
// return wait time between two journeys given
int wait(TrainInfoPerStation* From, TrainInfoPerStation* To){
	int fday,tday;
	for(fday=0;fday<7&&!From->daysOfWeek[fday];fday++){}
	for(tday=0;tday<7&&!To->daysOfWeek[tday];tday++){}

	int wait =(tday-fday)*(60*24)+(To->arrTime/100-From->depTime/100)*60+(To->arrTime%100-From->depTime%100);
	return (wait<0?wait+60*24*7:wait);
}
//different signature
int wait(int fday, int fromdeptime, int tday,  int toarrtime){
	int wait =(tday-fday)*(60*24)+(toarrtime/100-fromdeptime/100)*60+(toarrtime%100-fromdeptime%100);
	return (wait<0?wait+60*24*7:wait);
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
	static string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}; // num to day converter
	static Deque<journey*> DFSStack = Deque<journey*>(); // stack containing journey history
	static int reclevel = -1;//recursion level

	reclevel++;
	int currentindex = (DFSStack.isEmpty()?(stnNameToIndex.get(srcStnName)->value):DFSStack.getTail()->object->tostnindex);
	if (currentindex==stnNameToIndex.get(destStnName)->value){ // reached destination
		int prevj = -1;
		cout<<'\n'<<RED<<"Journey Found! \n"<<RESET;
		for (listOfObjects<journey*>* currlist=DFSStack.getHead();currlist != nullptr;currlist = currlist->next) {
			journey* currInfo = currlist->object;
			if (currInfo != nullptr&&(prevj!=currInfo->jcode||wait(currlist->prev->object->current,currInfo->current)<24*60)) {
				prevj=currInfo->jcode;
				cout << GREEN << "Day: " << RESET;
				for (int i=0; i<7; i++) {
					if (currInfo->current->daysOfWeek[i]) {
						cout << days[i] << '\n';
						break;
					}
				}
				cout<<BLUE<<"From "<<RESET<<stnNameToIndex.getKeyAtIndex(currInfo->fromstnindex)<<BLUE<<" To "<<RESET<<stnNameToIndex.getKeyAtIndex(currInfo->tostnindex)<<'\n';
				cout << GREEN << "JourneyCode: " << currInfo->jcode << RESET << "\t";
				cout << RED << "Arr: " << RESET;
				if (currInfo->current->arrTime == -1) cout << "Starts";
				else cout << currInfo->current->arrTime;
				cout << RED << " Dep: " << RESET;
				if (currInfo->current->depTime == -1) cout << "Ends"; 
				else cout << currInfo->current->depTime;
				cout << endl;
			}			
		}
		//journey* latest = DFSStack.getTail()->object;
	}
	else if (reclevel==0){// when DFS starts empty
		for(listOfObjects<StationConnectionInfo *>* sci = adjacency[currentindex].toStations; sci!=nullptr ;sci = sci ->next){ // corresponding to each station the train is travelling
			for (listOfObjects<TrainInfoPerStation*>* tips = sci->object->trains;tips!=nullptr;tips=tips->next){// corresponding to each traincode
				Deque<TrainInfoPerStation*>* Q = SplitStationInfo(tips->object); // corresponding to each individual day-journey
				while(!Q->isEmpty()){ //for each possibility
					listOfObjects<TrainInfoPerStation*>* Qel = Q->popAtHead();
					TrainInfoPerStation* el = Qel->object; 
					//pushing to stack
					DFSStack.push(new journey(el,sci->object->adjacentStnIndex,stnNameToIndex.get(srcStnName)->value,0));
					printPlanJourneys(srcStnName, destStnName,maxStopOvers,maxTransitTime);//recursive call
					listOfObjects<journey*>* td = DFSStack.popAtTail();//poppoing from stack
					delete td->object;//mem management
					delete td;					
					delete Qel;					
				}
				delete Q; // freeempty Q
			}
		}
	}
	else{ // DFS has non empty element in it
		TrainInfoPerStation* arrjourney; // corresponding to the previous jounrye at destination 

		journey* latest = DFSStack.getTail()->object;// most recent journey, we will find the relevant timestamps at the new place
		int day =0;//day of latest
		for (day =0 ;!latest->current->daysOfWeek[day];day++){}
		//finding the arrival time of the previous journey
		for(listOfObjects<StationConnectionInfo* >* arr = adjacency[currentindex].fromStations;arr!=nullptr;arr=arr->next){
			if (arr->object->adjacentStnIndex==latest->fromstnindex){

				for (listOfObjects<TrainInfoPerStation*>* arrivals = arr->object->trains;arrivals!=nullptr;arrivals=arrivals->next){
					if (arrivals->object->journeyCode==latest->jcode){ // relevant journey
						arrjourney = new TrainInfoPerStation(latest->current->journeyCode,latest->current->stopSeq,arrivals->object->arrTime,arrivals->object->depTime);
						if (arrivals->object->arrTime<=latest->current->depTime){
							arrjourney->setDayOfWeek((day+1)%7); // train went overnight
						}
						else{
							arrjourney->setDayOfWeek(day); //train on same day
						}
					break;
					}

				}
				break;
			}
		}
		//look at nextpossible journeys
		for(listOfObjects<StationConnectionInfo *>* sci = adjacency[currentindex].toStations; sci!=nullptr ;sci = sci->next){
			for (listOfObjects<TrainInfoPerStation*>* tips = sci->object->trains;tips!=nullptr;tips=tips->next){
				if (maxStopOvers!=latest->intermediate_stops||!(latest->jcode==tips->object->journeyCode)){
					Deque<TrainInfoPerStation*>* Q = SplitStationInfo(tips->object);
					while(!Q->isEmpty()){
						listOfObjects<TrainInfoPerStation*>* Qel = Q->popAtHead();// possible journeys for given train
						TrainInfoPerStation* el = Qel->object;  

						if (latest->jcode==el->journeyCode&&wait(arrjourney,el)<24*60){ // same train
						//threshold for wait kept arbitrarily, howeer it will catch all
							DFSStack.push(new journey(el,sci->object->adjacentStnIndex,latest->tostnindex,latest->intermediate_stops));
							printPlanJourneys(srcStnName, destStnName,maxStopOvers,maxTransitTime);//call recursively
							listOfObjects<journey*>* td = DFSStack.popAtTail();
							delete td->object;
							delete td;//free
						}
						
						else if((latest->intermediate_stops<maxStopOvers&&wait(arrjourney,el)<=60*maxTransitTime) || latest->jcode==el->journeyCode){ //different trains
						// new stopover and wait time to check
							DFSStack.push(new journey(el,sci->object->adjacentStnIndex,latest->tostnindex,latest->intermediate_stops+1));
							printPlanJourneys(srcStnName, destStnName,maxStopOvers,maxTransitTime);// call recursively
							listOfObjects<journey*>* td = DFSStack.popAtTail();
							delete td->object;//free
							delete td;
						}
						delete Qel;
					}
					delete Q;
				}
			}
		}
		delete arrjourney;
	}
	reclevel--;

}
//*/
#endif
