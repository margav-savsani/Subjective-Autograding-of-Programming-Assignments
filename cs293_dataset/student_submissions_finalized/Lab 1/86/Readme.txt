                         OBSERVATIONS

This lab is to implement a queue using arrays in two different way

1)linearQueue :
               In this queue, conditions for empty queue are already given
in class constructor and for the queue to be full head should be 0 and tail 
be N. size() function here returns the no of elements present in queue.
grow() function first checks whether the queue is full or not, if full then
maximum size of array is grown linearly leaving the queue as it is. Qinsert()
function inserts an element at the tail of the queue but when queue is full
then queue is grown and then the new element is inserted. Qdelete() function
generally deletes the first element of the queue i.e, element with head as 
index then moves head to its next position. Iniially i faced problemwith this 
function and added a new condition that if after deletion queue is empty then
update head and tail to 0 so that it represents an empty queue.


2)circularQueue :
                  This queue is implemented in the same way as linearQueue is 
implemented except, head=0 & tail=0 represents both empty queue and full queue.
So to solve this issue i assumed that when head is 0 and queue is full then 
tail is not N%N but its just N. This makes a change in insert function i.e,
if after insertion queue is full then set head to 0 and tail to be N.
   
                          THANK YOU.

 