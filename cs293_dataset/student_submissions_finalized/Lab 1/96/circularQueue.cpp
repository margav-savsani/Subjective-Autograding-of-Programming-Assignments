#include "queue.h"
using namespace std;

template <typename T>
bool DynamicQueue<T>::isEmpty(){
    return ((head==tail) && !isFull());
}

template <typename T>
bool DynamicQueue<T>::isFull(){
    return ((tail==N && head==0) || (head==tail));
}

template <typename T>
void DynamicQueue<T>::grow(){
    N=nextSize();
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
    return (N+tail-head)%N;
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isEmpty()){
        head=0;
        A[tail]=x;
        tail=1;
    }
    else if(isFull()){
        if(head==0){//grows the array size if queue is full and it is a linear queue
            grow();
            A[tail]=x;
            tail++;
        }
        else{
            while(head!=0){ //transform the circular queue into a linear queue
                T y=A[0];
                for(int i=i;i<N;i++){
                    A[i-1]=A[i];
                }
                A[N-1]=y;
                head--;
            }
            tail=N;
            grow();// grows the array size after the circular queue is transformed into a linear queue
            A[tail]=x;
            tail++;
        }
        
    }
    else{
        if(tail==N){
            //new element is added at the begining of the array 1 becomes the tail of the queue
            A[0]=x; 
            tail=1;
        }
        else{
            A[tail]=x;
            tail++;
        }
    }
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(!isEmpty()){
        *x=A[head];
        head=(head+1)%N;
        return true;
    }
    else return false;
}
