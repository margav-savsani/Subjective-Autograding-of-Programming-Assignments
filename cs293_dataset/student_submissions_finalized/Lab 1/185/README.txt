1) linear queue

- member function "bool isEmpty" is defined. this function will return true if queue is empty and returns false otherwise.if tail==head, then queue is empty.
- member function "bool isFull" is defined. returns whether queue is full or not. if size=N , then queue is full.
grow() grows the size of queue if the queue is full and we have to insert another element in queue.this is done by first creating a new array of increased size , then copying the elements in the new array. thenn deleting the previous array and updating size of head and tail.
size() returns the total number of elements present in array.for linear queue, number of total elements is (tail-head).
QInsert() inserts a new element at the end of array if tail is not equal to N. if the queue is full , first it increases the array size. if the queue is not full but tail = N , then it shifts all the elements at the beginning of the array i.e, index = 0 to index = N-1 and then inserts the new element.
QDelete() deletes the first element of the queue before saving it in the pointer x.