The zipped folder containes (along with the README file):
1. linearQueue.cpp 
2. circularQueue.cpp files
3. queue.h
4. Makefile
5. test.cpp 


Implementation of Linear Queue

1. The positions in the array are filled till tail pointer reaches the last possible index (index N).
2. Elements are deleted from the start of the array.
3. When the tail pointer reaches the end of the array (index N), the array grows to accomodate more elements, re-positioning the existing elements from the start of the array.

Implementation of the Circular Queue

1. The positions of the array are filled till the array is full - possibly in circular fashion with the tail (and head) pointer coming back to index 0 (if empty) after overflowing the end of the array.  
2. The array grows if N-1 elements are present in the array of size N.

