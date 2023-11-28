#include "queue.h"

//all the arguments given are based on the properties of the linearqueue

template <typename T> 
bool DynamicQueue<T>:: isEmpty(){   // is the queue empty?
    if(tail == head) return true;   // head reaches tail only if all the elements were deleted
                                    //so head=tails implies that queue is empty
    else return false;
}
template <typename T>
bool DynamicQueue<T>:: isFull(){     // is the queue full?
    if(tail-head == N) return true;  //observe that "tail-head" gives you the total number of elements in the queue
                                     //If this value becomes equal to N(size of array) then queue is full
    else return false;
}
template <typename T>
void DynamicQueue<T>:: grow(){             // grow the queue to its next size
        unsigned int new_sz = nextSize();  //new_sz stores the value next size of the queue
        T *S = new T[new_sz];              //create a new array of type T with size = new size
        for(int i=0;i<N;i++){              //This grow operation happens only if the queue is full(all places are occupied)
            S[i] = A[i];                   //copy the elements of the previous array into S
        }
        N = new_sz;                        //change the value of N to the new size of new array
        A = S;                             //assign S to A
}
template <typename T>
unsigned int DynamicQueue<T>:: size(){     // return the current number of elements in the queue
    return tail-head;                      //tail-head gives you the total number of elements in the array 
}
template <typename T> 
void DynamicQueue<T> :: QInsert(T x){      // insert given element at tail of the queue; grow array size as necessary
    if(isFull()) grow();                   //if the array is full; then grow the array 
    else if(tail == N){                    //else if it is not full and tail = N; move all the elements in array by "head" to front
                                           //so as to create the space at the back for inserting the new element
        for(int i=0;i<tail-head;i++){      //it performs the operation mentioned above
            A[i]=A[head+i];                //element at position i gets value of element at position head+i;
        }
        tail = tail-head;                  //value of tail for new array is tail-head and new value of head is 0
        head=0;
    }
    A[tail] = x;                           //now add the element at he tail position and increment the tail
    tail++;
}
template <typename T>
bool DynamicQueue<T> :: QDelete(T* x){     // delete element at head of the queue and place it in *x; 
    if(isEmpty()) return false;            // returns false if queue is empty, true otherwisec
    else {
        *x = A[head];                      //A[head] is placed in *x 
        head++;                            //it get deleted by incresing head value
        return true;
    }
}