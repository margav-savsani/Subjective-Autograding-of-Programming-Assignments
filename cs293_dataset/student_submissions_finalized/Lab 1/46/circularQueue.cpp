template <typename T> bool DynamicQueue<T>:: isEmpty() {
	if(head==tail) {
		return true;   // this happens when the queue is empty
	}
	return false;
}

template <typename T> bool DynamicQueue<T>:: isFull() {
	if(size()==N-1) {
		return true;  // this happens when the element inserted at last free position in the queue.
	}
	return false;
}

template <typename T> unsigned int DynamicQueue<T>:: size() {
	return (N-head+tail)%N;    // returning the current size.
}

template <typename T> void DynamicQueue<T>:: grow() {
  int tmp = N;
  int u = head, v = 0;
  N = nextSize(); // calling nextsize function for the increase of size of the queue.
  T *B = new T[N];
  head = 0;

  for(int i=0; u<N; i++) {
    B[i] = A[u];  // copying all the prev. elements to new array.
    u++;
    v = i;   
  }

  for(int i=0; i<tail; i++) {
    B[v] = A[i];   // copying elements part-2
    v++;
  }
  tail = tmp-1;   // this will be the new position of tail in new queue.
  A = B;
  B = NULL;
}

template <typename T> void DynamicQueue<T>:: QInsert(T x) {
	if(isFull()) {
		grow();  // growing to next size if the queue is full.
	}
    A[tail] = x;
    tail = (tail+1)%N;  // inserting new element at the end.
}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x) {
  if(isEmpty()) {
    return false;  // can't delete a element if there is none.
  }
  *x = A[head];
  head=(head+1)%N; // updating head value after deleting the first element.
  return true;
}