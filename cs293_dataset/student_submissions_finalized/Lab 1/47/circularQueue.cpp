
template <typename T>  bool DynamicQueue<T> ::  isEmpty(){  // if tail is in same position as head means that is an empty Queue.

	return head == tail;
	
}

template <typename T>  bool DynamicQueue<T> ::  isFull(){ // According to our convention, if tail == N then, the Queue is full.

	return tail == N;
	
}

template <typename T> void DynamicQueue<T> :: grow(){ //when we want to increase the size A, create B of nextSize(), insert elements of A into B, delete A, then equate B to A. By this way we are actually increasing the size of pointer A. 



	T* B;
	
	B = new T[nextSize()];
	
	if( head == 0 ){
	
		for( int i=0; i< N; i++){
	
			B[i] = A[i];
		}
		
	}
	else{ // if head is not at zero index, then move (head to N) index elements to the last. (to save time) 
	
		for( int i=0; i< head; i++){
	
			B[i] = A[i];
		}
		
		for( int i = head; i<N ; i++){
	
			B[CONST_GROWTH+i] = A[i];
		}
			
		tail = head;
		head = head + CONST_GROWTH;
				
	 		
	}	
	
	
	
	delete A;
	A = B;
	
	
	N = nextSize();
	
}

template <typename T> unsigned int DynamicQueue<T> :: size(){ // returns the size of the queue.


	if ( isFull() ){
	
		return N;
	}
	else {
		
		return (N + tail - head)%N;
	}
	
}

template <typename T>  void DynamicQueue<T> :: QInsert(T x){ 
	
	
	
	if( (tail+1)%N == head ){ // if next to tail there is head, then equate tail to N, to keep track of full queue cases.
	
		A[tail] = x;
		tail = N;
		return;
	}
	
	else if ( tail == N ){ 
	
		grow(); // if queue is full, then grow the size of pointer
		
		A[tail] = x;
		tail++;
	}
	
	else {
	
		A[tail] = x;
		tail = ( tail+1 ) %N;
	}
	
	
}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x){ // delete the element in the first.

	if( ! isEmpty() ){ 
	
		*x = A[head];
		
		head = (head+1)%N;
		
		return true;
		
	}

	return false;
}
	







