#include "queue.h"
//assuming that empty arrays are both empty and full at the same time

template <typename T>
bool DynamicQueue<T>::isEmpty(){
    if(size() == 0){     //true if no elements in the queue
        return true;
    }
    return false;
}

template <typename T>
bool DynamicQueue<T>::isFull(){
    if(size() == N){    //true if all N slots are filled
        return true;        
    }
    return false;
}

template <typename T>
void DynamicQueue<T>::grow(){
    T* B = new T[nextSize()];     //allocate new heap memory
    int ind = head;
    int sz = size();
    for(int i = 0; i < sz; i++){  //copy all the elements to the new array
        B[i] = A[ind];
        ind = ind+1;
    }
    delete[] A;  //delete the old array
    A = B;      //assign the new array pointer to A
    head = 0;
    tail = sz;
    N = nextSize();  //increase the value of N accordingly 
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
    return (tail-head);   //distance between head and tail is the size
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){   
    
    if(isFull()){    //if queue is already full, then grow
        
        grow();                   
    }
    
    else if(tail == N){  //if the tail is at the end, then shift everything to left
        int sz = size(); 
        int temp = head;
        
        for(int i = 0; i < sz; i++){
            A[i] = A[temp+i];
        }

        head = 0;
        tail = sz;        
    }
    A[tail] = x;   //store the element at the tail index in the array
    tail += 1;  //move tail to the next index
}

template <typename T>
bool DynamicQueue<T>::QDelete(T* x){
    if(isEmpty()){    //return false if empty
        return false;
    }
    *x = A[head];   //store the front element in *x
    if(head == N-1){
        head = 0;
        tail = 0;
        return true;
    }
    head = head+1;    //increment head, equivalent to removing the top element

    return true;
}