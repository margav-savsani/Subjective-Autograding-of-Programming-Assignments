#include "queue.h"
#include <string.h>
template <typename T>
bool DynamicQueue<T>::isEmpty(){
    return tail == head; 
}

template <typename T>
bool DynamicQueue<T>::isFull(){
    return tail - head == N; //array full => (tail-1) - head + 1 = N
}

template <typename T>
void DynamicQueue<T>::grow(){
    int M = nextSize(); 
    T *B = new T[M]; //larger array on the heap
    for(int i = head; i < tail; i++){
        B[i - head] = A[i]; //copying the N elements
    }
    //less expensive library operation for copying
    //memcpy(B, A, N * sizeof(T));
    delete[] A; //deleting the old array
    A = B;
    N = M; 
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
    return tail - head;
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if(!isFull()){
        if(tail < N){ //space at the end of the array
            A[tail++] = x;
            return;
        }
        else{ //need to shift elements to start from the head
            int s = size();
            for(int i = 0; i < s; i++){
                A[i] = A[i + head];
            }
            //less expensive library operation for moving
            //memmove(A, A + head, s * sizeof(T));
            head = 0;
            tail = s;
            A[tail++] = x; //move the tail ahead by 1
            return;
        }
    }
    else{
        grow(); //create a larger array
        A[tail++] = x;
        return;
    }
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()) return false;
    x = &(A[head]); //x contains the address of the removed element
    head++; //head moved ahead by 1
    if(isEmpty()){ //if the array becomes empty, we move the markers to the start
        head = tail = 0;
    }
    return true;
}

/* Debugging function
template <typename T>
void DynamicQueue<T>::display(){
    cout << "Array Size " << N << endl;
    cout << "Head " << head << endl;
    int s = size();
    for(int i = 0; i < s; i++){
        cout << A[(head+i)%N] << " "; 
    }
    cout << endl << endl;
}
*/
