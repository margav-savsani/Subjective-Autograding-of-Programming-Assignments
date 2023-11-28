linearQueue.cpp
if head is equal to tail then queue is empty or else not empty
the queue is full if the head is at 0 index and last index is filled
if the queue is full then we create a new queue with nextsize and copy
the elements into the new queue and delete the old queue and change the
address of new queue into old one
size of the queue is tail-head
insert if the queue is filled than we will grow it and insert the elements
if the head is not at zero index then we will shift the queue such that 
head is at 0 index and grow it
if the queue is empty then the QDelete() returns false

circularQueue.cpp
if head = tail then the queue is empty 
considered that queue is filled if tail is N-1 
so when the size is N-l it is filled or else not filled
when the queue is filledand head is not at index 0 then the queue is 
growed such that the gap between tail and head is increased 
if head is at 0 then the queue increased as in case of linearQueue
size of the queue is(N-head+tail)%N 
if the queue is full then it is growed and element is inserted
or else element is inserted after tail
delete is same as in case of linear queue 
