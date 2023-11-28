												Lab 1

1) linearQueue.cpp:

		In linearQueue, consecutive elements in the queue are stored atarray locations with consecutive indices.  Thus, the first element in linearQueue must always be atthe array location with the smallest index (need not be 0) compared to other elements in linearQueue.As an example, if linearQueue is implemented using an array A of size 10, and if there are 3elements in the queue, the consecutive elements could be at locations A[3], A[4], A[5].
		
Functions Implemented:

	a) isEmpty() :-  When there is no element in the queue, head and tail will be at the same index.So, when queue is empty, head and tail will be equal
	b) isFull()  :-  When the queue is full, size of the queue will be equal to the current size of the array i.e, tail-head==N
        c) grow()    :- To grow an array A to its next size, we have to create a new array say B with size equal to the next size of array A and copy the elements filled in A intothe array B. Now 				delete the current array A and equate it to B.
        d) QInsert(T x) :- When we insert an element into the queue, we have to update tail to its next value.If the size of the array is full we have to grow it to the next size first and then insert. 				    if the array is not full and the last element is at the last index of the array we have to shift the array such that head becomes 
			    zero instead of growing the array unnecessarily
        e) size() :- return the current number of elements in the queue .
        f) QDelete(T*x) :- delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise .


 2) circularQueue.cpp :
 
		In Circular Queue , circularQueue, consecutive elements in the queue are stored at array locations that are consecutive *modulo the array size*.  Thus, the first element in
 circularQueue may not always be at the array location with the smallest index compared to other elements in circular queue .As an example, if circularQueue is implemented using an array A of size 10, 
 and if there are 3 elements in the queue, the consecutive elements could be at locations A[9], A[0], A[1].	
 
Functions Implemented:

	a) isEmpty() :-  When there is no element in the queue, head and tail will be at the same index.So, when queue is empty, head and tail will be equal
	b) isFull()  :-  We consider the queue is full when size of the queue as N-1.
        c) grow()    :-  First I have created a new array and then we need two different cases 1) when the tail is greater than head then we can directly copy the elements.
        		  2) when the tail is less than head we need to divide the elements into two cases.
        d) QInsert(T x) :- When we insert an element into the queue, we have to update tail to its next value.If the size of the array is full we have to grow it to the next size first and then insert. 
        e) size() :- return the current number of elements in the queue .
        f) QDelete(T*x) :- delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise .
