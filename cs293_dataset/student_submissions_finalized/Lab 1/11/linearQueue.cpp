#include "queue.h" 
template <typename T> bool DynamicQueue<T>:: isEmpty() { 
  if(head == tail) { return true ; }
  else { return false ; }
}

template <typename T> bool DynamicQueue<T>:: isFull() { 
   if(tail-head >= N) { return true ; }
   else { return false ; }
}

template <typename T> unsigned int DynamicQueue<T>:: size() { 
    return tail-head  ; 
}

template <typename T> void DynamicQueue<T>:: grow() { 
   unsigned int old_size = size() ; 
   N = nextSize() ; 
   T* new_A = new T[N];
   for (int i = 0 ; i<old_size; i++) { 
      new_A[i] = A[i] ; 
   }
   A = new_A ;
   tail = old_size ; 
   head = 0 ; 
}


template <typename T> void DynamicQueue<T>::QInsert(T x) { 
     while(isFull())  {  //the queue is full
       grow() ; 
     }
     if(tail == N) {
        T* new_A = new T[N];
        for(int i =0; i<size() ; i++) { 
            new_A[i] = A[head+i] ; 
        }  
        A = new_A ;   
        tail -= head ;
        head = 0 ;   
     }
     A[tail++] = x ; 
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x) { 
     if (isEmpty()) return false  ;  //queue empty -> return false 
     *x = A[head++] ; 
     return true ; 
}
