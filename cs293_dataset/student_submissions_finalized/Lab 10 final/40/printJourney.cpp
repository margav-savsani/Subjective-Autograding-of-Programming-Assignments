#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif
#include <cassert>

using namespace std;

#define COLORBLUE "\033[34m"
#define COLORYELLOW "\033[33m"
#define RESET "\033[0m"
#define COLORPURPLE "\033[35m"


class JourneyAndStation{
	public:
		int stnIndex;
		TrainInfoPerStation *jrny;

		JourneyAndStation(int stnI, TrainInfoPerStation *train){
			stnIndex = stnI;
			jrny = train;
		}
};

class AllAboutJourney{
	public:
		int stnIndex;
		int stopOvers;
		listOfObjects<JourneyAndStation *> *cumulative;

		AllAboutJourney(){
			stnIndex = -1;
			stopOvers = -1;
			cumulative = nullptr;
		}

		AllAboutJourney(int stnI, int totalstops){
			stnIndex = stnI;
			stopOvers = totalstops;
			cumulative = nullptr;
		}

		AllAboutJourney(int stnI, int totalstops, listOfObjects<JourneyAndStation *> *listptr){
			stnIndex = stnI;
			stopOvers = totalstops;
			cumulative = listptr;
		}
};


template <typename T>
class Q{
	listOfObjects<T> *head; 
	listOfObjects<T> *tail; 
	int size;				
public:
	Q(){
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	
	void push(T x){
		if (head == nullptr){
			head = new listOfObjects<T>(x);
			tail = head;
			size++;
		}
		else{
			tail->next = new listOfObjects<T>(x);
			tail = tail->next;
			size++;
		}
	}

	void pop(){
		if (head == nullptr) return;
		else{
			listOfObjects<T> *temp = head->next;
			head = temp;
			if (head == nullptr) tail = nullptr;
			else head->prev = nullptr;
			
			size--;
		}
	}

	T front(){
		return head->object;
	}

	bool empty(){
		return size == 0;
	}
};

template <typename T>
void insertAtHead(listOfObjects<T> *&pointer, T var){
	if (pointer == nullptr) pointer = new listOfObjects<T>(var);

	else{
		listOfObjects<T> *tempo = pointer;
		pointer = new listOfObjects<T>(var);
		pointer->next = tempo;
		tempo->prev = pointer;
	}
}

template <typename T>
void insertAtTail(listOfObjects<T> *&pointer, T var){
	if (pointer == nullptr) pointer = new listOfObjects<T>(var);
	
	else{
		listOfObjects<T> *tempo = pointer;
		while (tempo->next != nullptr){
			tempo = tempo->next;
		}
		tempo->next = new listOfObjects<T>(var);
		tempo->next->prev = tempo;
	}
}

listOfObjects<TrainInfoPerStation *> *separator(listOfObjects<TrainInfoPerStation *> *pointer){

	listOfObjects<TrainInfoPerStation *> *tempo = pointer;
	listOfObjects<TrainInfoPerStation *> *list = nullptr;

	while (tempo != nullptr){
		int jC = tempo->object->journeyCode;
		int sS = tempo->object->stopSeq;
		int aT = tempo->object->arrTime;
		int dT = tempo->object->depTime;

		for (int i = 0; i < 7; ++i){
			if (tempo->object->daysOfWeek[i]){
				TrainInfoPerStation *journey = new TrainInfoPerStation(jC, sS, aT, dT);
				journey->setDayOfWeek(i);
				insertAtHead(list, journey);
			}
		}
		tempo = tempo->next;
	}
	return list;
}

listOfObjects<TrainInfoPerStation *> *srcSeparator(listOfObjects<TrainInfoPerStation *> *pointer){
	
	listOfObjects<TrainInfoPerStation *> *list = nullptr;
	listOfObjects<TrainInfoPerStation *> *tempo = pointer;
	listOfObjects<TrainInfoPerStation *> *temp2 = pointer;

	int count = 0;

	while (temp2 != nullptr){
		count++;
		temp2 = temp2->next;
	}

	while (tempo != nullptr){
		int jC = tempo->object->journeyCode;
		int sS = tempo->object->stopSeq;
		int aT = tempo->object->arrTime;
		int dT = tempo->object->depTime;

		if (dT == -1){
			tempo = tempo->next;
			continue;
		}
		for (int i = 0; i < 7; ++i){
			if (tempo->object->daysOfWeek[i]){
				TrainInfoPerStation *journey = new TrainInfoPerStation(jC, sS, aT, dT);
				journey->setDayOfWeek(i);
				insertAtHead(list, journey);
			}
		}
		tempo = tempo->next;
	}
	count = 0;

	listOfObjects<TrainInfoPerStation *> *test = list;

	while (test != nullptr)
	{
		count++;
		test = test->next;
	}
	return list;
}

bool Intersect(int day1, int day2, int time1, int time2, int max){

	int difftime = (2400 + time2 - time1) % 2400;
	int diffday = (7 + day2 - day1) % 7;

	if (difftime == 0) diffday++;
	
	int timebtw = diffday * 2400 + difftime;

	return timebtw <= max;
}

void initialPusher(Q<AllAboutJourney *> *queue, listOfObjects<TrainInfoPerStation *> *prunedJrnies, int stnIndx){

	listOfObjects<TrainInfoPerStation *> *pointer = prunedJrnies;
	int count = 0;

	while (pointer != nullptr){
		TrainInfoPerStation *goodjourney = new TrainInfoPerStation(pointer->object->journeyCode, pointer->object->stopSeq, pointer->object->arrTime, pointer->object->depTime);

		for (int i = 0; i < 7; ++i){
			if (pointer->object->daysOfWeek[i]) goodjourney->setDayOfWeek(i);
		}

		JourneyAndStation *newObj = new JourneyAndStation(stnIndx, goodjourney);
		listOfObjects<JourneyAndStation *> *newList = new listOfObjects<JourneyAndStation *>(newObj);
		AllAboutJourney *temp = new AllAboutJourney(stnIndx, 0, newList);
		queue->push(temp);
		pointer = pointer->next;
		count++;
	}
	
}

string day(int i){
	
	switch(i) {
		case 0 :
			return "Monday";
			break;
		case 1 :
			return "Tuesday";
			break;
		case 2 :
			return "Wednesday";
			break;
		case 3 :
			return "Thursday";
			break;
		case 4 :
			return "Friday";
			break;
		case 5 :
			return "Saturday";
			break;
		case 6 :
			return "Sunday";
			break;
	}
}

bool offset(TrainInfoPerStation *a, TrainInfoPerStation *b){
	for (int i = 0; i < 7; ++i){
		if (a->daysOfWeek[i] != b->daysOfWeek[i]){
			return true;
		}
	}
	return false;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){
	int srcIndex = stnNameToIndex.get(srcStnName)->value;
	int destIndex = stnNameToIndex.get(destStnName)->value;

	listOfObjects<TrainInfoPerStation *> *prunedSrcJournies = srcSeparator(stationInfo[srcIndex]);
	Q<AllAboutJourney *> *q = new Q<AllAboutJourney *>;

	initialPusher(q, prunedSrcJournies, srcIndex);

	while (q->empty() != true){
		AllAboutJourney *now = q->front();

		if (now->stnIndex == destIndex){
			cout << "### Journey" << endl;

			listOfObjects<JourneyAndStation *> *print = now->cumulative;
			int d;

			for (int j = 0; j < 7; j++){
				if (print->object->jrny->daysOfWeek[j]){
					d = j;
				}
			}
			cout << COLORPURPLE << "Departs JC: " << print->object->jrny->journeyCode << " " << COLORBLUE << stnNameToIndex.getKeyAtIndex(print->object->stnIndex) << COLORYELLOW << " " << day(d) << " " << print->object->jrny->depTime << RESET << " | ";

			listOfObjects<JourneyAndStation *> *prevPrint = now->cumulative;
			print = print->next;

			while (print != nullptr){
				if (print->object->jrny->journeyCode == prevPrint->object->jrny->journeyCode){
					print = print->next;
					prevPrint = prevPrint->next;
					continue;
				}
				for (int k = 0; k < 7; k++){
					if (prevPrint->object->jrny->daysOfWeek[k]){
						d = k;
					}
				}
				cout << COLORPURPLE << "Arrives " << COLORBLUE << stnNameToIndex.getKeyAtIndex(prevPrint->object->stnIndex) << COLORYELLOW << " " << day(d) << " " << prevPrint->object->jrny->arrTime << RESET << endl;

				for (int i = 0; i < 7; ++i){
					if (print->object->jrny->daysOfWeek[i]){
						d = i;
					}
				}
				cout << COLORPURPLE << "Departs JC: " << print->object->jrny->journeyCode << " " << COLORBLUE << stnNameToIndex.getKeyAtIndex(prevPrint->object->stnIndex) << COLORYELLOW << " " << day(d) << " " << prevPrint->object->jrny->depTime << RESET << " | ";

				print = print->next;
				prevPrint = prevPrint->next;
			}
			cout << COLORPURPLE << "Arrives " << COLORBLUE << stnNameToIndex.getKeyAtIndex(prevPrint->object->stnIndex) << COLORYELLOW << " " << day(d) << " " << prevPrint->object->jrny->arrTime << RESET << endl;
			cout << endl;
			q->pop();
			continue;
		}

		{
			int currStnIndx = now->stnIndex;
			listOfObjects<JourneyAndStation *> *ptr = now->cumulative;

			while (ptr->next != nullptr){
				ptr = ptr->next;
			}
			listOfObjects<StationConnectionInfo *> *outward = adjacency[currStnIndx].toStations;

			while (outward != nullptr){
				int adjStnIndx = outward->object->adjacentStnIndex;
				listOfObjects<TrainInfoPerStation *> *outTrains = separator(outward->object->trains);
				printStationInfo(outTrains);

				while (outTrains != nullptr){
					int jC = outTrains->object->journeyCode;
					int time1 = ptr->object->jrny->arrTime;
					int day1;

					for (int a = 0; a < 7; a++){
						if (ptr->object->jrny->daysOfWeek[a]){
							day1 = a;
						}
					}
					int time2 = outTrains->object->depTime;
					int day2;

					for (int i = 0; i < 7; ++i){
						if (outTrains->object->daysOfWeek[i]){
							day2 = i;
						}
					}

					if (outTrains->object->journeyCode == ptr->object->jrny->journeyCode){
						if (now->stnIndex == srcIndex || true){
							int i1, i2;
							for (int i = 0; i < 7; ++i){
								if (ptr->object->jrny->daysOfWeek[i]) i2 = i;
								
								if (outTrains->object->daysOfWeek[i]) i1 = i;
							}
							if (i1 != i2){
								outTrains = outTrains->next;
								continue;
							}
						}
						listOfObjects<JourneyAndStation *> *tempPtr = now->cumulative;
						listOfObjects<JourneyAndStation *> *buildNew = nullptr;

						while (tempPtr != nullptr){
							int indx = tempPtr->object->stnIndex;
							TrainInfoPerStation *t = tempPtr->object->jrny;
							TrainInfoPerStation *newtrain = new TrainInfoPerStation(t->journeyCode, t->stopSeq, t->arrTime, t->depTime);

							for (int i = 0; i < 7; ++i){
								if (t->daysOfWeek[i]){
									newtrain->setDayOfWeek(i);
								}
							}
							JourneyAndStation *newentry = new JourneyAndStation(indx, newtrain);
							insertAtTail<JourneyAndStation *>(buildNew, newentry);
							tempPtr = tempPtr->next;
						}
						listOfObjects<StationConnectionInfo *> *m = adjacency[adjStnIndx].fromStations;

						while (m->object->adjacentStnIndex != currStnIndx){
							m = m->next;
						}

						listOfObjects<TrainInfoPerStation *> *n = m->object->trains;

						while (n->object->journeyCode != outTrains->object->journeyCode){
							n = n->next;
						}

						TrainInfoPerStation *t = n->object;
						TrainInfoPerStation *newtrain = new TrainInfoPerStation(t->journeyCode, t->stopSeq, t->arrTime, t->depTime);
						listOfObjects<StationConnectionInfo *> *pp = outward;

						while (pp->object->adjacentStnIndex != adjStnIndx){
							pp = pp->next;
						}
						listOfObjects<TrainInfoPerStation *> *bb = pp->object->trains;

						while (bb->object->journeyCode != outTrains->object->journeyCode){
							bb = bb->next;
						}

						bool isoff = offset(t, bb->object);

						for (int i = 0; i < 7; ++i){
							if (outTrains->object->daysOfWeek[i]){

								if (isoff) newtrain->setDayOfWeek((i + 1) % 7);
							
								else newtrain->setDayOfWeek(i);
							}
						}
						JourneyAndStation *newentry = new JourneyAndStation(adjStnIndx, newtrain);
						insertAtTail<JourneyAndStation *>(buildNew, newentry);
						AllAboutJourney *pushing = new AllAboutJourney(adjStnIndx, now->stopOvers, buildNew);
						q->push(pushing);
					}

					else{
						if (now->stnIndex == srcIndex){
							outTrains = outTrains->next;
							continue;
						}

						if (now->stopOvers + 1 > maxStopOvers){
							outTrains = outTrains->next;
							continue;
						}

						bool checkintersect = Intersect(day1, time1, day2, time2, maxTransitTime);

						if (checkintersect){
							listOfObjects<JourneyAndStation *> *tempPtr = now->cumulative;
							listOfObjects<JourneyAndStation *> *buildNew = nullptr;

							while (tempPtr != nullptr){
								int indx = tempPtr->object->stnIndex;
								TrainInfoPerStation *t = tempPtr->object->jrny;
								TrainInfoPerStation *newtrain = new TrainInfoPerStation(t->journeyCode, t->stopSeq, t->arrTime, t->depTime);

								if (tempPtr->next == nullptr) newtrain->depTime = outTrains->object->depTime;
								
								for (int i = 0; i < 7; ++i){
									if (t->daysOfWeek[i]) newtrain->setDayOfWeek(i);
								}
								JourneyAndStation *newentry = new JourneyAndStation(indx, newtrain);
								insertAtTail<JourneyAndStation *>(buildNew, newentry);
								tempPtr = tempPtr->next;
							}

							listOfObjects<StationConnectionInfo *> *m = adjacency[adjStnIndx].fromStations;

							while (m->object->adjacentStnIndex != currStnIndx){
								m = m->next;
							}
							listOfObjects<TrainInfoPerStation *> *n = m->object->trains;

							while (n->object->journeyCode != outTrains->object->journeyCode){
								n = n->next;
							}

							TrainInfoPerStation *t = n->object;
							TrainInfoPerStation *newtrain = new TrainInfoPerStation(t->journeyCode, t->stopSeq, t->arrTime, t->depTime);
							listOfObjects<StationConnectionInfo *> *pp = outward;

							while (pp->object->adjacentStnIndex != adjStnIndx){
								pp = pp->next;
							}

							listOfObjects<TrainInfoPerStation *> *bb = pp->object->trains;

							while (bb->object->journeyCode != outTrains->object->journeyCode){
								bb = bb->next;
							}
							bool isoff = offset(t, bb->object);

							for (int i = 0; i < 7; ++i){
								if (outTrains->object->daysOfWeek[i]){
									if (isoff) newtrain->setDayOfWeek((i + 1) % 7);
									else newtrain->setDayOfWeek(i);
								}
							}
							JourneyAndStation *newentry = new JourneyAndStation(adjStnIndx, newtrain);
							insertAtTail<JourneyAndStation *>(buildNew, newentry);
							AllAboutJourney *pushing = new AllAboutJourney(adjStnIndx, now->stopOvers + 1, buildNew);
							q->push(pushing);
							
						}
					}
					outTrains = outTrains->next;
				}
				outward = outward->next;
			}
		}
		q->pop();
	}
	return;
}
#endif
