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

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"

template <typename T>
class Q
{
	listOfObjects<T> *head; // pointer to head of queue
	listOfObjects<T> *tail; // pointer to tail of queue
	int size;				// size of queue

public:
	// constructor
	Q()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	// pushing new element at the tail of the queue
	void push(T x)
	{
		if (head == nullptr)
		{
			head = new listOfObjects<T>(x);
			tail = head;
			size++;
		}
		else
		{
			tail->next = new listOfObjects<T>(x);
			tail = tail->next;
			size++;
		}
	}

	// removing element from the head of the queue
	void pop()
	{
		if (head == nullptr)
		{
			return;
		}
		else
		{
			listOfObjects<T> *temp = head->next;
			// delete head;
			head = temp;

			if (head == nullptr)
			{
				tail = nullptr;
			}
			else
			{
				head->prev = nullptr;
			}

			size--;
		}
	}

	// returning element present at the head of the queue
	T front()
	{

		assert(head != nullptr);

		if (head != nullptr)
		{
			return head->object;
		}
	}

	// checking if the queue is empty
	bool empty()
	{
		return size == 0;
	}
};

// This class is a part of storing history of all the switching of trains
// A list of this class will be used to store the overall history
// contains a pointer to a train and a station index
class JourneyAndStation
{
public:
	int stnIndex;
	TrainInfoPerStation *jrny;

	JourneyAndStation(int sI, TrainInfoPerStation *ptr)
	{
		stnIndex = sI;
		jrny = ptr;
	}
};

// this class will be pushed into the queue
// this class contains the history of the journies encountered till now
// this class corresponds to a particular station denoted by station index
class AllAboutJourney
{
public:
	int stnIndex;
	int stopOvers;
	listOfObjects<JourneyAndStation *> *history;

	AllAboutJourney()
	{
		stnIndex = -1;
		stopOvers = -1;
		history = nullptr;
	}

	AllAboutJourney(int sI, int sO)
	{
		stnIndex = sI;
		stopOvers = sO;
		history = nullptr;
	}

	AllAboutJourney(int sI, int sO, listOfObjects<JourneyAndStation *> *ptr)
	{
		stnIndex = sI;
		stopOvers = sO;
		history = ptr;
	}
};

// helper function to insert at the head of listOfObjects
template <typename T>
void insertAtHead(listOfObjects<T> *&ptr, T x)
{
	if (ptr == nullptr)
	{
		ptr = new listOfObjects<T>(x);
	}
	else
	{
		listOfObjects<T> *temp = ptr;
		ptr = new listOfObjects<T>(x);
		ptr->next = temp;
		temp->prev = ptr;
	}
}

// helper function to insert at the tail of listOfObjects
template <typename T>
void insertAtTail(listOfObjects<T> *&ptr, T x)
{
	if (ptr == nullptr)
	{
		ptr = new listOfObjects<T>(x);
	}
	else
	{
		listOfObjects<T> *temp = ptr;

		while (temp->next != nullptr)
		{
			temp = temp->next;
		}

		temp->next = new listOfObjects<T>(x);
		temp->next->prev = temp;
	}
}

// this function separates a list of journeys into it's individual days
// separated journeys are also returned as a listOfObjects
listOfObjects<TrainInfoPerStation *> *separator(listOfObjects<TrainInfoPerStation *> *ptr)
{
	listOfObjects<TrainInfoPerStation *> *ret = nullptr;

	listOfObjects<TrainInfoPerStation *> *temp = ptr;

	while (temp != nullptr)
	{
		int jC = temp->object->journeyCode;
		int ss = temp->object->stopSeq;
		int aT = temp->object->arrTime;
		int dT = temp->object->depTime;

		for (int i = 0; i < 7; ++i)
		{
			if (temp->object->daysOfWeek[i])
			{
				TrainInfoPerStation *nuJrny = new TrainInfoPerStation(jC, ss, aT, dT);
				nuJrny->setDayOfWeek(i);

				insertAtHead(ret, nuJrny);
			}
		}

		temp = temp->next;
	}

	return ret;
}

// this does the same work as the separator function above but for the source station
// it has a slight modification that all the trains which end at source station are removed from the list
listOfObjects<TrainInfoPerStation *> *srcSeparator(listOfObjects<TrainInfoPerStation *> *ptr)
{
	listOfObjects<TrainInfoPerStation *> *ret = nullptr;

	listOfObjects<TrainInfoPerStation *> *temp = ptr;

	listOfObjects<TrainInfoPerStation *> *lmao = ptr;

	int count = 0;

	while (lmao != nullptr)
	{
		count++;
		lmao = lmao->next;
	}

	while (temp != nullptr)
	{
		int jC = temp->object->journeyCode;
		int ss = temp->object->stopSeq;
		int aT = temp->object->arrTime;
		int dT = temp->object->depTime;

		if (dT == -1)
		{
			temp = temp->next;
			continue;
		}

		for (int i = 0; i < 7; ++i)
		{
			if (temp->object->daysOfWeek[i])
			{
				TrainInfoPerStation *nuJrny = new TrainInfoPerStation(jC, ss, aT, dT);
				nuJrny->setDayOfWeek(i);

				insertAtHead(ret, nuJrny);
			}
		}

		temp = temp->next;
	}

	count = 0;

	listOfObjects<TrainInfoPerStation *> *test = ret;

	while (test != nullptr)
	{
		count++;
		test = test->next;
	}

	return ret;
}

// pushes all the journies beginning from the source station
// listOfObjects created by above function is fed into this function
void initialPusher(Q<AllAboutJourney *> *q, listOfObjects<TrainInfoPerStation *> *prunedJrnies, int stnIndx)
{
	listOfObjects<TrainInfoPerStation *> *ptr = prunedJrnies;

	int count = 0;

	while (ptr != nullptr)
	{
		TrainInfoPerStation *okJrny = new TrainInfoPerStation(ptr->object->journeyCode, ptr->object->stopSeq, ptr->object->arrTime, ptr->object->depTime);

		for (int i = 0; i < 7; ++i)
		{
			if (ptr->object->daysOfWeek[i])
			{
				okJrny->setDayOfWeek(i);
			}
		}

		JourneyAndStation *newObj = new JourneyAndStation(stnIndx, okJrny);

		listOfObjects<JourneyAndStation *> *newList = new listOfObjects<JourneyAndStation *>(newObj);

		AllAboutJourney *temp = new AllAboutJourney(stnIndx, 0, newList);
		q->push(temp);

		ptr = ptr->next;

		count++;
	}
}

// checks if 2 times are less than max allowed time or not
bool checkIntersection(int day1, int time1, int day2, int time2, int max)
{
	int min1 = time1 % 100;
	int min2 = time2 % 100;

	int hr1 = time1 - min1;
	int hr2 = time2 - min2;

	int t1prime = hr1 + (100.0 / 60.0) * min1;
	int t2prime = hr2 + (100.0 / 60.0) * min2;

	int dt = (2400 + t2prime - t1prime) % 2400;

	int mindt = dt % 100;
	int hrdt = dt - mindt;

	dt = hrdt + (60.0 / 100.0) * mindt;

	int dd = (7 + day2 - day1) % 7;

	if (t1prime > t2prime)
	{
		dd--;
	}

	int timeBW = dd * 2400 + dt;

	if (timeBW <= max)
		return true;
	else
		return false;
}

// calculates the difference between two times
int transitTime(int day1, int time1, int day2, int time2)
{

	int min1 = time1 % 100;
	int min2 = time2 % 100;

	int hr1 = time1 - min1;
	int hr2 = time2 - min2;

	int t1prime = hr1 + (100.0 / 60.0) * min1;
	int t2prime = hr2 + (100.0 / 60.0) * min2;

	int dt = (2400 + t2prime - t1prime) % 2400;

	int mindt = dt % 100;
	int hrdt = dt - mindt;

	dt = hrdt + (60.0 / 100.0) * mindt;

	int dd = (7 + day2 - day1) % 7;

	if (t1prime > t2prime)
	{
		dd--;
	}

	int timeBW = dd * 2400 + dt;

	return timeBW;
}

// returns day of the week corresponding to the number
string day(int i)
{
	if (i == 0)
	{
		return "Monday";
	}

	if (i == 1)
	{
		return "Tuesday";
	}

	if (i == 2)
	{
		return "Wednesday";
	}

	if (i == 3)
	{
		return "Thursday";
	}

	if (i == 4)
	{
		return "Friday";
	}

	if (i == 5)
	{
		return "Saturday";
	}

	if (i == 6)
	{
		return "Sunday";
	}
}

// to check if the train reaches on the same day or next day
bool offset(TrainInfoPerStation *a, TrainInfoPerStation *b)
{
	for (int i = 0; i < 7; ++i)
	{
		if (a->daysOfWeek[i] != b->daysOfWeek[i])
		{
			return true;
		}
	}

	return false;
}

// I have used BFS for this assignment
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
	// getting indices of source and destination stations
	int srcIndex = stnNameToIndex.get(srcStnName)->value;
	int destIndex = stnNameToIndex.get(destStnName)->value;

	bool isAnyJourney = false;

	// pruning and expanding the journies from source station
	listOfObjects<TrainInfoPerStation *> *prunedSrcJournies = srcSeparator(stationInfo[srcIndex]);

	// queue to implement BFS
	Q<AllAboutJourney *> *q = new Q<AllAboutJourney *>;

	// pushing the journies from source station
	initialPusher(q, prunedSrcJournies, srcIndex);

	// the actual BFS
	while (q->empty() != true)
	{
		// getting the element at the front
		AllAboutJourney *now = q->front();

		// if we reach destination then print the journies in appropriate format
		if (now->stnIndex == destIndex)
		{
			{
				listOfObjects<JourneyAndStation *> *print = now->history;

				int d;

				for (int i = 0; i < 7; ++i)
				{
					if (print->object->jrny->daysOfWeek[i])
					{
						d = i;
					}
				}


				listOfObjects<JourneyAndStation *> *prevPrint = now->history;
				print = print->next;

				bool y = false;

				while (print != nullptr)
				{
					if (print->object->jrny->journeyCode == prevPrint->object->jrny->journeyCode)
					{
						print = print->next;
						prevPrint = prevPrint->next;
						continue;
					}

					for (int i = 0; i < 7; ++i)
					{
						if (prevPrint->object->jrny->daysOfWeek[i])
						{
							d = i;
						}
					}

					int dtemp = d;

					for (int i = 0; i < 7; ++i)
					{
						if (print->object->jrny->daysOfWeek[i])
						{
							d = i;
						}
					}

					if(transitTime(dtemp, prevPrint->object->jrny->arrTime, d, prevPrint->object->jrny->depTime) <= 0){
						y = true;
					}

					if(transitTime(dtemp, prevPrint->object->jrny->arrTime, d, prevPrint->object->jrny->depTime) > maxTransitTime){
						y = true;
					}

					print = print->next;
					prevPrint = prevPrint->next;
				}

				if(y){
					q->pop();
					continue;
				}
			}
			// ########################################################################

			isAnyJourney = true;

			cout << "### Journey" << endl;

			listOfObjects<JourneyAndStation *> *print = now->history;

			int d;

			for (int i = 0; i < 7; ++i)
			{
				if (print->object->jrny->daysOfWeek[i])
				{
					d = i;
				}
			}

			cout << RED << "Departs JC: " << print->object->jrny->journeyCode << " " << BLUE << stnNameToIndex.getKeyAtIndex(print->object->stnIndex) << GREEN << " " << day(d) << " " << print->object->jrny->depTime << RESET << " | ";

			listOfObjects<JourneyAndStation *> *prevPrint = now->history;
			print = print->next;

			while (print != nullptr)
			{
				if (print->object->jrny->journeyCode == prevPrint->object->jrny->journeyCode)
				{
					print = print->next;
					prevPrint = prevPrint->next;
					continue;
				}

				for (int i = 0; i < 7; ++i)
				{
					if (prevPrint->object->jrny->daysOfWeek[i])
					{
						d = i;
					}
				}

				int dtemp = d;

				cout << RED << "Arrives " << BLUE << stnNameToIndex.getKeyAtIndex(prevPrint->object->stnIndex) << GREEN << " " << day(d) << " " << prevPrint->object->jrny->arrTime << RESET << endl;

				for (int i = 0; i < 7; ++i)
				{
					if (print->object->jrny->daysOfWeek[i])
					{
						d = i;
					}
				}

				cout << "Transit Time : " << transitTime(dtemp, prevPrint->object->jrny->arrTime, d, prevPrint->object->jrny->depTime) << RED << " Departs JC: " << print->object->jrny->journeyCode << " " << BLUE << stnNameToIndex.getKeyAtIndex(prevPrint->object->stnIndex) << GREEN << " " << day(d) << " " << prevPrint->object->jrny->depTime << RESET << " | ";

				print = print->next;
				prevPrint = prevPrint->next;
			}

			cout << RED << "Arrives " << BLUE << stnNameToIndex.getKeyAtIndex(prevPrint->object->stnIndex) << GREEN << " " << day(d) << " " << prevPrint->object->jrny->arrTime << RESET << endl;
			cout << endl;
			q->pop();
			continue;
		}

		// continuing BFS if we haven't yet reached destination station
		{
			int currStnIndx = now->stnIndex;

			listOfObjects<JourneyAndStation *> *ptr = now->history;

			assert(ptr != nullptr);

			while (ptr->next != nullptr)
			{
				ptr = ptr->next;
			}

			// outward journies from the current station
			listOfObjects<StationConnectionInfo *> *outward = adjacency[currStnIndx].toStations;

			// iterating over outward journies
			while (outward != nullptr)
			{
				// index of adjacent station
				int adjStnIndx = outward->object->adjacentStnIndex;
				listOfObjects<TrainInfoPerStation *> *outTrains = separator(outward->object->trains);

				// iterating over each train going to the particular station
				while (outTrains != nullptr)
				{
					int jC = outTrains->object->journeyCode;

					int time1 = ptr->object->jrny->arrTime;
					int day1;

					// getting days and times of arriving train and departing train
					for (int i = 0; i < 7; ++i)
					{
						if (ptr->object->jrny->daysOfWeek[i])
						{
							day1 = i;
						}
					}

					int time2 = outTrains->object->depTime;
					int day2;

					for (int i = 0; i < 7; ++i)
					{
						if (outTrains->object->daysOfWeek[i])
						{
							day2 = i;
						}
					}

					// if arriving and departing train have same jourey code
					// meaning they are the same trains
					if (outTrains->object->journeyCode == ptr->object->jrny->journeyCode)
					{

						// to avoid redundant journies
						// for example if a train arrives and departs on mon and tues
						// we won't show a journey containing arrival on monday and departure on tuesday
						// monday will map to monday, tues to tues
						if (now->stnIndex == srcIndex || true)
						{

							int i1, i2;

							for (int i = 0; i < 7; ++i)
							{
								if (outTrains->object->daysOfWeek[i])
								{
									i1 = i;
								}

								if (ptr->object->jrny->daysOfWeek[i])
								{
									i2 = i;
								}
							}

							if (i1 != i2)
							{
								outTrains = outTrains->next;
								continue;
							}
						}

						// building a new AllAboutJourney object to push into the queue

						listOfObjects<JourneyAndStation *> *tempPtr = now->history;

						listOfObjects<JourneyAndStation *> *buildNew = nullptr;

						// copying the history from the previous station
						// previous station is the one at the head of the queue
						while (tempPtr != nullptr)
						{
							int ix = tempPtr->object->stnIndex;
							TrainInfoPerStation *t = tempPtr->object->jrny;

							TrainInfoPerStation *newt = new TrainInfoPerStation(t->journeyCode, t->stopSeq, t->arrTime, t->depTime);

							for (int i = 0; i < 7; ++i)
							{
								if (t->daysOfWeek[i])
								{
									newt->setDayOfWeek(i);
								}
							}

							// creating elements for listOfObjects
							JourneyAndStation *naya = new JourneyAndStation(ix, newt);

							// inserting created objects at tail of listOfObjects
							insertAtTail<JourneyAndStation *>(buildNew, naya);

							tempPtr = tempPtr->next;
						}

						// this part of the code basically gets appropriate arrival and departure times
						// using these   arrival and departure times new element of the queue is created
						// new element is also pushed in queue

						listOfObjects<StationConnectionInfo *> *m = adjacency[adjStnIndx].fromStations;

						while (m->object->adjacentStnIndex != currStnIndx)
						{
							m = m->next;
						}

						listOfObjects<TrainInfoPerStation *> *n = m->object->trains;

						while (n->object->journeyCode != outTrains->object->journeyCode)
						{
							n = n->next;
						}

						TrainInfoPerStation *t = n->object;

						TrainInfoPerStation *newt = new TrainInfoPerStation(t->journeyCode, t->stopSeq, t->arrTime, t->depTime);

						listOfObjects<StationConnectionInfo *> *pp = outward;

						while (pp->object->adjacentStnIndex != adjStnIndx)
						{
							pp = pp->next;
						}

						listOfObjects<TrainInfoPerStation *> *bb = pp->object->trains;

						while (bb->object->journeyCode != outTrains->object->journeyCode)
						{
							bb = bb->next;
						}

						// checking offset if any
						bool isoff = offset(t, bb->object);

						// setting day of the journey
						for (int i = 0; i < 7; ++i)
						{
							if (outTrains->object->daysOfWeek[i])
							{
								if (isoff)
								{
									newt->setDayOfWeek((i + 1) % 7);
								}
								else
								{
									newt->setDayOfWeek(i);
								}
							}
						}

						JourneyAndStation *naya = new JourneyAndStation(adjStnIndx, newt);

						insertAtTail<JourneyAndStation *>(buildNew, naya);

						AllAboutJourney *pushing = new AllAboutJourney(adjStnIndx, now->stopOvers, buildNew);

						q->push(pushing);
					}
					// if we have to change trains at the station
					else
					{
						// to avoid initial looping
						if (now->stnIndex == srcIndex)
						{
							outTrains = outTrains->next;
							continue;
						}

						// if we have exceeded maximum allowed stopovers then exit
						if (now->stopOvers + 1 > maxStopOvers)
						{
							outTrains = outTrains->next;
							continue;
						}

						// check if transit time is within stipulated limit
						bool flag = checkIntersection(day1, time1, day2, time2, maxTransitTime);

						// if all the above conditions are satisfied then go ahead with the BFS
						if (flag)
						{
							listOfObjects<JourneyAndStation *> *tempPtr = now->history;

							listOfObjects<JourneyAndStation *> *buildNew = nullptr;

							// copying the history that is created till now into new node
							// same as the code in the above part
							listOfObjects<JourneyAndStation *> *wPtr;

							while (tempPtr != nullptr)
							{
								int ix = tempPtr->object->stnIndex;
								TrainInfoPerStation *t = tempPtr->object->jrny;

								TrainInfoPerStation *newt = new TrainInfoPerStation(t->journeyCode, t->stopSeq, t->arrTime, t->depTime);

								if (tempPtr->next == nullptr)
								{
									wPtr = tempPtr;
									newt->depTime = outTrains->object->depTime;
								}

								for (int i = 0; i < 7; ++i)
								{
									if (t->daysOfWeek[i])
									{
										newt->setDayOfWeek(i);
									}
								}

								JourneyAndStation *naya = new JourneyAndStation(ix, newt);

								insertAtTail<JourneyAndStation *>(buildNew, naya);

								tempPtr = tempPtr->next;
							}

							// getting appropriate arrival and departure times
							// code is almost same as the above part

							listOfObjects<StationConnectionInfo *> *m = adjacency[adjStnIndx].fromStations;

							while (m->object->adjacentStnIndex != currStnIndx)
							{
								m = m->next;
							}

							listOfObjects<TrainInfoPerStation *> *n = m->object->trains;

							while (n->object->journeyCode != outTrains->object->journeyCode)
							{
								n = n->next;
							}

							TrainInfoPerStation *t = n->object;

							TrainInfoPerStation *newt = new TrainInfoPerStation(t->journeyCode, t->stopSeq, t->arrTime, t->depTime);

							listOfObjects<StationConnectionInfo *> *pp = outward;

							while (pp->object->adjacentStnIndex != adjStnIndx)
							{
								pp = pp->next;
							}

							listOfObjects<TrainInfoPerStation *> *bb = pp->object->trains;

							while (bb->object->journeyCode != outTrains->object->journeyCode)
							{
								bb = bb->next;
							}

							bool isoff = offset(t, bb->object);

							for (int i = 0; i < 7; ++i)
							{
								if (outTrains->object->daysOfWeek[i])
								{
									if (isoff)
									{
										newt->setDayOfWeek((i + 1) % 7);
									}
									else
									{
										newt->setDayOfWeek(i);
									}
								}
							}

							JourneyAndStation *naya = new JourneyAndStation(adjStnIndx, newt);

							insertAtTail<JourneyAndStation *>(buildNew, naya);

							AllAboutJourney *pushing = new AllAboutJourney(adjStnIndx, now->stopOvers + 1, buildNew);

							// pushing the new element in queue
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

	if(isAnyJourney == false){
		cout << RED << "NO JOURNEY FOUND" << RESET << endl;
	}

	return;
}

#endif
