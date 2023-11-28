LinearQueue:

Queue is implemented linearly which means consecutive elements in the queue are stored at array locations with consecutive indices.So the first element is always at smaller index
tail-the index next to the latest filled element
head-the index from which the next element is removed
in grow function we increase the size of array by creating a temporary array with the increased size and then copying the elements into it and then changing the address of original array to the new one
we consider the queue is full if the array is completely filled(N)
in insert function we grow the array when required and if the array is not completely filled and even then if the last filled element of array is at the last then we shift the elements of array such that we can insert elements to the last
for the delete function we just change the position of head instead of deletion

CircularQueue:

Array is taken to be circular which means consecutive elements in the queue are stored at array locations that are consecutive *modulo the array size*.So, the first element in circularQueue may not always be at the array location with the smallest index compared to other elements in circularQueue.
tail-the index next to the latest filled element
head-the index from which the next element is removed
in grow function we increase the size of array by creating a temporary array with the increased size and then copying the elements into it and then changing the address of original array to the new one
we consider the queue is full if the array is completely filled except for one position(N-1)
here we use %N everywhere as the array is considered to be circular

########################################################## ANCHA PRANAVI ##########################################################
