template <typename T> bool DynamicQueue<T>::isEmpty() {
	if(tail-head==0) return true; //the case where head index and index where next element will be stored are equal, is taken to be the case for empty queue is case of circular queue implementation
	return false;
}

template <typename T> bool DynamicQueue<T>::isFull() {
	if(size()==N-1) return true; //in circular queue, we declare the queue to be full when the array contains N-1 elements to resolve ambiguity of full or empty
	if(N==0) return true;
	return false;
}

template <typename T> unsigned int DynamicQueue<T>::size() {
	int a; 
	if(tail>=head) a = (tail-head); //if tail comes after head, size is simply calculated as in case of linear queue
	else a = N-head+tail; //if tail comes before head, the queue contains N-head+tail number of elements
	return a;
}

template <typename T> void DynamicQueue<T>::grow() {
	int n=nextSize(); 
	T *B = new int[n];
	if(N==0) A=B;
	else{
		if((tail>=head)&&(head==0)) {
			for(int i=0; i<N-1; i++){ //similar to copying in case of linear queue
				B[i]=A[i];
			}
		}
		else if((tail>=head)&&(head==1)) {
			for(int i=1; i<N; i++){ //similar to copying in case of linear queue
				B[i-1]=A[i];
			}
		}
		else { //the new array contains head at 0 and tail at N-1
			for(int i=head; i<N; i++){ 
				B[i-head]=A[i];
			}
			for(int i=0; i<tail; i++){
				B[i+N-head]=A[i];
				}
		}
	A=B;
	head=0;
	tail=N-1;
	N=n;
	}
}

template <typename T> void DynamicQueue<T>::QInsert(T x) {
	if(isFull()) grow(); //if queue is full, grow the array
	A[tail]=x; //allot x to tail index
	if((!isFull())&&(tail>=N-1)){ 
		tail=0; //if tail reaches end, we allot tail to be equal to 0 in circular queue
	}
	else tail++;	
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x) {
	bool a = isEmpty();
	if(a) return false;
	*x=A[head]; //if the queue is not empty, we remove the head element by increasing head index by 1
	if(head>=N-1) head=0; //if head reaches end, we allot head to be equal to 0 in circular queue
	else head++; //since all operations are done on head to tail elements, the previous head element is essentially gone
	return true;
}