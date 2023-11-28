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
		// creating new array of incresed size and coping the elements to it 
		int a = nextSize();
		N = a;
		T *B = new T[N];
		for (int i = head; i < ((a - CONST_GROWTH) + head); i++)
		{
			B[i] == A[((a - CONST_GROWTH) + head) % (a - CONST_GROWTH)];
		}	// coping the elemts in the queue order 
		A = B;	// chaning the pointer to the new one

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
			tail = tail % N;
		}
		else if (dummy::no_of_ele == N)
		{
			grow();	//if the queue is full incresing the size of queue
			if (head != 0)
			{
				tail = tail + N - CONST_GROWTH;
			}
			A[tail] = x;
			tail = tail + 1;
			tail = tail % N;
		}
		else
		{
			A[tail] = x;
			tail = tail + 1;
			tail = tail % N;
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
