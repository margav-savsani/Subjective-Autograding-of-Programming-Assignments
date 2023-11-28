template <typename T>  bool DynamicQueue<T> ::  isEmpty(){ // if tail is in same position as head means that is an empty Queue.


	return head == tail;
	
}

template <typename T>  bool DynamicQueue<T> ::  isFull(){ // if the elements between tail and head is equal to N then the Queue is full.


	return tail-head == N;
	
}

template <typename T> void DynamicQueue<T> :: grow(){ // when we want to increase the size A, create B of nextSize(), insert elements of A into B, delete A, then equate B to A. By this way we are actually increasing the size of pointer A. 


	T* B;
	
	B = new T[nextSize()];
	for( int i=0; i< N; i++){
	
		B[i] = A[i];
	}
	
	delete A;
	A = B;

	N = nextSize();
	
}

template <typename T> unsigned int DynamicQueue<T> :: size(){ // returns number of elements between head and tail.

	
	return  tail - head;
	
}

template <typename T>  void DynamicQueue<T> :: QInsert(T x){ 



	if( isFull() ) { // if Queue is full, the Queue size will grow.
	
		grow();
	}
	
	else{
	
		if( tail == N){ // if Queue is not full but tail reached to end, then shift the queue by head positions forward, so the pointer positions wont be wasted.
		
			for( int i=0; i< tail-head; i++){
			
				A[i] = A[i+head];
			}
			tail = tail-head;
			head = 0;
		}
	}
	A[tail++] = x;
	
}
	

template <typename T> bool DynamicQueue<T> :: QDelete(T *x){ // delete the first element in the queue.


	if( ! isEmpty() ){
	
		*x = A[head];
		
		head = (head+1);
		
		return true;
		
	}
	
	return false;
}
	
		
		
		
		
		


		
