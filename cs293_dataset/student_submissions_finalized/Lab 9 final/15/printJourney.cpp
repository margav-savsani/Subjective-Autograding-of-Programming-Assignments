#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

#define CONST_GROWTH 20
#define INIT_SIZE 10


// Implementation of a queue from lab1
template <typename T> class DynamicQueue {
private:
  T *A; // the array used for implementing the dynamic dequeue
  unsigned int N; // the current size of array A
  unsigned int head; // index where next element of queue will be deleted from
  unsigned int tail; // index where next element will be inserted
  unsigned int nextSize() { return N+CONST_GROWTH; }
public:
  DynamicQueue() // default constructor
  {
    A = new T[INIT_SIZE];
    if (A != nullptr) N = INIT_SIZE;
    else N = 0;
    head = tail = 0;
  } 
  ~DynamicQueue(){delete[] A;}; // default destructor
  bool isEmpty(); // is the queue empty?
  bool isFull(); // is the queue full?
  void grow(); // grow the queue to its next size 
  unsigned int size(); // return the current number of elements in the queue
  void QInsert(T x); // insert given element at tail of the queue; grow array size as necessary
  bool QDelete(T *x); // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
};

template<typename T>
bool DynamicQueue<T>::isEmpty(){        //returns true if queue is empty else returns false
    return head==tail;
}

template<typename T>
unsigned int DynamicQueue<T>::size(){   
    return tail-head;             //here head and tail are not indexes but their mod N are indexes
}

template<typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isFull()){                       //Increasing the size if the queue is full
        grow();
    }
    A[tail%N]=x;                        //we do not loop we use tail%N as index
    tail=(tail+1);                    //We just increase the tail
}

template<typename T>
bool DynamicQueue<T>::isFull(){         //I can fill the array up to N which is the full size
    return (size()==N);
}

template<typename T>
void DynamicQueue<T>::grow(){
    T* B=new T[N+CONST_GROWTH];             //making a new array of T of increased size
    for(int i=0;i<size();i++){          //copying the elements of A in B
        B[i]=A[(head+i)%N];            
    }

    head=0;
    tail=N;                           //now it is arranged with head starting from 0
    N=N+CONST_GROWTH;                      //updating N
    delete(A);                          //deleting the space allocated to A
    A=B;
}

template<typename T>
bool DynamicQueue<T>::QDelete(T* x){
    if(isEmpty()){                      //returning false if the queue is empty
        return false;
    }
    *x=A[head%N];                         //storing the value at position pointed by x
    head=(head+1);                    //updating head
    return true;                        
}





// This corresponds to a journey from a station or an edge of the graph we will put this in the queue
class edge
{
public:
    int stationnumber, journeycode;
    edge(int sn = -1, int jc = -1)
    {
        stationnumber = sn;
        journeycode = jc;
    }
};

// A function to insert to a ll
template <typename T>
void add_ll(listOfObjects<T>* &valid_jcs,T val){
    if(valid_jcs==nullptr){
        valid_jcs=new listOfObjects<T>(val);
        return;
    }
    else{
        listOfObjects<T> *curr=valid_jcs;
        while(curr->next!=nullptr){
            curr=curr->next;
        }
        curr->next=new listOfObjects<T>(val);
        return;
    }
}


// A function to find if an element is present in an ll
template <typename T>
bool present_ll(T i,listOfObjects<T>* valid_jcs){
    listOfObjects<T>* n=valid_jcs;
    while(n!=nullptr){
        if(n->object==i){
            return true;
        }
        n=n->next;
    }
    return false;
}


void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
    int index = stnNameToIndex.get(srcStnName)->value;  // index of source
    int dest = stnNameToIndex.get(destStnName)->value;  // index of destination
    DynamicQueue<edge> QueueTrains;                     // Queue for BFS
    listOfObjects<StationConnectionInfo *> *Station = adjacency[index].toStations;  // All reachable stations
    listOfObjects<int> *valid_jcs=nullptr;  // This list will store the valid journey codes we will later add the
                                            // corresponding information to another list


    // here we basically added all the trains going out of the source station to all stations in the queue
    while (Station != nullptr)
    {
        listOfObjects<TrainInfoPerStation *> *trains = Station->object->trains;
        int sn = Station->object->adjacentStnIndex;
        while (trains != nullptr)
        {
            if (sn == dest)     //if directly connected to the destination then bingo
            {   
                add_ll<int>(valid_jcs,trains->object->journeyCode);
                trains=trains->next;
                continue;       // We do not need journeys from the destination
            }

            QueueTrains.QInsert(edge(sn, trains->object->journeyCode));
            trains = trains->next;
        }
        Station = Station->next;
    }

    while (!QueueTrains.isEmpty())
    {
        edge *e = new edge();
        QueueTrains.QDelete(e); // This basically deletes from the queue and stores the information in e.
        int jc = e->journeycode;
        listOfObjects<StationConnectionInfo *> *Station2 = adjacency[e->stationnumber].toStations;
        while (Station2 != nullptr) // Seeing all stations
        {
            listOfObjects<TrainInfoPerStation *> *trains2 = Station2->object->trains;   // Seeing all trains
            int sn = Station2->object->adjacentStnIndex;
            while (trains2 != nullptr)
            {
                if (trains2->object->journeyCode == jc) // We only consider journeys whose journey code matches the removed 
                                                        // entries journey code
                {
                    if (sn == dest)         // If reached the destination
                    {
                        add_ll<int>(valid_jcs,trains2->object->journeyCode);
                        break;
                    }
                    QueueTrains.QInsert(edge(sn, jc));  // Inserting to the queue
                }
                trains2 = trains2->next;
            }
            Station2 = Station2->next;
        }
    }

    listOfObjects<TrainInfoPerStation *> *Answers=nullptr;//Stores what we have to print

    listOfObjects<TrainInfoPerStation*>* s=stationInfo[index];//Iterating through the stationInfo list to
                                                    // add journeys which have the valid journeycodes
    while(s!=nullptr){
        if(present_ll<int>(s->object->journeyCode,valid_jcs)){
            add_ll<TrainInfoPerStation*>(Answers,s->object);
        }
        s=s->next;
    }
    printStationInfo(Answers);  //printing the Answers
    return;
}

#endif
