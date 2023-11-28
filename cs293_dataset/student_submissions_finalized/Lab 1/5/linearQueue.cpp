template <typename T>
bool DynamicQueue<T>::isEmpty(){
	// checks if queue is empty
   	return head == tail;
}

template <typename T>   
bool DynamicQueue<T>::isFull()
{
  	//checks if the queue is full
  	return tail == N;
}

template <typename T>  
void DynamicQueue<T>::grow() 
{
 	// If the queue is full, then grow it
 	//Two cases arise.
  	// case 1) .If the queue is actually full, i.e. head = 0 and tail = N, create new array of bigger size.
  	if(size() == N)
  	{	
  		int oldSize = tail - head;
  		int newSize = nextSize();
  		T *B;
  		B = new T[newSize];
  		
  		// copying elements to new array
  		for(int i=0; i < oldSize; i++)
  		{
  			B[i] = A[i];
  		}
  		A = B;
  		N = newSize;
  	}
  	// case 2). If the queue is not actually full because head is not 0 and tail = N.
  	else
  	{
  		// actual cappacity of array
  		int currSize = size();
  		
  		// shifting elements in the original array
  		for(int i=0 ;i<currSize; i++)
  		{
  			A[i] = A[head + i];
  		}
  		head = 0;
  		tail = currSize;
  	}
  	return;
}
  
template <typename T>  
unsigned int DynamicQueue<T>::size()
{
  	// Number of elements in the queue
  	return (tail-head);
}

template <typename T> 
void DynamicQueue<T>::QInsert(T x)
{
  	// Insert element x into the queue. If need be then grow the queue.
  	
  	if(isFull()) grow();
  	
  	A[tail++] = x;  	
  	return;
}

template <typename T>  
bool DynamicQueue<T>::QDelete(T *x)
{
  	// delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
  	if(isEmpty()) return false;
  	
  	x = A + head;
  	head++;
  	return true;
}
  
