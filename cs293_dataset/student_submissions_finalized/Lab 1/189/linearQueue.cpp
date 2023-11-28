#include "queue.h"
template<class T> void DynamicQueue<T>::QInsert(T x) {
      if(tail<=N-1) {
          A[tail]=x;//Tail generally does not hold element,it is a vacant space for the new element to get added.
          tail++;
      }
  }
 template<class T> bool DynamicQueue<T>::isEmpty() {
      return head=tail;//eventually if there are no elements left,through our denotion the head will be equal to tail sinceafter last standing element is removed head will go to next index that is tail,
  }
   
 template<class T> bool DynamicQueue<T>::isFull() {
      return tail=N;
  }//if all array is full tail will value the size of the array.
  template<class T> unsigned int DynamicQueue<T>::size() {
      return tail-head;
  }
  template<class T> bool DynamicQueue<T>::QDelete( T *x) {
      if(tail==head) {
          return false;

      }
      else{
          *x=A[head];
          head++;
          return true;
      }
  }//if no elements, we cannot delete,if there is,we will remove element added earliest currently in the list and increment head.


template <class T> void DynamicQueue<T>::grow(){
    T* b;
    b=new T[nextSize()];
    for(int i=head;i<N;i++) {
        b[i]=A[i];
    }
    A=b;
    N=nextSize();
}//Make new array,of greater size,copy all elements from previous array.
  