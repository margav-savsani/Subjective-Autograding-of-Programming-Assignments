#include <iostream>
#include "queue.h"

namespace dummy
{
	int no_of_ele = 0;
}	// using this to keep track of no of elements and intialising it to zero

template < typename T>
	bool DynamicQueue<T>::isEmpty()
	{
		if (dummy::no_of_ele == 0)
		{
			return true;
		}
		else return false;
	}

template < typename T>
	bool DynamicQueue<T>::isFull()
	{
		if (dummy::no_of_ele == N)
		{
			return true;
		}	// if no of elements is N then returns true
		else return false;
	}

template < typename T>
	void DynamicQueue<T>::grow()
	{
		int a = nextSize();
		N = a;
		T *B = new T[N];	// creating new array of incresed size and coping the elements to it 
		for (int i = 0; i < (a - CONST_GROWTH); i++)
		{
			B[i] == A[i];
		}
		delete[] A;	// coping the elements to new array and deleting the old pointer and giving the new pointer 
		A = B;
	}

template < typename T>
	void DynamicQueue<T>::QInsert(T x)
	{
		if (isEmpty())
		{
			// checks if empty and inserts the element at some random position in queue
			int k = rand() % N;
			head = k;
			A[k] = x;
			tail = k + 1;
		}
		else if (tail == N)
		{
			// as intialised from from anywhere in between queue when tail reaches end it can be bcuz the queue is full or it needs to shift to the first

			if (isFull())
			{
				grow();	// if full grows the size of array first and then inserts a element and updates the tail
				A[tail] = x;
				tail = tail + 1;
			}
			else
			{
				// shifting the queue to the start and updating the head and tail
				T *B = new T[N];
				for (int i = head; i < tail; i++)
				{
					B[i - head] = A[i];
					//delete[]A;
					A = B;
					tail = tail - head;
					head = 0;
				}
				A[tail] = x;
				tail = tail + 1;
			}
		}
		else
		{
			if (tail != N)
			{
				// if queue is not full then inserting the elment to the end
				A[tail] = x;
				tail = tail + 1;
			}
		}
		dummy::no_of_ele++;	// updating size after every insertion
	}

template < typename T>
	unsigned int DynamicQueue<T>::size()
	{
		return dummy::no_of_ele;
	}

template < typename T>
	bool DynamicQueue<T>::QDelete(T *x)
	{
		if (isEmpty())
		{
			return false;
		}
		else
		{
			x = &A[head];	//returns the pointer of the deleted element 
			head++;	// as element is deleted shifting head and decresing no of elements
			dummy::no_of_ele--;
		}
		return true;
	}
