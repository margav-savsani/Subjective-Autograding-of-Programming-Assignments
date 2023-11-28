template <typename T> bool DynamicQueue<T>::isEmpty(){
	return (size() == 0);
}
template <typename T> bool DynamicQueue<T>::isFull(){
	return (size() == N);
}

template <typename T> unsigned int DynamicQueue<T>::size(){
	return tail-head;
}

template <typename T> void DynamicQueue<T>::grow(){
	if(isFull()){ // Pre-cautionatory code; so that grow can happen only if the Queue is full
		T* tmp = new T[nextSize()]; // A new array of greater size
		for(int i = 0 ; i < N; i++) tmp[i] = A[i]; // Copying elements
		delete(A); // Freeing up previous memory
		A = tmp; // Setting A to a new address
		head = 0; tail = N; N = nextSize();
	}
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
	if(isFull()) grow(); // Growing if the array is full
	else{
		if (tail == N){ // Shifting elements if end of array is reached, but head is not 0
			for (int i = head; i < tail; i++){
				A[i-head] = A[i]; // Actual shifting
			}
			tail = size(); head = 0;
		}
	}
	A[tail++]=x;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
	if(isEmpty()) return false; 
	*x = A[head++];
	return true;
}
