// The major difference compared to linearQueue implemetation is the use of modular arithmetic

template<typename T> bool DynamicQueue<T>::isEmpty(){
	return (size() == 0);
}

template<typename T> bool DynamicQueue<T>::isFull(){
	return (tail == -1);
}

template<typename T> unsigned int DynamicQueue<T>::size(){
	if (isFull()) return N;
	return (tail - head + N) % N; // This formula allows us to bypass different calculations which could have arose depending on different positions of head and tail
}

template<typename T> void DynamicQueue<T>::grow(){
	T* tmp = new T[nextSize()]; // Creating a new array of greater size
	for(int i = 0; i < N; i++){
		tmp[i] = A[(i + head)%N]; // Copying elements, such that the head element in A is the first element in tmp
	}
    delete(A); // Freeing up memory 
	A = tmp; // Giving A the address of the new array
	head = 0; tail = N; N = nextSize();

}

template<typename T> void DynamicQueue<T>::QInsert(T x){
	if(isFull()) grow(); // Growing array if full
	int s = size(); // This is aking a to taking a temporary copy of size for future use
	A[tail%N] = x; tail = (tail + 1)%N; // Adding the element, and incrementing tail as per modular arithmetic
	if(s == N-1) tail = -1; // tail = -1 signifies that the queue is now full
}

template<typename T> bool DynamicQueue<T>::QDelete(T* x){
	if(isEmpty()) return false;
	if (isFull()) tail = head; // Accounting for the fact that an element has been deleted
	*x = A[head]; head = (head+1)%N; 
	return true;
}
