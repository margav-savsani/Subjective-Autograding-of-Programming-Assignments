#include "queue.h"

template<typename T>
bool DynamicQueue<T>:: isEmpty()
{
	if(head==tail) return true;
	return false;
}
template<typename T>
bool DynamicQueue<T>:: isFull()
{
	if(tail==-1) return true;         // For both empty and full comdition, the position of head and tail is the same. 
	                            	  // To differentiate the cases, tail is assigned -1 if about to become full on inserting an element
	return false;
}
template<typename T>
void DynamicQueue<T>:: grow()
{  
	int M = nextSize();               // New size of array
	T* B = new T[M];                  // New array with updated size is being created, where the pre-existing elements of array A are copied element-wise
	for(int i=0; i<N; i++)
	{
		B[i] = A[i];
	}
	A = B;                            // The new array is renamed to A for proceeding further with A
	head = 0; tail = N; N = M;        // reassignment of tail and head and increasing variable N to updated size

}
template<typename T>
unsigned int DynamicQueue<T>:: size()
{
	if(isFull()) return N;
	return (tail - head + N) % N;
}
template<typename T>
void DynamicQueue<T>:: QInsert(T x)
{
	if(isFull()) 
	{
		tail = head;                  // tail, which was assigned -1 for differentiating purposes is reassigned its original value
		T* B = new T[N];              // new array with same size is created
		for(int i=0; i<N; i++)
		{
			B[i] = A[(i + head)%N];   // ordering the elements with head element at 0 and tail at N
		}
		A = B;
		grow();                       // After ordering of elements, array is enlarged
	}
	int num = size();  
	A[tail%N] = x;                    // Insertion of new element
	tail=(tail+1)%N;                  // Circular precautions
	if(num==N-1) tail = -1;           // If before insertion of element, size was N-1, array will become full after insertion, hence tail is assigned -1
}
template<typename T>
bool DynamicQueue<T>:: QDelete(T* x)
{
	if(isEmpty()) return false;
	if(isFull()) tail = head;         // If array is full, tail will be -1, hence its real value is re-established here
	*x = A[head]; head = (head+1)%N;  // Storing the address the head element in pointer variable x and increasing head with circular precautions 
	return true;
}
		

		
