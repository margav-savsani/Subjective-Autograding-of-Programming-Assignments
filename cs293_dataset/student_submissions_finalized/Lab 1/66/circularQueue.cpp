#include "queue.h"


template <typename T>bool DynamicQueue<T>::isEmpty(){
          if(size()==0) {return true;}
          else {return false;}
}
        
template <typename T>bool DynamicQueue<T>::isFull(){
          if(size()==N) {return true;}
          else {return false;}
}

template <typename T>void DynamicQueue<T>::grow(){
          T *b=new T[nextSize()]   ;                        // creating new array of bigger size
          
          if(tail>head) {                                   //copying elements of A into b
              for(int i=head;i<tail;i++) b[i-head] == A[i];
          }
          else{
              for(int i=head;i<N;i++) b[i-head]=A[i];
              for(int i=0;i<tail;i++) b[N-head+i]=A[i];
          }
       
          A=b;                                             // now making A to point out to new array
          head=0; tail=N;                                  // changing head and tail
          N = nextSize();                                  // changing variable representing size of array 
}

template <typename T>unsigned int DynamicQueue<T>::size(){
          if(head==tail&&A[head]==NULL) {return 0;}        // array empty condition
          else if(head==tail&&A[head]!=NULL) {return N;}   // array full condition
          else if(tail>head) {return tail-head;}
          else { return N+tail-head;}                      // size in case where tail is ahead of head
}

template <typename T>void DynamicQueue<T>::QInsert(T x){
          if(tail==head&&A[head]!=NULL) grow();            // increasing array size if it is full
          
          A[tail] = x;                                     
          if(tail==N-1) {tail=0;}                          //making tail 0 if it is N-1 previously
          else{tail=tail+1;}
}

template <typename T>bool DynamicQueue<T>::QDelete(T *x){
         if(isEmpty()) {return false;}
         else {A[head]=NULL;
               if(head==N-1) {head=0;}                   //making head 0 if it is N-1 previously 
               else {head=head+1;}
                             return true;
                             }
         
}
