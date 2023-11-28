linearQueue:

size():
checks the size of the linear queue by just doing head-tail beacuse head is always greater than the tail.

isFull:
I use the size function here to check whether it returns N--max capacity of the queue

isEmpty:
if size function returns 0 then isEmpty becomes true

QInsert:
if it is full--go to grow function first
if tail==N but head is not 0, then the elements are being shifted to the front to create space at the back.For this a for loop of order O(n) is run.

QDelete:
not possible is queue is empty
if not, then just shift head by 1, rest reamins same

Grow:
once queue is full, its size is grown by a constant size,elements are shifted in a new array and then our original array is reallocated to that array.
head and tail are adjusted accordingly.

CircularQueue:

I have kept incrementing head and tail.only while indexing , I have used mod N so that the values are stored in the corect places.

size():
checks the size of the circular queue by just doing head-tail beacuse head is always greater than the tail.(No mod used here!)

isFull:
I use the size function here to check whether it returns N--max capacity of the queue

isEmpty:
if size function returns 0 then isEmpty becomes true

QInsert:
if it is full--go to grow function first
insert element and back and increment tail.

QDelete:
not possible is queue is empty
if not, then just shift head by 1, rest reamins same

Grow:
once queue is full, its size is grown by a constant size,elements are shifted in a new array starting from head of the original array, and then our original array is reallocated to that array.
head and tail are adjusted accordingly.

WHY IS CIRCULAR QUEUE BETTER?
Because we dont have to shift the elements to the front when tail reaches N and head is not 0, we can just add mod N at the index and our work is done.
Therefore time for circular is almost half the time for linear.

Constructor function is not changed as we were instructed to keep queue.h as it was.


