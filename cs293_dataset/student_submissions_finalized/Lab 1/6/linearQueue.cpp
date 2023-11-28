#include "queue.h"

template<typename T>
bool DynamicQueue<T>:: isEmpty()
{
	if(head==tail) return true;                // Both head and tail are at the same position (not necessarily 0)
	return false;
}
template<typename T>
bool DynamicQueue<T>:: isFull()
{
	if(head==0 && tail==N) return true;       
	return false;
}
template<typename T>
void DynamicQueue<T>:: grow()
{
	int M = nextSize();                 // New size of array
	T* B = new T[M];                    // New array with updated size is being created, where the pre-existing elements of array A are copied element-wise
	for(int i=0; i<N; i++)
	{
		B[i] = A[i];
	}
	A = B;                              // The new array is renamed to A for proceeding further with A 
	head = 0; tail = N; N = M;          // reassignment of tail and head and increasing variable N to updated size

}
template<typename T>
unsigned int DynamicQueue<T>:: size()
{
	return (tail - head);
}
template<typename T>
void DynamicQueue<T>:: QInsert(T x)
{
	if(isFull()) grow();
	int num = size(); 
	if(tail==N && !isFull())            // This condition occurs when the last element is at the last index but the array is not full
	{                                   // In this case, the elements are shifted to the start to make way for new elements
		for(int i=0; i++; i<num)
		A[i] = A[i+head];
		head = 0; tail = num;           // reassignment of tail and head
	} 
	A[tail] = x;                        // Insertion of new element 
	tail++;                             // Increasing tail 
}
template<typename T>
bool DynamicQueue<T>:: QDelete(T* x)
{
	if(isEmpty()) return false;
	*x = A[head]; head++; return true;  // Storing the address the head element in pointer variable x and increasing head
}
		

		
