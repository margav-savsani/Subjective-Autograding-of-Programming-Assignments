#include<iostream>
using namespace std;
#include"queue.h"

#define CONST_GROWTH 1000
#define INIT_SIZE 1000

// if tail is same as head, the queue is empty otherwise its not
template <typename T>bool DynamicQueue<T>:: isEmpty(){
	if(tail==head)return true;
	else{
	return false;
	}
}

// returns true if Queue is full otherwise returns false size has to be equal to N so that no position in the array gets wasted
template <typename T>bool DynamicQueue<T>:: isFull(){
	if(size()==N) return true;
	else{
	return false;
	}
}

template <typename T>void DynamicQueue<T>:: grow(){// if the queue becomes full, it grows to by the constant defined
	//if queue becomes full
	if(isFull()){
		N=nextSize();
		T* B;
		B=new T[N];
		int k=0;
		//if head<tail a new array is created and elements are copied into it
		if(head<tail){
			for(int i=head;i<tail;i++){
				B[k]=A[i];
				k++;
			}
		}
		// if head>tail, then first elements from the head to the end of the array are copied
		else{
			for(int i=head;i<N-CONST_GROWTH;i++){
				B[k]=A[i];
				k++;
			}
			//then elements beginning from 0 to the tail are copied
			for(int i=0;i<tail;i++){
				B[k]=A[i];
				k++;
			}
		}
		A=B;
		head=0;
		tail=k;
	}
	return;

}

//function returns the size of the array
template <typename T>unsigned int DynamicQueue<T>:: size(){
    if(tail==N){// this indicated that the queue is full
        return N;
    }

	else{
		return (N-head+tail)%N;

	}
}

// inserts an element in the array in a circular fashion
template <typename T>void DynamicQueue<T>:: QInsert(T x){
	if(isFull()){
		grow();
	}
	A[tail]=x;
	//tail is incremented in a circular fashion
    if((tail+1)%N==head){
        tail=N;
        return;
    }
	else{
		tail=(tail+1)%N;
	}
	return;
}

// deletes an element in the array
template <typename T>bool DynamicQueue<T>:: QDelete(T* x){
// if the array is not empty, an element from the head is deleted
	if(size()!=0){
        if(tail==N){// as the head is deleted tail again returns to where it should have been
            tail=head;
        }
		*x=A[head];
		A[head]=-1;// giving an arbitary value to the deleted element
		head=(head+1)%N;
		return true;
	}
	else{
	return false;
	}
}
