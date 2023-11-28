#include "queue.h"

template <typename T> bool DynamicQueue <T> :: isEmpty(){
        if(head == tail)
       	        return true;
        else
	        return false;
}

/*for  Circular linked list ..if we consider having N elements as list being full ..then condition of empty and full queue is same ,..so
to avoid confusion we assume that queue is full when N- 1 elements are present in it*/

template <typename T> unsigned int DynamicQueue <T> :: size(){
    return (N -tail +head)%N;
}

template <typename T> bool DynamicQueue <T> :: isFull(){
	if(size()==N-1)          
		return true;
	else
		return false;
}

template <typename T> void DynamicQueue <T> :: grow(){
        T* B = new T[nextSize()];
        for(int j = 0; j < size();++j){
                B[j] = A[(j+head)%N];
        }

        delete(A);
        A = B;
        unsigned int temp = size();
        head = 0;
        tail = temp;
        N = nextSize();
}

template <typename T> void DynamicQueue <T> :: QInsert(T x){
        if(size() == N-1){
                grow();
                A[tail]= x;
                tail = (tail + 1)% N;                             // in case of circular array we should always convert tail/head into respective % N
                return;
        }
        else if(size() < N-1){
		A[tail]= x;
                tail = (tail + 1 )% N;
                return;
        }
}

template <typename T> bool DynamicQueue <T> :: QDelete(T* x){
	if(isEmpty())
                return false;

        else{
                *x = A[head];
		head = (head + 1) % N;
                return true;
        }
}

