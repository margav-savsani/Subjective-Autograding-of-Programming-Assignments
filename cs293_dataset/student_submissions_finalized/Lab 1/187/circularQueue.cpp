 template<typename T>
  bool DynamicQueue<T>::isEmpty(){// checks if queue is empty.
    if(tail == head){return true;}// if tail = head then queue is empty.
    else {return false;}
   }
   template<typename T>
  bool DynamicQueue<T>::isFull(){// checks if queue is full.
     if((tail+1)%N == head){// if size of queue=N-1 then its full.
       return true;
     }
     else{
      return false;
    }
 }
    template<typename T>
   unsigned int DynamicQueue<T>::size(){// size of queue.
   return (N-head+tail)%N;// this returns size of circular queue.
 }
   template<typename T>
   void DynamicQueue<T>::grow(){// This function grows the array.
       T *B;// New pointer in type T.
       B = new T[nextSize()];// size of array is 1000+N.
       for(int i=0;i<size();i++){
         B[i] = A[(i+head)%N];// Reads the values from head to tail in order to array B.
        }
        A = B;// B is assigned to A.
        tail= size();// tail is equal to size of previous array.
        head = 0;// head is equal to 0.
        N = nextSize();// N is equal to N+1000.
      }
 template<typename T>
 void DynamicQueue<T>::QInsert(T x){// inserts elements in queue from back.
   if(isFull()){
     grow();
   }
     A[tail] = x;
     tail = (tail+1)%N;// if tail > N and head > 0 then elements are given to index from 0 to head.
   }
 template<typename T>
 bool DynamicQueue<T>::QDelete(T *x){// Deletes the head of queue and inserts them in pointer x.
 int j=0;
 if(isEmpty()){// if queue is empty then return false.
       return false;
     }
     else{// if queue is not empty the return true.
       x[j] = A[head];
       head = (head+1)%N;
       j++;
       return true;
     }
}
