#include<iostream>
using namespace std;

template <typename T> bool DynamicQueue<T>:: isEmpty(){
    if(head == tail)
        return true;
    else
        return false;
}

template <typename T> bool DynamicQueue<T>:: isFull(){
    if(tail - head == N -1)
        return true;
    else
        return false;
}

template <typename T> void DynamicQueue<T> :: grow(){
    T *B;
    unsigned int p = DynamicQueue<T> ::nextSize();
    B = new T[p];
    for(int i = 0; i < N;i++){
        //this part assigns the previous values to new queue
        B[i] = A[i];
    }
    A = B;
    N = p;
}

template <typename T> unsigned int DynamicQueue<T> :: size(){
    return (tail - head + 1);
}

template <typename T> void DynamicQueue<T> ::QInsert(T x){
	if(tail == N-1){
        	if(head== 0){
                //this part increases the size and inserts the x.
            		grow();
            		QInsert(x);
        	}
        	else {
                //this part shifts the whole queue backwards
            		for(int i = 0;i< tail - head +1;i++)
                		A[i] = A[i + head];
            		tail = tail-head;
            		head = 0;  
        	} 
        }  
    	else{
        	tail = tail + 1;
        	A[tail] = x;
    	}	
}

template <typename T> bool DynamicQueue<T> ::QDelete(T *x){
    if(isEmpty()){
        return false;
    }
    else{
        *x = A[head];
        head  = head + 1;
        return true;
    }
}
