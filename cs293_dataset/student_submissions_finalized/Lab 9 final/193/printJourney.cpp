#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// Defining the constants for the DynamicQueue
#define CONST_GROWTH 40
#define INIT_SIZE 40

template <typename T>
class DynamicQueue
{
private:
    T *A;              // the array used for implementing the dynamic dequeue
    unsigned int N;    // the current size of array A
    unsigned int head; // index where next element of queue will be deleted from
    unsigned int tail; // index where next element will be inserted
    unsigned int nextSize() { return N + CONST_GROWTH; }

public:
    DynamicQueue() // default constructor
    {
        A = new T[INIT_SIZE];
        if (A != nullptr)
            N = INIT_SIZE;
        else
            N = 0;
        head = tail = 0;
    }
    ~DynamicQueue() { delete[] A; }; // default destructor

    bool isEmpty()
    {
        return (tail == head); // When the head variable is the same as tail variable the queue becomes empty.
    }                          // is the queue empty?
    bool isFull()
    {
        return (size() == N);
    } // is the queue full?
    void grow()
    {
        unsigned int b = nextSize();
        T *B = new T[b]; // Alloting a new memory to a pointer.
        for (int i = head; i < tail; i++)
        { // copying the elements of the initial array to newly created array.
            // In the new array the elements are kept in a linear fashion.
            B[i - head] = A[i % N];
        }
        tail = N;   // tail becomes N
        head = 0;   // head again becomes 0
        N = b;      // grow the queue to its next size.
        delete (A); // freeing up the memory A initially pointed to.
        A = B;      // reallocating A to Newly created memory.
        B = NULL;   // making B point to NULL.
    }               // grow the queue to its next size
    unsigned int size()
    { // Gives the total number of elements present in the queue.
        return (tail - head);
    } // return the current number of elements in the queue
    void QInsert(T x)
    {
        if (isFull())
        {
            grow(); // just grow if full (in case of circular array.)
        }
        A[tail % N] = x;
        tail += 1;
    }
    bool QDelete(T *x)
    {
        if (size() == 0)
            return false;
        *x = A[head % N]; // storing the head in x.
        head += 1;        // head incremented.
        return true;
    }
    bool find_elem(T tofind) //Find whether an element is present in the Queue.
    {
        for (int i = head; i < tail; i++)
        {
            if (tofind == A[i % N])
            {
                return true;
            }
        }
        return false;
    }
};

class QueueElem
{ // The Object present in the Queue. Contains the train no connecting two adjacent Stations
  // and the station_No of the 2nd station.
public:
    int stn_ind; // The index of the station which is the end of the edge
    int trainno; // The journeyCode of the train from which we came to this node
    QueueElem()  // Default constructor
    {
        stn_ind = -1;
        trainno = -1;
    }
    QueueElem(int name, int jCode)
    {
        stn_ind = name;
        trainno = jCode;
    }
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
    // The Index of destination station
    int destination_ind = stnNameToIndex.get(destStnName)->value;

    // The Direct journeys are stored in form of Queue of their Train-No.
    DynamicQueue<int> Train_nos;

    // insert your code here
    DynamicQueue<QueueElem> queue_BFS;

    // Index of the station_Name
    int index = stnNameToIndex.get(srcStnName)->value;

    // The adjacency of the current station.
    StationAdjacencyList* curr = adjacency;

    // An iterator for the to.Stations to store all the adjacent stations
    listOfObjects<StationConnectionInfo *> *adjstns = curr[index].toStations;

    while (adjstns != NULL) // Storing all the adjacent station Names
    {
        // The index of the station which we have reached
        int ind_of_station = adjstns->object->adjacentStnIndex;

        // An iterator for trains to this station
        listOfObjects<TrainInfoPerStation *> *train = adjstns->object->trains;

        while (train != NULL)
        {
            // If there is direct train at start from source to stop.
            if (ind_of_station == destination_ind)
            {
                // Adding the TrainNo to the Queue of Train_nos.
                Train_nos.QInsert(train->object->journeyCode);
                train = train->next;
                continue; // Since we donot add these trains to the Queue
            }
            queue_BFS.QInsert(QueueElem(ind_of_station, train->object->journeyCode));
            train = train->next;
        }
        adjstns = adjstns->next;
    }

    while (!queue_BFS.isEmpty())
    {                                      // The Main BFS loop
        QueueElem *head = new QueueElem(); // Head of the Queue
        queue_BFS.QDelete(head);           // This stores the Head in the 'head' pointer
        int trainno = head->trainno;       // Gives the Train No of the Head
        int stn_ind = head->stn_ind;       // Gives Station index of the HEAD.
        adjstns = adjacency[stn_ind].toStations;
        while (adjstns != NULL)
        {
            listOfObjects<TrainInfoPerStation *> *train = adjstns->object->trains;
            int adjStn = adjstns->object->adjacentStnIndex;
            while (train != NULL)
            {
                if (train->object->journeyCode == trainno)
                {
                    // Check Whether the Removed trainno is same as that removed from Queue.
                    if (adjStn == destination_ind)
                    {
                        // When we reach the destination required.
                        //  Adding the TrainNo in the Queue Train_nos
                        Train_nos.QInsert(train->object->journeyCode);
                        break; // No further train exists hence exit While Loop
                    }
                    // Adding the element into the Queue
                    queue_BFS.QInsert(QueueElem(adjStn, trainno));
                }
                train = train->next;
            }
            adjstns = adjstns->next;
        }
    }
    // Finally Train_nos contain all the Train numbers.
    // We Check the Source Station for the corresponding TrainNo.

    // Finally the list to be returned.
    listOfObjects<TrainInfoPerStation *> *source_j = NULL;

    // Total Train Info for the source station.
    listOfObjects<TrainInfoPerStation *> *Total_source = stationInfo[stnNameToIndex.get(srcStnName)->value];

    while (Total_source != NULL)
    {
        if (Train_nos.find_elem(Total_source->object->journeyCode))
        {
            if (source_j == NULL)
            {
                source_j = new listOfObjects<TrainInfoPerStation *>(Total_source->object);
            }
            else
            { // Adding the element to the list at the start
                listOfObjects<TrainInfoPerStation *> *iterator = source_j;
                iterator->prev = new listOfObjects<TrainInfoPerStation *>(Total_source->object);
                iterator->prev->next = iterator;
                source_j = iterator->prev;
            }
        }
        Total_source = Total_source->next;
    }

if (source_j == NULL)
{
    std::cout << "No direct journeys available" << endl;
    return;
}

printStationInfo(source_j);
// This would return all the journeys from the source station.

return;
}

#endif
