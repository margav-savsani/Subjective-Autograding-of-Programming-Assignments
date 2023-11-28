#include<iostream>
#include"queue.h"

using namespace std;

template <typename T> unsigned int DynamicQueue<T>::size(){
	return ((tail-head+N)%N);			//this value returns the size of the array
}

template <typename T> bool DynamicQueue<T>::isEmpty(){
	return (head==tail);		
}	

template <typename T> bool DynamicQueue<T>::isFull(){
	if(size() == N-1)return true;		//if size is N-1 , it means the array is full
	else return false;
}	

template <typename T> void DynamicQueue<T>::grow(){
	T* B=A;							//all the elemats of A were moved to the new array B
	A=new T[N+CONST_GROWTH];		//incremented the size of array A

	if(head==0 && tail==N){
		for(int i=0;i<tail;i++){
			A[i]=B[i];				//elements of B are again moved into A
		}
	}
	N=nextSize();					//value of N is increased

	if(head==tail+1){				//this is the case when head>tail
		head+=CONST_GROWTH;
		for(int i=0;i<tail;i++){	
			A[i]=B[i];				//again similiarly elements of B are copied into A
		}
		for(int i=head;i<N;i++){	//this is case after head and N are increased
			A[i]=B[i-CONST_GROWTH];
		}
	}
}	

template <typename T> void DynamicQueue<T>::QInsert(T x){
	if(isFull()){
		grow();						//when array is full ,it needs to be growed and then the element should be added
		A[tail]=x;
		tail++;
	}
	else if(tail==N-1){				//when tail=N and queue is not full A[0] beacomes x and then tail is shifted to 1
		A[0]=x;
		tail=1;
	}
	else{
		A[tail]=x;					//this is the general case
		tail++;
	}
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
	if (head==tail){				//when array is empty,it returns false
		return false;
	}
	else{							
		if(head==N-1){				//when head is N-1 then new head becomes 0 	
			*x=A[head];
			head=0;
		}
		else{
			*x=A[head];				//this is the usual case
			head++;
		}
		return true;
	}
}


