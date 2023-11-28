#include "queue.h"

template <typename T> unsigned int DynamicQueue<T>::size(){
	if(head > tail) return N-head+tail;
	else return tail-head;
}

template <typename T> bool DynamicQueue<T>::isEmpty(){
	if(size()==0) return true;
	else return false;
}

template <typename T> bool DynamicQueue<T>::isFull(){
	if(size()==N) return true;
	else return false;
}

template <typename T> void DynamicQueue<T>::grow(){
	int n = N;
	N = nextSize();
	A = (T*)realloc(A,N*sizeof(T));
	//now after growing if we continue adding elements then order will be disrupted so rearrange the elements such that they are
	// from first to last --> oldest to latest
	if(head>int((n-1)/2)){
		//just transfer the head to end of initial array part to the end of the new array
		for(int i=head;i<n;i++){
			A[i+N-n] = A[i];
		}
		head = head + N - n;
	}
	else{
		if(head!=0){
		//just transfer the part from start to tail --> end of previous array
			for(int i=0;i<tail;i++){
				A[i+n] = A[i];
			}
		}
		tail = tail + n;
	}
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
	if(isFull()) grow();
	else{
		A[tail] = x;
		tail = (tail+1)%N;
		//circular queue so modulus needs to be taken
	}
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
	if(isEmpty()) return false;
	else{
		*x = A[head];
		head = (head+1)%N;
		return true;
	}
}
