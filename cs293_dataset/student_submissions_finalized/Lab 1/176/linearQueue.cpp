#include <iostream>
using namespace std;
#include "queue.h"

template<typename T>
bool DynamicQueue<T>::isEmpty(){
    return (head==tail);            // queue empty when head and tail point to same index
}

template<typename T>
bool DynamicQueue<T>::isFull(){
    return N==size();               // queue full when the no. of elements equals total capacity 
}

template<typename T>
void DynamicQueue<T>::grow(){
    unsigned int n = nextSize();        // stores size of larger array
    T *a = new T[n];                    // dummy array to transfer elements
    for(unsigned int i=0; i<N; i++)
        a[i] = A[i];                    // copying elements to new array
    delete[] A;
    A = a;                              // dummy array is nnow our primary array
    N = n;                              // size of array has increased
}

template<typename T>
unsigned int DynamicQueue<T>::size(){
    return tail-head;                   // tail index - head index gives no. of elements
}

template<typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isFull()){
        grow();                         // if queue is full we grow it to a larger size befor inserting
        A[tail] = x;                    // insertion of element
        tail+=1;                        // increment of tail index
    }
    else{
        if(tail!=N){                    // if tail isn't pointing out of array bounds we normally insert 
            A[tail] = x;
            tail+=1;
        }
        else{                                           // if tail points out of bounds but isnt full (empty spaces at the start of array)
            for(unsigned int i=0; i<size(); i++)
                A[i] = A[i+head];                       // shifting of elements to the start of array to free space at end 
            tail-=head;                                 // tail also shifts accordingly
            head=0;                                     // since the array starts for the first index
            A[tail] = x;                                // normal insertion
            tail+=1;
        }
        // cout << head <<" " << tail <<endl;
        // for(unsigned int i=head; i<tail; i++)
        //     cout<<A[i]<<" ";
        // cout<<endl;
    }
}

template<typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty())
        return false;                                   // can't delete element from empty array
    *x = A[head];                                       // x stores the element to be deleted
    head+=1;                                            // increment head by 1 to mimic deletion of element
        // for(unsigned int i=head; i<tail; i++)
        //     cout<<A[i]<<" ";
        // cout<<endl;
    return true;
}