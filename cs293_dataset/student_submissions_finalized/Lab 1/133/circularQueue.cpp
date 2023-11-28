#include "queue.h"

//all the arguments given are based on the properties of the circularqueue

template <typename T> 
bool DynamicQueue<T>:: isEmpty(){   // is the queue empty?
    if(size() == 0) return true;    // if size of array becomes 0, then the queue is empty
    else return false;
}
template <typename T>
bool DynamicQueue<T>:: isFull(){     // is the queue full?
    if(size() == N) return true;     //if size is N, queue is full
    else return false;
}
template <typename T>
void DynamicQueue<T>:: grow(){             // grow the queue to its next size
        unsigned int new_sz = nextSize();  //new_sz stores the value next size of the queue
        T *S = new T[new_sz];              //create a new array of type T with size = new size
        for(int i=0;i<N;i++){              //This grow operation happens only if the queue is full(all places are occupied)
            S[i] = A[(i+head)%N];          //copy the elements of the previous array into S by arranging them to their original order
        }
        head = 0;                          //head becomes zero for the new array
        tail = N;                          //tail becomes N for the new array
        N = new_sz;                        //change the value of N to the new size of new array       
        A = S;                             //assign S to A
}
template <typename T>
unsigned int DynamicQueue<T>:: size(){     // return the current number of elements in the queue
    if(tail == head) return 0;             // tail = head can happen while inserting elements(in this case queue becomes full)
    else if(tail == N+1) return N ;        // or while deleting elements(in this case queue becomes empty).To differentiate these two 
    else return (N-head+tail)%N ;          // cases, I kept track of what case happens by changing the value of tail temporarily to 2*N
                                           // in case of inserting and reverting the tail value back to its original value in case of 
                                           // deleting. By this we get the correct value of size for all the cases 
                         
}
template <typename T> 
void DynamicQueue<T> :: QInsert(T x){      // insert given element at tail of the queue; grow array size as necessary
    if(isFull()) grow();                   // if the array is full, then grow the array                                      
    tail=(tail+1)%N;                       // circular increase since it is circular array
    if(tail == head)  tail = N+1;          // this is where I change the value of the tail temporarily to random number greater than N.
                                           // I took N+1 just for convenience
}
template <typename T>
bool DynamicQueue<T> :: QDelete(T* x){     // delete element at head of the queue and place it in *x; 
    if(isEmpty()) return false;            // returns false if queue is empty, true otherwise
    else {
        if(tail == N+1) tail = head;       // this is where I again change the tail value to it's original value.
        *x = A[head];                      //A[head] is placed in *x 
        head=(head+1)%N;                   //it get deleted by incresing head value
        return true;
    }
}