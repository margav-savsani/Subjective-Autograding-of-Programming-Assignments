#include <iostream>

template <typename T> bool DynamicQueue<T>::isEmpty(){
	return(head == tail);
}

template <typename T> bool DynamicQueue<T>::isFull(){
	return(N == tail - head);
}

template <typename T> void DynamicQueue<T>::grow(){
	T *A1;
	A1 = new T[nextSize()];
	for (int i = 0; i<N; i++){
		A1[i] = A[i];
	}
	delete A;
	A = A1;
	head = 0;
	tail = N;
	N = nextSize();
}

template <typename T> unsigned int DynamicQueue<T>::size()
{
	return(tail - head);
}

template <typename T> void DynamicQueue<T>::QInsert(T x) // insert given element at tail of the queue; grow array size as necessary
{
	if (tail == N){
		if (isFull()){grow();}
		else{	
			for (int i = 0; i<tail-head; i++){
				A[i] = A[i+head];
			}
		}
		tail = size();
		head = 0;
	}
	A[tail++] = x;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x)
{
	if (isEmpty()){
		return 0;
	}
	*x = A[head];
	head++;
	return 1;
}
