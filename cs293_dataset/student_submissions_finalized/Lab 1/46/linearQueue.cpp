template <typename T> bool DynamicQueue<T>:: isEmpty() {
  if(tail == 0) {
    return true; // is empty if tail is at 0
  }
  return false;
}

template <typename T> bool DynamicQueue<T> :: isFull() {
  if(tail==N && head==0) {
    return true; // is full if tail reaches the end of the queue.
  }
  return false;
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
  return N;    // returning the size of the queue
}

template <typename T> void DynamicQueue<T> :: grow() {
  int tmp = N;
  N = nextSize(); // calling nextsize function for the increase of size of the queue.
  T *B = new T[N];
  for(int i=0; i<tmp; i++) {
    B[i] = A[i];  // copying all the prev. elements to new array.   
  }
  A = B;
  B = NULL;
}

template <typename T>  void DynamicQueue<T> :: QInsert(T x) {
  if(isFull()) {
    grow();     // growing to next size if the queue is full.
  }
  if(tail==N && head!=0) {
    for(int i=0; i<N-head; i++) {
      A[i] = A[head+i];
    }
    tail = N-head;
    head = 0;
  }
  A[tail] = x;  // inserting new element at the end.
  tail++;
}

template <typename T> bool DynamicQueue<T> :: QDelete(T *x) {
  if(isEmpty()) {
    return false;
  }
  *x = A[head];
  head++;     // updating the head after deletion.
  return true;
}



