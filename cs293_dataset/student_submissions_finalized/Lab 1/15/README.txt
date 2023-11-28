linearQueue-
1)I implemented the isEmpty function which returns true if head is same as tail else false.
2)The size would be tail-head so I implemented it in the size function.
3)In the QInsert function if the queue is full we grow the queue,but if the queue is not full and
    the tail reaches N ie the queue has reached its end we shift the queue and the new head is at 0.
    Then we insert the desired element and increment the tail.
4)isFull returns true if the tail reaches N and the head is 0.
5)the grow function increases the size of the queue. We first create a new array of increased size nestSize
    then copy the elements of A to the new array such that the element at the head of the queue will be at 0 th index
    .We then assign new correct values to head and tail and then delete the space allocated to A and then assign B to A.
6)The QDelete returns false if we try to delete from an empty queue else it stores the value at the position to be deleted
    at the position pointed by the pointer passed as argument.We then increment the head and return true.

circularQueue-
* here i am taking head and tail not to be indexes  and head%N and tail%N to be indexes.
    Whenever an element is added tail is incremented(if grow is not required) and when deleted head is incremented.
1)isEmpty will return true if the tail is equal to head.
2)size will return the difference of head and tail as every added element increases the tail and deleted element increases the head.
    also when we grow the difference tail and head remains the same.
3)QInsert grow the queue if it is full and then adds x at the tail%N and increments the tail.
4)IsFull returns true if the size is N.
5)grow makes a new array of N+ CONST_GROWTH size and then copies the elements such that the final head will be 0.Also final tail will be 
    the size.
6)QDelete returns false if we try to delete from an empty queue else it stores the value at the head in the pointer passed and then increments
    head.
