template <typename T>
bool DynamicQueue<T>::isEmpty(){
	// checks if queue is empty
   	return head == tail;
}

template <typename T>   
bool DynamicQueue<T>::isFull()
{
  	//checks if the queue is full. We only insert N-1 elements in the queue
  	return size() == N-1;
}

template <typename T>  
void DynamicQueue<T>::grow() 
{
 	// If the queue is full, then grow it
  	// Create new array and copy elements into new array
  	
  	int oldSize = N-1;
  	int newSize = nextSize();
  	T *B;
  	B = new T[newSize];
  	
  	// copying elements to new array
  	for(int i=0; i < oldSize; i++)
  	{
  		B[i] = A[(head+i)%N];
  	}
  	A = B;
  	N = newSize;
  	return;
}
  
template <typename T>  
unsigned int DynamicQueue<T>::size()
{
  	// Number of elements in the queue
  	return (N-head+tail)%N;
}

template <typename T>  
void DynamicQueue<T>::QInsert(T x)
{
  	// Insert element x into the queue. If need be then grow the queue.
  	
  	if(isFull()) grow();
  	
  	A[tail] = x;
  	tail = (tail + 1)%N;
  	return;
  	
}
template <typename T>  
bool DynamicQueue<T>::QDelete(T *x)
{
  	// delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
  	if(isEmpty()) return false;
  	
  	x = &A[head];
  	head = (head + 1)%N;
  	return true;
}
