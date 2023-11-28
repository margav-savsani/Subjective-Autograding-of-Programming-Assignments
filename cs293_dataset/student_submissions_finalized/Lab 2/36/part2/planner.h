#ifndef PLANNER_H
#define PLANNER_H
#include <string.h>
#include <iostream>
#include<cmath>
using namespace std;

#define CONST_GROWTH 10
#define INIT_SIZE 10  //for queue
const int DICT_SIZE=64;


struct Journey
{
  // define suitable fields here
  float start_time;
  char station_2[32];
  float finish_time;
};


class Queue
{
public:
    struct Journey *journey_data;              // the array used for implementing the dynamic dequeue
    unsigned int N;    // the current size of array A
    unsigned int head; // index where next element of queue will be deleted from
    unsigned int tail; // index where next element will be inserted
    unsigned int nextSize() { return N + CONST_GROWTH; }


    Queue() // default constructor
    {
        journey_data = new struct Journey[INIT_SIZE];
        if (journey_data != nullptr)
            N = INIT_SIZE;
        else
            N = 0;
        head = tail = 0;
    }
    ~Queue() { delete[] journey_data; }; // default destructor

    bool isEmpty()
    {
        return (tail == head);
    }
    bool isFull()
    {
        return tail == N;
    }
    void grow()
    {
        struct Journey *B;
        B = new struct Journey[nextSize()];         // new array with nextSize
        for (int i = head; i < N; i++) // copying elements into new array
        {
            B[i] = journey_data[i];
        }
        journey_data = B;          // changing pointer to new array
        N = nextSize(); // changing current size
    }
    unsigned int size()
    {
        return tail - head;
    }
    void QInsert(struct Journey x)
    {
        if (tail == N)
        {
            grow();
        }
        journey_data[tail] = x;
        cout<<"\tAdded " <<journey_data[tail].start_time<<" "<<journey_data[tail].station_2<<" "<<journey_data[tail].finish_time<<endl;
        tail++;

    }
    bool QDelete()
    {
        if (tail - head == 0)
        {
            return false;
        }
        head++;
        return true;
    }
};

struct Entry {
  // define suitable fields here
  char station_1[32];
  Queue journeys_of_train;
  int tombstone=0;
};

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:

int hashValue(char key[])
{
    int hash_v = 0;
    int x = 33;
    int y = 1;
    int lastindex;
    for (int i=0;i<32;i++) {
        if (key[i]=='\0') {lastindex=i;break;}
    }
    for (int i=lastindex-1;i>0;i--) {
        hash_v=(hash_v +key[i])*x;
        hash_v=hash_v%DICT_SIZE;
    }
    hash_v+=key[0];
    return hash_v%DICT_SIZE;
}

int findFreeIndex(char key[])
{   int t=0;
    int hash_v = hashValue(key);
    while (t<DICT_SIZE)
    {
        if (A[hash_v].tombstone != 2)
        {
            return hash_v;
        }
        else
            hash_v++;
            t++;
    }
    return -1;
}

Dictionary()
{
    N = 0;
    A = new struct Entry[DICT_SIZE];
}

struct Entry *get(char key[])
{
    int hash_v = hashValue(key);
    while (A[hash_v].tombstone != 0)
    {
        if (strcmp(A[hash_v].station_1, key)==0)
        {
            return &A[hash_v];
        }
        hash_v++;
    }
    return NULL;
}

void put(struct Entry e)
{
    int index = findFreeIndex(e.station_1);
    if (index == -1)
    {
      cout<<"\tno free space\n";
    }
    A[index] = e;
    A[index].tombstone = 2;
    cout<<"\tJourney added successfully\n";
    N++;
}

bool remove(char key[])
{
    if (get(key) == NULL)
    {   
        return false;
    }
    int hash_v = hashValue(key);
    while (&A[hash_v].tombstone != 0)
    {
        if (strcmp(A[hash_v].station_1 , key)==0)
        {
            A[hash_v].tombstone = 1;
            N--;
            return true;
        }
        hash_v++;
    }
    return false;
}
};


#endif