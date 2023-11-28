#include "queue.h"
using namespace std;

template <typename T>
bool DynamicQueue<T>::isEmpty(){
    return head==tail;
}

template <typename T>
bool DynamicQueue<T>::isFull(){
    return (tail==N && head==0);
}

template <typename T>
void DynamicQueue<T>::grow(){
    N=nextSize();
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
    return tail-head;
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isEmpty()){
        head=0;
        A[tail]=x;
        tail=1;
    }
    else if(isFull()){ //grows the array size if queue is full
        grow();
        A[tail]=x;
        tail++;
    }
    else if(tail==N){ //if tail==N but head!=0,then shift the the elements of array backwards by 1
            for(int i=head;i<tail;i++){
                A[i-1]=A[i];
            }
            A[tail-1]=x;
            
        }
    else{ //when there is sufficient space at the end of array
        A[tail]=x;
        tail++;
    }
    
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(head==tail) return false;

    else{
        *x=A[head]; //places element at the head of the queue at *x
        head++; //deletes element at the head of the queue
        return true;
    }
}
