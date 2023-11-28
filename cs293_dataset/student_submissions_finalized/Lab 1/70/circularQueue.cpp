#include<iostream>
#include "queue.h"

using namespace std;

//this is an impelementation of the circular queue where consecutive elements in the queue are stored at
// array locations that are consecutive *modulo the array size*
//the first element is not always at the smallest index compared to other elements of the array

//my array implementation puts tail one index after the last entered element
//whereas head represents the first element, except when the queue is empty

template<typename T> bool DynamicQueue<T>:: isEmpty(){
    //returns true if the array is empty
    return (head==tail);
}
template<typename T> bool DynamicQueue<T>:: isFull(){
    //returns true if the array is full my array becomes full once the number of elements in the array reaches N-1 that is to avoid clash with the empty case which has head==tail
    return(size()==N-1);
}
template<typename T> void DynamicQueue<T>:: grow(){
    //increases the size of the array linearly if the array is full and the new array with increased size has elements arranged, i.e, the first element lies at index zero

    if(isFull()){   //this is needed for the case when grow() is accessed from the interface/outside by the user
        unsigned int sz = N-1;
        N = nextSize(); //increase in size of the array if the array is full
        T *newA; newA = new T[N];   //temporary array with increased size if the array is full
        unsigned int newAelem = 0;
        for(unsigned int i = head; i != tail; i = (i+1)%(sz+1)){
            newA[newAelem] = A[i];  //copying of elements from primary array to the temporary array
            newAelem++;
        }
        head = 0; tail = sz;    //reassigning the head and tail after rearrangement
        A = newA;   //pointing the primary array towards the temporary array to get the desired array
    }
}
template<typename T> unsigned int DynamicQueue<T>:: size(){
    //returns the number of elements in the array
    return((N+tail-head)%N);
}
template<typename T> void DynamicQueue<T>:: QInsert(T x){
    if(isFull()) grow();    //grow the queue once the queue becomes full
    A[tail] = x;    //insertion of new element at the tail position
    tail = (tail+1)%N;
}
template<typename T> bool DynamicQueue<T>:: QDelete(T *x){
    //deletes the element at the head position by reassigning the head position to the second element in the array

    if(isEmpty()) return false; //returns false if the array is empty and there is nothing to delete
    else{
        *x = A[head];
        head = (head+1)%N;
        return true;    //returns true if the operation is preformed successfully
    }
}