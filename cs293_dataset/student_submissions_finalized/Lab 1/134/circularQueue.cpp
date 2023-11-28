#include <iostream>
using namespace std;
#include "queue.h"

template < typename T>
bool DynamicQueue<T> :: isEmpty(){
    return tail == head && head == 0;   // array is empty when head=tail=0 
}                                       // and is full when head=tail!=0 or at head=0 & tail=10 (in this problem tail can take values between 0,N but elements are noonly at 0,N-1)
template < typename T>                  // this is assumed and also implemented accordingly for this problem to become easier and effective
bool DynamicQueue<T> :: isFull(){
    return (tail-head)%N==0 && tail!=0; 
}
template < typename T>
void DynamicQueue<T> :: grow(){
    T* Anew;                                                                        
    Anew = new T[nextSize()];
    for(int i=0; i<size(); i++){
        Anew[i] = A[(i+head)%N];  
    }                                                       
    delete(A);
    tail = size();
    head = 0;       //set head=0 for new array                                    
    N += CONST_GROWTH;  // updation of N
    A = Anew;
}
template < typename T>
unsigned int DynamicQueue<T> :: size(){
    if(!isFull())
        return (tail-head)%N;          // size is N if array is full. mod function with N doesn't work if array is full, so if condition is used here
    return N;
}
template < typename T>
void DynamicQueue<T> :: QInsert(T x){
    //cout << " >> " << N << " " << tail << " " << head << " " << isFull() << isEmpty() << endl;
    if(isFull())
      grow();             
    tail = tail% N;  //ensure tail is within range for assaignment
    A[tail] = x;     
    tail = (tail+1); //here we consiously dont use 'modulo N' such that it helps to find whether the array is empty or full when head is at 0. 
}
template < typename T>
bool DynamicQueue<T> :: QDelete(T *x){

    //cout << " >> " << N << " " << tail << " " << head << " " << isEmpty() << isFull() << endl;
    if(isEmpty())
      return false;   // if the array is empty the program returns false
    else if((tail-head)%N == 1){  
        *x = A[head];    // if there is only one element remaining in the array, we delete it and set head=tail=0 so that we dont get mistaken with array being full.
        head == 0;     
        tail == 0;         
        return true;
    }
    *x = A[head];
    head = (head+1)%N;  //in all other cases.
    return true;
}