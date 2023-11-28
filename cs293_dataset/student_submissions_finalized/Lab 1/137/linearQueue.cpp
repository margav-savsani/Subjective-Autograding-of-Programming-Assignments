#include<iostream>
#include "queue.h"
using namespace std;

template <typename T> bool DynamicQueue<T>::isFull(){
//Checking if the queue is full or not
    if(head == 0 && tail == N)
        {
            return 1;
        }
    return 0;
}

template <typename T> bool DynamicQueue<T>::isEmpty(){
//Cheking if the queue is empty or not 
    if(head == tail)
    {
        return 1;
    }
    return 0;
}

template <typename T> void DynamicQueue<T>::grow(){
//Function to increase the size of the queue
    T* queue = new T[nextSize()];                    //Creating a temporary queue with size CONST_GROWth more than the current size
        for(int i=0 ; i<nextSize(); i++)              
        {
            if(i<N) 
            {
                queue[i] = A[i];                           //Copying the elements of the current queue to the temporary queue
            }
            else
            {
                queue[i] = 0;
            }
        }
    delete[] A;                                            //Deleting the old array
    A = queue;                                             //Providing the value of pointer of the temporary queue to the pointer of actual queue
    queue = NULL;                                          //Deleting the value of pointer of temporary queue
    N = nextSize();                                  //Increamenting the size of queue by CONST_GROWTH
}

template <typename T> unsigned int DynamicQueue<T>::size(){
//Function to calculate the size of the queue
    return tail - head;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
//Function to insert a new element in the queue
    if(isFull())                                            //Increasing the size of the queue if it is full
    {
        grow();                                             //Executing grow function to increase the size of queue
        A[tail] = x;                                        //Inserting the element in the queue
        tail++;                                             //Increamenting the tail
    }
    else if(head != 0 && tail == N)                         //Evaluating condition where queue is empty at the begining
        {
            T* queue = new T[N];                            //Creating a temporary queue
            for(int i=0; i<N; i++)
            {
                if(i + head<tail)
                {
                    queue[i] = A[i + head];                 //Copying the current queue in the temporary queue
                }
                else
                {
                    queue[i] = 0;
                }
            }
            delete[] A;                                     //Deleting the old queue
            A = queue;                                      //Providing the value of pointer of the temporary array to the pointer of old array
            queue = NULL;                                   //Deleting the value of pointer of temporary queue
            tail = N - head;                                
            head = 0;
            A[tail] = x;                                    //Inserting the new element at the back of quueue
            tail++;                                         //Increamenting tail
        }
    else
    {
        A[tail] = x;                                        //Inserting the new element at the back of quueue
        tail++;                                             //Increamenting tail
    }
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
//Function to delete an element in the queue
    if(isEmpty())                                           //Evaluating the condition of the queue is empty or not
    {
        return false;
    }
    else
    {
        *x = A[head];                                       //Equating the value of head of the queue to the reference variable
        A[head] = 0;         
        head++;                                             //Increamenting head
        return true;                                        
    }
}