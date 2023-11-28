Observations-
I have implemented two files- linearqueue.cpp and circularqueue.cpp
In both the files the functions isEmpty and isFull checks whether the queue is empty or full respectively and return true or false accordingly.
The function size gives the current size of the queue.
The function grow grows the entire array storing the queue by a constant number only when the initial queue is full. 
The function delete deletes the first element of the queue.
The function insert inserts a new element in the queue at last and it checks initially if the queue is full or not. It calls the grow function if the queue is already full.

The circular queue implementation is more useful than the linear queue implementation as it is easy to insert elements in a circular queue.
In circular queue we can go on inserting elements untill the queue is full. While for a linear queue if the last element is at the rear end then we need to grow the size of the array i.e, take a new bigger array and then copy the initial queue into it and then insert the element at the required place. This increases the time in which the algorithm executes.
Circular queue also uses less space and utilises the entire memory allocated.


