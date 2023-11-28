#include<iostream>
#include"queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T>::isEmpty(){
	return (head==tail);
}	

template <typename T> bool DynamicQueue<T>::isFull(){
	return (tail==N && head==0);  
}

template <typename T> void DynamicQueue<T>::grow(){
	T* B=A;		//all the elemats of A were moved to the new array B
	A=new T[N+CONST_GROWTH]; //incremented the size of array A
	for(int i=head;i<tail;i++){
		A[i]=B[i];			//elements of B are again moved into A
	}
	N=nextSize();			//value of N is increased
}	

template <typename T> unsigned int DynamicQueue<T>::size(){
	return tail-head;		//this value returns the size of the array
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
	if (tail == N){
		if(head==0){	//this is the case of full array
			grow();		//so the size of array is increased
		}
		else{
			for(int i=head;i<N;i++){	//Initial indexes were empty,so the head was shifted to 0 index and continued the process till tail
				A[i-head]=A[i];
			}
			tail=N-head;head=0;			//after shifting ,the new tail becomes N-head and head becomes 0
		}	
	}
	A[tail]=x;							//after the shifting,x is placed at the tail
	tail++;								//later the tail is incremented
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
	if (head==tail){					//when array is empty,it returns false
		return false;
	}
	else{	
		*x=A[head];						
		head++;
		return true;
	}

}


