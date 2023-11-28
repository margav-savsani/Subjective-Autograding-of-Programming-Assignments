template <typename T> bool DynamicQueue<T>::isEmpty() {
	return head == tail;
}

template <typename T> bool DynamicQueue<T>::isFull() {
	return size() == N;
}

template <typename T> void DynamicQueue<T>::grow() {
	N = nextSize();
	T* nextA = new T[N];		// next value of A
	for(int i=head; i<tail; i++) {
		nextA[i] = A[i];
	}
	delete[] A;
	A = nextA;
}

template <typename T> unsigned int DynamicQueue<T>::size() {
	return tail-head;
}

template <typename T> void DynamicQueue<T>::QInsert(T insertMe) {
	if(tail == N) {		// cannot simply insert at tail. we need to make some room
		if (head >= CONST_GROWTH) {	// shift all elements backwards so that head becomes 0
			int shiftLength = head;
			for(int index=head; index<tail; index++) {
				A[index-shiftLength] = A[index];
			}
			head -= shiftLength;
			tail -= shiftLength;
		}
		else {
			grow();		// if shifting is not worth it
		}
	}
	A[tail] = insertMe;
	tail++;
}

template <typename T> bool DynamicQueue<T>::QDelete(T* deletedElement) {
	if (isEmpty()) {
		return false;
	}
	*deletedElement = A[head];
	head++;
	return true;
}
