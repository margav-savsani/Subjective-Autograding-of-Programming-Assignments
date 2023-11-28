#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#define INF 1000000

// helper function for formatted printing
void printJourney(TrainInfoPerStation *currInfo)
{
	string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

	if (currInfo != nullptr)
	{
		cout << GREEN << "Day(s): " << RESET;
		for (int i = 0; i < 7; i++)
		{
			if (currInfo->daysOfWeek[i])
				cout << days[i] << " ";
		}
		cout << endl;
		cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
		cout << RED << "Arr: " << RESET;
		if (currInfo->arrTime == -1)
		{
			cout << "Starts";
		}
		else
		{
			cout << currInfo->arrTime;
		}
		cout << RED << " Dep: " << RESET;
		if (currInfo->depTime == -1)
		{
			cout << "Ends";
		}
		else
		{
			cout << currInfo->depTime;
		}
		cout << endl;
	}
}

// implementation of helper queue
class Q
{
	listOfObjects<int> *head; // pointer to head of queue
	listOfObjects<int> *tail; // pointer to tail of queue
	int size;				  // size of queue

public:
	// constructor
	Q()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	// pushing new element at the tail of the queue
	void push(int x)
	{
		if (head == nullptr)
		{
			head = new listOfObjects<int>(x);
			tail = head;
			size++;
		}
		else
		{
			tail->next = new listOfObjects<int>(x);
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
			listOfObjects<int> *temp = head->next;
			delete head;
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
	int front()
	{
		if (head != nullptr)
		{
			return head->object;
		}

		return -1;
	}

	// checking if the queue is empty
	bool empty()
	{
		return size == 0;
	}
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
	// index of source station in dictionary
	int srcStnIndex = stnNameToIndex.get(srcStnName)->value;

	// index of destination station in dictionary
	int destStnIndex = stnNameToIndex.get(destStnName)->value;

	bool isJourneyPresent = false;

	// here we will get all the journey codes that originate from source station
	// for this we will traverse over all the adjacent nodes of source station
	// and for each adjacent node we will traverse over all the journeys from source to that node
	// we will create a linked list containing all the journeys from source station
	// for each journey code we will do a different BFS to see if source and destination are connected

	// list of adjacent nodes of source station
	listOfObjects<StationConnectionInfo *> *journiesFromSrc = adjacency[srcStnIndex].toStations;

	// linked list to store journey codes originating from source station
	listOfObjects<int> *jrnyCodes = nullptr;

	// iterating over adjacent nodes
	while (journiesFromSrc != nullptr)
	{
		// journeys to particular adjacent station
		listOfObjects<TrainInfoPerStation *> *ptr = journiesFromSrc->object->trains;

		// iterating over journies to particular adjacent station
		while (ptr != nullptr)
		{
			// journey code of the particular journey
			int val = ptr->object->journeyCode;

			// pointer to prior created linked list of jouney codes
			listOfObjects<int> *temp = jrnyCodes;
			bool flag = true;

			// checking whether this journey code is already present in our linked list
			while (temp != nullptr)
			{
				if (temp->object == val)
				{
					flag = false;
					break;
				}
				temp = temp->next;
			}

			// if not present then insert in the linked list
			if (flag)
			{
				if (jrnyCodes == nullptr)
				{
					jrnyCodes = new listOfObjects<int>(val);
				}
				else
				{
					listOfObjects<int> *t = jrnyCodes;
					jrnyCodes = new listOfObjects<int>(val);
					jrnyCodes->next = t;
					t->prev = jrnyCodes;
				}
			}
			ptr = ptr->next;
		}

		journiesFromSrc = journiesFromSrc->next;
	}

	// now we will do BFS for each of the journey code obtained earlier

	listOfObjects<int> *jrnyTemp = jrnyCodes;

	// iterating over each jouneyCode originating from source station
	while (jrnyTemp != nullptr)
	{
		// here is a normal BFS as we would do on any graph

		// queue
		Q q;

		// jouney code of present journey
		int jrnyCode = jrnyTemp->object;

		// array to store distance
		int *d = new int[DICT_SIZE];

		// array to store color denoting visited or not
		int *color = new int[DICT_SIZE];
		// 0 - white
		// 1 - gray
		// 2 - black

		// initializing the above arrays
		for (int i = 0; i < DICT_SIZE; ++i)
		{
			color[i] = 0;
			d[i] = INF;
		}

		// setting for the source station
		color[srcStnIndex] = 1;
		d[srcStnIndex] = 0;
		q.push(srcStnIndex);

		// same as in a normal BFS
		// we do this until queue is empty
		while (q.empty() != true)
		{
			// getting the element at the head of queue
			int currStnIndex = q.front();

			// now we will determine the connectedness of nodes

			// here we are considering the nodes to be connected only if
			// they have a train journey of given journey code between them

			// here basically we are checking if the train with the given
			// journey code is present between 2 nodes

			// stations adjacent to current station
			listOfObjects<StationConnectionInfo *> *currTo = adjacency[currStnIndex].toStations;

			// iterating over adjacent nodes to determine connectedness
			while (currTo != nullptr)
			{
				// iterating over journeys to determine if the journey with specific
				// journey code is present between 2 stations
				listOfObjects<TrainInfoPerStation *> *currJournies = currTo->object->trains;

				while (currJournies != nullptr)
				{
					// journey code
					int val = currJournies->object->journeyCode;

					// if unvisited
					if (color[currTo->object->adjacentStnIndex] == 0)
					{
						// if connected
						if (val == jrnyCode)
						{

							int indx = currTo->object->adjacentStnIndex;
							// setting appropriate color
							color[indx] = 1;
							// setting distance
							d[indx] = d[currStnIndex] + 1;
							// pushing station in queue
							q.push(indx);
							break;
						}
					}
					currJournies = currJournies->next;
				}

				currTo = currTo->next;
			}
			// pop the station
			q.pop();
			// set color to black
			color[currStnIndex] = 3;
		}

		// if connected
		if (d[destStnIndex] < INF)
		{	
			
			// formatted printing 

			isJourneyPresent = true;

			listOfObjects<StationConnectionInfo *> *journiesFromSrc = adjacency[srcStnIndex].toStations;
			

			while (journiesFromSrc != nullptr)
			{	
				listOfObjects<TrainInfoPerStation *> *ptr = journiesFromSrc->object->trains;
				bool f = false;

				while (ptr != nullptr)
				{
					int val = ptr->object->journeyCode;

					if(val == jrnyCode){

						listOfObjects<TrainInfoPerStation *> *lmao = stationInfo[srcStnIndex];

						while(lmao != nullptr){
							if(lmao->object->journeyCode == val){
								printJourney(lmao->object);
								break;
							}

							lmao = lmao->next;
						}

						f = true;
						break;
					}

					ptr = ptr->next;
				}

				if(f){
					break;
				}

				journiesFromSrc = journiesFromSrc->next;
			}
		}

		jrnyTemp = jrnyTemp->next;
	}

	if(isJourneyPresent == false){
		cout << BLUE << "No direct journeys available" << RESET << endl;
	}

	return;
}

#endif
