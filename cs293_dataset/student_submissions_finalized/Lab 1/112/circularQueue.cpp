template <typename T> bool DynamicQueue<T>::isEmpty() {
	return head == tail;		// head == tail  taken to be empty by convention
}

template <typename T> bool DynamicQueue<T>::isFull() {
	return size() == N-1;		// size cannot be N because of above convention
}

template <typename T> void DynamicQueue<T>::grow() {
	N = nextSize();
	T* nextA = new T[N];
	for(int i=0; i<N-CONST_GROWTH; i++) {
		nextA[i] = A[i];
	}
	delete[] A;
	A = nextA;
	if (tail < head) {		// need to wrap a few elements after growing in this case
		for(int index = 0; index<tail; index++) {
			A[(5*N+index-CONST_GROWTH)%N] = A[index];	// 5N ensures positivity as long as CONST_GROWTH is not absurdly big
		}
		tail = (5*N+tail-CONST_GROWTH)%N;
	}
}

template <typename T> unsigned int DynamicQueue<T>::size() {
	return (N+tail-head) % N;
}

template <typename T> void DynamicQueue<T>::QInsert(T insertMe) {
	if(size() == N-1) {		// cannot simply insert at tail. we need to make some room
		grow();
	}
	A[tail] = insertMe;
	tail = (tail+1)%N;
}

template <typename T> bool DynamicQueue<T>::QDelete(T* deletedElement) {
	if (isEmpty()) {
		return false;
	}
	*deletedElement = A[head];
	head= (head+1)%N;
	return true;
}