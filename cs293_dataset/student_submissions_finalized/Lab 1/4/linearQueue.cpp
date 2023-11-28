#include "queue.h"
template<typename T> 
unsigned int DynamicQueue<T>:: size(){
   return(tail-head);//the size of linear queue is defined here
}

template<typename T>
bool DynamicQueue<T>::isFull(){//this function is to check weather the queue is full or not
    if(tail==(N)){//if the tail become equal to N then the the queue is considered as full 
        return(true);
    }
    else{
      return false;
     }
}

template<typename T>
bool DynamicQueue<T>:: isEmpty(){//this function is to check weather the queue is empty or not
    if(head == tail){//if head become equal to tail then the queue is empty
        return(true);
    }
    else{
      return false;
     }
}

template<typename T>
void DynamicQueue<T>::grow(){//this is grow function called when the queue is full we require to add more elements to it
    if(isFull()){
        T *B;
        B = new T[nextSize()];//a new array is defined here which has greater size than the queue which is full
        for(int i=0;i<=N;i++){
            B[i]=A[i];//the for loop is to copy all the elemets of of older queue to the new queue created
        }
        A=B;
        N = nextSize();
    }
}

template<typename T>
void DynamicQueue<T>::QInsert(T x){//this function is to insert elements in the queue 
    if(isFull()){// if the queue gets full then grow function is called to increase the size of the array to add more elemets
        grow();
    }
    A[tail] = x;//once the new array of new size is created then we start insert more elemts to it. Element is inserted at tail and the value of tail is increased
    tail=tail+1;  
}
template<typename T>
bool DynamicQueue<T>::QDelete(T *x){//the function is ysed to delete elements from the queue
    if(isEmpty()){//if queue is empty then it would return false
        return(false);
    }
    else{
        *x= A[head];//pointer of head is shifted to next element to the head and the element which previously was head is delted from the queue
        head=head+1;
        return true;
    }
}

