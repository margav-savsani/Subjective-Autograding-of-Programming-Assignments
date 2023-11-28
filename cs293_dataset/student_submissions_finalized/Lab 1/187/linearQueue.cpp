  template<typename T>
 unsigned int DynamicQueue<T>::size(){// size of queue.
   return (tail-head);
 }
 template<typename T>
  bool DynamicQueue<T>::isEmpty(){// checks if queue is empty or not.
    if(size() == 0) {return true;}
    else {return false;}
   }
   template<typename T>
  bool DynamicQueue<T>::isFull(){// checks if queue is full or not.
     if(size() == N){
       return true;
     }
     else{
      return false;
     }
   }
   template<typename T>
   void DynamicQueue<T>::grow(){// grows the size of array by taking array of size 1000+N and copying values from A to B and reassign B to A. 
       T *B;
       B = new T[nextSize()];
       for(int i=0;i<N;i++){
         B[i] = A[i];
       }
        A = B;
        N = nextSize();
   }
 template<typename T>
 void DynamicQueue<T>::QInsert(T x){// inserts elements at the end.
  if(isFull()){// if queue is full then grow the array.
    grow();
  }
  if(head > 0 && tail == N){// if tail is equal to N then move array such that head = 0 and inserts at tail.
    for(int i=head;i<tail;i++){
      A[i-head] = A[i];
    }
    tail = tail-head;
    head = 0;
   }
  A[tail] = x;
  tail++;
}
 template<typename T>
 bool DynamicQueue<T>::QDelete(T *x){// Deletes element at the head of queue and assign them to x. 
 int j=0;
 if(isEmpty()){// if queue is empty then return false.
       return false;
     }
     else{// if queue is not empty then assign them to x then return true.
     x[j] = A[head];
     head++;
     j++;
     return true;
     }
}
