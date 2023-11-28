using namespace std;
#include "queue.h"
#include<cmath>
template <typename T>
bool DynamicQueue<T> :: isEmpty(){  //condition of the queue to be empty
    return (size() == 0);
}
template <typename T>
bool DynamicQueue<T> :: isFull(){   //condition of the queue to be full(note that we take the array to be full when size is N-1)
    return (size() == N-1);
}
template <typename T>
void DynamicQueue<T> :: grow(){      //growing the size of the queue when size is full
    T *S;
    S = new T[nextSize()];
    for(int i=head; i<N; i++){      //transferring the elements to the new array
        S[i-head] = A[i];
    }
    for(int i=0; i<tail;i++){
        S[N-head] = A[i];
    }
    delete []A;
    head = 0;
    tail = N-1;
    N = nextSize();
    A = S;
    S= NULL;

}
template <typename T>
unsigned int DynamicQueue<T> :: size(){    // writing the mathematical function for size
    return((N-head+tail) % N);
}
template<typename T>
void DynamicQueue<T> :: QInsert(T x){   //insertion of elements
    if(isFull()){                       //grow and insert when the array is full
        grow();
            A[tail] = x;
            tail++;
            tail %= N;
    }
    
    else{                                //otherwise add the element in a circular fashion if required
        tail %= N;
        A[tail] = x;
        tail++;
    }
 }
template <typename T>
bool DynamicQueue<T> :: QDelete(T *x){     // deletion
     if(isEmpty()){return false;}
     else if(head == N-1){          //boundary case to be written separately
         *x = A[head];
         head = 0;
         return true;
     }
     else{
          *x = A[head];
        head++;
        return true;
     }
}