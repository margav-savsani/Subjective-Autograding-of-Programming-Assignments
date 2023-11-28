#include "queue.h"

template <typename T> bool DynamicQueue<T>:: isEmpty() { 
  return (head==tail)  ; 
}

template <typename T> bool DynamicQueue<T>:: isFull() { 
     return ( tail-head == N ); 
}

template <typename T> unsigned int DynamicQueue<T>:: size() { 
    return tail-head ; 
}

template <typename T> void DynamicQueue<T>:: grow() { 
   unsigned int old_size = N ; 
   N = nextSize() ; 
   T* new_A = new T[N];
   for (int i = 0, j=head ; j<tail ; i++,j++ ) { 
      new_A[i] = A[j%old_size] ; 
   }
   head = 0 ; tail -= head ; 
   A = new_A ; 
}

template <typename T> void DynamicQueue<T>::QInsert(T x) { 
     while(isFull())  {  //the queue is full
       grow() ; 
     }
     A[tail++ % N] = x ;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x) { 
     if (isEmpty()) return false  ;  //queue empty -> return false 
     *x = A[head++ % N] ; 
     return true ; 
}



// int main() { 
//    DynamicQueue<int> q   ;
//    int pop ; 
//    for (int i =0 ; i < 2000; i++ ) { 
//         q.QInsert(i) ; 
//    }
//    for (int i =0 ; i < 1000; i++ ) { 
//         q.QDelete(&pop) ; 
//    } 

//    for (int i =0 ; i < 1000; i++ ) { 
//         q.QInsert(i) ; 
//    }
//    cout<<"The poped element "<<pop<<endl ;    
//    q.a() ; 
// }