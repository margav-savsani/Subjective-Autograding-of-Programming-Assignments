#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

// Defining the constants for the DynamicQueue
#define CONST_GROWTH 1000
#define INIT_SIZE 1000

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
    ~DynamicQueue(){}; // default destructor

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

        for (unsigned int i = head; i < tail; i++)
        { // copying the elements of the initial array to newly created array.
            // In the new array the elements are kept in a linear fashion.
            B[i - head] = A[i % N];
        }
        tail = N; // tail becomes N
        head = 0; // head again becomes 0
        N = b;    // grow the queue to its next size.

        // delete (A); // freeing up the memory A initially pointed to.
        A = B;    // reallocating A to Newly created memory.
        B = NULL; // making B point to NULL.
    }             // grow the queue to its next size
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
    bool QDelete()
    {
        if (size() == 0)
            return false;
        head += 1; // head incremented.
        return true;
    }
    bool find_elem(T tofind) // Find whether an element is present in the Queue.
    {
        for (unsigned int i = head; i < tail; i++)
        {
            if (tofind == A[i % N])
            {
                return true;
            }
        }
        return false;
    }
    T get_last()
    {
        return A[(tail - 1) % N];
    }
    T get_first()
    {
        return A[head % N];
    }
};

// Find the arrival time of the given train at the specified station.
int find_arr_time(int train_no, listOfObjects<TrainInfoPerStation *> *iterator)
{
    while (iterator != NULL)
    {
        if (iterator->object->journeyCode == train_no)
        {
            return iterator->object->arrTime;
        }
        iterator = iterator->next;
    }
    return -1; // When the arrival time is not found.
}

// Find the departure time of the given train from the specified station.
int find_dep_time(int train_no, listOfObjects<TrainInfoPerStation *> *iterator)
{
    while (iterator != NULL)
    {
        if (iterator->object->journeyCode == train_no)
        {
            return iterator->object->depTime;
        }
        iterator = iterator->next;
    }
    return -1; // If departure time is not found.
}

// Find all the days this train is involved in a station.
DynamicQueue<int> find_days(int train_no, listOfObjects<TrainInfoPerStation *> *iterator)
{
    DynamicQueue<int> days;
    while (iterator != NULL)
    {
        TrainInfoPerStation *itr = iterator->object;
        if (itr->journeyCode == train_no)
        {
            for (int i = 0; i < 7; i++)
            {
                if (itr->daysOfWeek[i])
                    days.QInsert(i);
            }
        }
        iterator = iterator->next;
    }
    // Contains a Queue of Days when the train is on the specified station.
    return days;
}

// The Element of the BFS queue
struct QueueElem
{
    // The number of stops reached during the journey.
    int Stops = -1; // initially the variable is initialised to -1.

    // The Days on which the train arrives at the adjacent station.
    DynamicQueue<int> days;

    // The trains that were taken for the Journey.
    DynamicQueue<int> trains;

    // The station sequences in the journey.
    DynamicQueue<int> Stations;

    // The Function to update the Queue Element.
    QueueElem update(int train, int Station, int day)
    {
        this->trains.QInsert(train);
        this->Stations.QInsert(Station);
        this->days.QInsert(day);
        if (trains.get_last() != train)
        // If the train is changed then increment the number of stops.
        {
            Stops += 1;
        }
        // If the last train is the same then donot increment the stops
        return *(this);
    }
    // The construction for the first time in the Queue.
    QueueElem(int train, int Station, int day)
    {
        Stops = 0;
        this->trains.QInsert(train);
        this->Stations.QInsert(Station);
        this->days.QInsert(day);
    }
    QueueElem() // The default constructor for the QueueElem
    {
        Stops = -1;
    }
};

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
    int destination_ind = stnNameToIndex.get(destStnName)->value;
    int source_ind = stnNameToIndex.get(srcStnName)->value;

    // // The Queue For the BFS
    DynamicQueue<QueueElem> BFS_queue;

    // // The final Answer Queue, which would be used for printing
    DynamicQueue<QueueElem> FINAL_ANS;

    // // The adjacency array.
    StationAdjacencyList *curr = adjacency;

    // // An iterator for the to.Stations to store all the adjacent stations to source
    listOfObjects<StationConnectionInfo *> *adjstns = curr[source_ind].toStations;

    while (adjstns != NULL) // Storing all the adjacent stations of the source
    {
        // The index of the station which we have reached
        int ind_of_station = adjstns->object->adjacentStnIndex;

        // An iterator for trains from source to this station.
        listOfObjects<TrainInfoPerStation *> *train = adjstns->object->trains;
        while (train != NULL)
        {
            // A Queue of days when the train is running in the adjacent station.
            int currtn = train->object->journeyCode;
            DynamicQueue<int> days = find_days(currtn, stationInfo[ind_of_station]);
            while (!days.isEmpty())
            {
                int temp = days.get_first();
                days.QDelete();

                // If there is direct train at start from source to stop.
                if (ind_of_station == destination_ind)
                {
                    QueueElem *a = new QueueElem(currtn, ind_of_station, temp);
                    FINAL_ANS.QInsert(*a);
                }
                else
                {
                    QueueElem *b = new QueueElem(currtn, ind_of_station, temp);
                    BFS_queue.QInsert(*b);
                }
            }
            train = train->next;
        }
        adjstns = adjstns->next;
    }

    while (!BFS_queue.isEmpty())
    {
        QueueElem head_bfs = BFS_queue.get_first();  // Head_bfs of the Queue
        BFS_queue.QDelete();                         // Delete the start element of the Queue
        int prev_train = head_bfs.trains.get_last(); // Gives the last Train No of the head_bfs of queue.
        int prev_stn = head_bfs.Stations.get_last(); // Gives last Station index of the head_bfs of queue.
        int day = head_bfs.days.get_last();          // Gives the arrival day of train at this given station.
        adjstns = curr[prev_stn].toStations;         // All the stations that can be reached from this station.

        if (head_bfs.Stops > maxStopOvers)
        {
            // If we cross the maximum stopovers then we donot add
            // anything further using that object in the Queue and just look for next Element of BFS_queue
            continue;
        }

        // When the stopovers are within the range
        while (adjstns != NULL)
        {
            listOfObjects<TrainInfoPerStation *> *train = adjstns->object->trains;
            int adjStn = adjstns->object->adjacentStnIndex;
            if (adjStn == destination_ind)
            {
                while (train != NULL)
                {
                    // The days when this train is running in current adjacent station to the previous station.
                    int currt = train->object->journeyCode;
                    DynamicQueue<int> days = find_days(currt, stationInfo[adjStn]);
                    while (!days.isEmpty())
                    {
                        int temp_day = days.get_first();
                        days.QDelete();
                        QueueElem temp = head_bfs;
                        QueueElem new_elem = temp.update(currt, adjStn, temp_day);
                        FINAL_ANS.QInsert(new_elem);
                    }
                    train = train->next;
                }
            }
            else
            {
                while (train != NULL)
                {
                    // The days when this train is running in current adjacent station to the previous station.
                    int currt = train->object->journeyCode;
                    DynamicQueue<int> days = find_days(currt, stationInfo[adjStn]);
                    while (!days.isEmpty())
                    {
                        int temp_day = days.get_first();
                        days.QDelete();

                        // If the train is the same as that of the previous train then we simply add them in the Queue
                        //  i.e no contraints are checked
                        if (currt == prev_train)
                        {
                            QueueElem temp = head_bfs;
                            QueueElem new_elem = temp.update(currt, adjStn, temp_day);
                            BFS_queue.QInsert(new_elem);
                        }

                        // Adding the trains to the Queue only after checking the constraints.
                        else
                        {
                            // The arrival time of the previous train at prev the station.
                            int arr = find_arr_time(prev_train, stationInfo[prev_stn]);

                            // The departure time of the current train from the prev station.
                            int dep = find_dep_time(currt, stationInfo[prev_stn]);

                            if (dep == -1)
                            { // Which means the train ends at this station and hence we donot continue further.
                                break;
                            }
                            // This Queue Stores the departure days of the current train from the previous station.
                            DynamicQueue<int> dept_days = find_days(currt, stationInfo[prev_stn]);
                            while (!dept_days.isEmpty())
                            {
                                // If the journey is within the bounds.
                                int temp_dept_day = dept_days.get_first();
                                dept_days.QDelete();

                                // Adding into the Queue only when the departure day of this train is greater than or equal arrival day
                                // Of the previous train
                                if (temp_dept_day >= day)
                                {
                                    if (((temp_dept_day - day) * 24 + ((dep - arr) / 100)) <= maxTransitTime)
                                    {
                                        // New element to be inserted into the queue
                                        QueueElem temp = head_bfs;
                                        QueueElem new_elem = temp.update(currt, adjStn, temp_day);
                                        BFS_queue.QInsert(new_elem);
                                    }
                                }
                            }
                        }
                    }
                    train = train->next;
                }
            }
            adjstns = adjstns->next;
        }
    }
    // PRINTING THE FINAL JOURNEYS
    {
        bool exists = false; // Boolean to check if the journeys exists between the station.
        int sz = FINAL_ANS.size();
        for (int i = 0; i < sz; i++)
        {
            exists = true;
            // The HEAD of the queue.
            QueueElem tmp = FINAL_ANS.get_first();
            FINAL_ANS.QDelete(); // Obtained the head of the Queue
            std::cout << GREEN << "THE JOURNEY IS " << RESET << endl;
            int prev_stn = source_ind;   // Prev_station
            int prev_tr = -12;           // Prev_train
            int sz1 = tmp.trains.size(); // size of the trains.

            for (int j = 0; j < sz1; j++)
            {
                // While the Trains in the head queue is not empty then print the stations in the queue
                int stnno = tmp.Stations.get_first();
                int tno = tmp.trains.get_first();
                int aday = tmp.days.get_first();
                // station in the journey
                tmp.Stations.QDelete();

                // train in journey
                tmp.trains.QDelete();

                // Day of arrival
                tmp.days.QDelete();

                cout << BLUE << "STATION: "
                     << "\t" << RESET << stnNameToIndex.getKeyAtIndex(prev_stn) << endl;
                std::cout << BLUE << "TRAIN_NO: "
                          << "\t" << RESET << tno << endl;
                std::cout << BLUE << "ARRIVAL DAY"
                          << "\t" << RESET << aday << endl;
                std::cout << RED << "Arr: "
                          << "\t" << RESET;

                int atime = find_arr_time(tno, stationInfo[prev_stn]);
                int dtime = find_dep_time(tno, stationInfo[prev_stn]);
                if (atime == -1)
                {
                    std::cout << "Starts";
                }
                else
                {
                    std::cout << atime;
                }
                std::cout << RED << " Dep: " << RESET;
                if (dtime == -1)
                {
                    std::cout << "Ends";
                }
                else
                {
                    std::cout << dtime;
                }
                cout << endl;
                prev_stn = stnno;
                prev_tr = tno;
            }

            cout << "================================" << endl;
        }
        if (!exists)
        {
            std::cout << RED << "NO JOURNEYS POSSIBLE" << RESET << endl;
        }
    }
    return;
}

#endif
