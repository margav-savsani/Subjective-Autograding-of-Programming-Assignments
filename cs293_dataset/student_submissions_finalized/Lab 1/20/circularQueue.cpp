#include <iostream>
using namespace std;
#include "queue.h"
template <typename T>bool DynamicQueue<T>::isEmpty(){
          if(head == tail && A[head]== NULL) return 1;
          else return 0;
}
        
template <typename T>bool DynamicQueue<T>::isFull(){
          if(head == tail && A[head]!= NULL) return 1;
          else return 0;
}

template <typename T>void DynamicQueue<T>::grow(){
          T *b=new T[N]   ;                        
              for(int i=head;i<N;i++) b[i-head]=A[i];
              for(int i=0;i<tail;i++) b[N-head+i]=A[i];
          
     A = new T[N+CONST_GROWTH];
     for(int i=0;i<N;i++)
     A[i] = b[i];      
          A=b;                                             
          head=0; tail=N;                                  
          N = nextSize();                                  }

template <typename T>unsigned int DynamicQueue<T>::size(){
          if(isEmpty()) {return 0;}        
          else if(isFull()) {return N;}   
           if(tail>head) {return tail-head;}
          else if(tail<head) { return N+tail-head;}                      
}

template <typename T>void DynamicQueue<T>::QInsert(T x){
          if(isFull()) grow();            
          
          A[tail] = x;                                     
          tail = (tail + 1)%N;
          
}
template <typename T>bool DynamicQueue<T>::QDelete(T *x){
         if(head== tail && A[tail] == NULL) return false;
         else {
               head = (head +1)%N
                             return true;
                             }
         
}
