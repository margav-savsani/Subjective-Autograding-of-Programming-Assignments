This was the first lab of DSA. In this lab, we implemented dynamic queues invloving arrays. We were to make two files named linearQueue.cpp and circularQueue.cpp. Lets dive into the
implementation.

linearQueue.cpp -> The first three member functions, namely 'size', 'isFull' and 'isEmpty' were pretty straightforward. They just used the variables 'head' and 'tail' to define their body.
Then came the 'grow' function. It grew the array by a fixed length whenever the array was found to be full. Next in line were the 'insert' and 'delete' functions. The delete function was
simple enough. It just increments the 'head' variable and stores the delete element in a pointer, provided the array isn't empty. The insert function, on the other hand, checks whether the
any space is available at the end. If yes, its done else we need to check whether to grow the array or shift elements to the left.

circularQueue.cpp -> Computing the 'size' of the queue is a bit tricky here. We need to take two cases and depending upon that we need to calculate. The 'isEmpty' and 'isFull' functions
were straightforward this time as well. The 'grow' function checks whether the queue is full and if it is then increases the array by a fixed length. The 'delete' function was simple
enough. We need to just incremenet the 'head' variable appropriately provided the array isn't empty. Lastly, the 'insert' functions checks whether the array is full or not and accordingly
inserts an element into the queue.