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

listOfObjects<TrainInfoPerStation *> *separator(listOfObjects<TrainInfoPerStation *> *ptr)
{
	listOfObjects<TrainInfoPerStation *> *ret = nullptr;

	listOfObjects<TrainInfoPerStation *> *temp = ptr;

	while (temp != nullptr)
	{
		int jCode = temp->object->journeyCode;
		int sSeq = temp->object->stopSeq;
		int aTime = temp->object->arrTime;
		int dTime = temp->object->depTime;

		for (int i = 0; i < 7; ++i)
		{
			if (temp->object->daysOfWeek[i])
			{
				TrainInfoPerStation *nuJrny = new TrainInfoPerStation(jCode, sSeq, aTime, dTime);
				nuJrny->setDayOfWeek(i);

				insertAtHead(ret, nuJrny);
			}
		}

		temp = temp->next;
	}

	return ret;
}

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
		int jCode = temp->object->journeyCode;
		int sSeq = temp->object->stopSeq;
		int aTime = temp->object->arrTime;
		int dTime = temp->object->depTime;

		if (dTime == -1)
		{
			temp = temp->next;
			continue;
		}

		for (int i = 0; i < 7; ++i)
		{
			if (temp->object->daysOfWeek[i])
			{
				TrainInfoPerStation *nuJrny = new TrainInfoPerStation(jCode, sSeq, aTime, dTime);
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

bool checkIntersection(int day1, int time1, int day2, int time2, int max)
{
	int dt = (2400 + time2 - time1) % 2400;

	int dd = (7 + day2 - day1) % 7;

	if (dt == 0)
	{
		dd++;
	}

	int timeBW = dd * 2400 + dt;

	if (timeBW <= max)
		return true;
	else
		return false;
}

string day(int i)
{
	if (i == 0)
	{
		return "Monday";
	}

	else if (i == 1)
	{
		return "Tuesday";
	}

	else if (i == 2)
	{
		return "Wednesday";
	}

	else if (i == 3)
	{
		return "Thursday";
	}

	else if (i == 4)
	{
		return "Friday";
	}

	else if (i == 5)
	{
		return "Saturday";
	}

	else
	{
		return "Sunday";
	}
}

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

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
	int srcIndex = stnNameToIndex.get(srcStnName)->value;
	int destIndex = stnNameToIndex.get(destStnName)->value;

	listOfObjects<TrainInfoPerStation *> *prunedSrcJournies = srcSeparator(stationInfo[srcIndex]);

	Q<AllAboutJourney *> *q = new Q<AllAboutJourney *>;

	initialPusher(q, prunedSrcJournies, srcIndex);

	// cout << "point 1" << endl;

	while (q->empty() != true)
	{
		AllAboutJourney *now = q->front();

		if (now->stnIndex == destIndex)
		{

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

				cout << RED << "Arrives " << BLUE << stnNameToIndex.getKeyAtIndex(prevPrint->object->stnIndex) << GREEN << " " << day(d) << " " << prevPrint->object->jrny->arrTime << RESET << endl;

				for (int i = 0; i < 7; ++i)
				{
					if (print->object->jrny->daysOfWeek[i])
					{
						d = i;
					}
				}

				cout << RED << "Departs JC: " << print->object->jrny->journeyCode << " " << BLUE << stnNameToIndex.getKeyAtIndex(prevPrint->object->stnIndex) << GREEN << " " << day(d) << " " << prevPrint->object->jrny->depTime << RESET << " | ";

				print = print->next;
				prevPrint = prevPrint->next;
			}

			cout << RED << "Arrives " << BLUE << stnNameToIndex.getKeyAtIndex(prevPrint->object->stnIndex) << GREEN << " " << day(d) << " " << prevPrint->object->jrny->arrTime << RESET << endl;
			cout << endl;
			q->pop();
			continue;
		}

		{
			int currStnIndx = now->stnIndex;

			listOfObjects<JourneyAndStation *> *ptr = now->history;

			assert(ptr != nullptr);

			while (ptr->next != nullptr)
			{
				ptr = ptr->next;
			}

			listOfObjects<StationConnectionInfo *> *outward = adjacency[currStnIndx].toStations;

			while (outward != nullptr)
			{
				int adjStnIndx = outward->object->adjacentStnIndex;
				listOfObjects<TrainInfoPerStation *> *outTrains = separator(outward->object->trains);

				printStationInfo(outTrains);

				while (outTrains != nullptr)
				{
					int jC = outTrains->object->journeyCode;
					int time1 = ptr->object->jrny->arrTime;
					int day1;

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

					if (outTrains->object->journeyCode == ptr->object->jrny->journeyCode)
					{

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

						listOfObjects<JourneyAndStation *> *tempPtr = now->history;

						listOfObjects<JourneyAndStation *> *buildNew = nullptr;

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

							JourneyAndStation *naya = new JourneyAndStation(ix, newt);

							insertAtTail<JourneyAndStation *>(buildNew, naya);

							tempPtr = tempPtr->next;
						}

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

						AllAboutJourney *pushing = new AllAboutJourney(adjStnIndx, now->stopOvers, buildNew);

						q->push(pushing);
					}
					else
					{
						if (now->stnIndex == srcIndex)
						{
							outTrains = outTrains->next;
							continue;
						}

						if (now->stopOvers + 1 > maxStopOvers)
						{
							outTrains = outTrains->next;
							continue;
						}

						bool flag = checkIntersection(day1, time1, day2, time2, maxTransitTime);

						if (flag)
						{
							listOfObjects<JourneyAndStation *> *tempPtr = now->history;

							listOfObjects<JourneyAndStation *> *buildNew = nullptr;

							while (tempPtr != nullptr)
							{
								int ix = tempPtr->object->stnIndex;
								TrainInfoPerStation *t = tempPtr->object->jrny;

								TrainInfoPerStation *newt = new TrainInfoPerStation(t->journeyCode, t->stopSeq, t->arrTime, t->depTime);

								if (tempPtr->next == nullptr)
								{
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
