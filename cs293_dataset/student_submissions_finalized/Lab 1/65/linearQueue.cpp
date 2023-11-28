  template <typename T> unsigned int DynamicQueue<T>::size(){              // return the current number of elements in the queue
     return (tail-head);
  }; 
  template <typename T> bool DynamicQueue<T>::isEmpty(){                   // is the queue empty?
     if(size()==0) return true;
     else return false;
  }; 

  template <typename T> bool DynamicQueue<T>::isFull(){                    // is the queue full?
     if(size()==N) return true;
     else return false;
  }; 
  template <typename T> void DynamicQueue<T>::grow(){                      // grow the queue to its next size 
      
       T *B=A;
       A= new T[nextSize()];
      
       for(int i=0; i<size(); i++){
        B[i]=A[i];                                                         //initialized an array of new size and copied everyting from prev array to this modified array
        }
       
        N=N+CONST_GROWTH;                                                   //increased N and changed head and tail
        tail=size();
        head=0;
  };
  template <typename T> void DynamicQueue<T>::QInsert(T x){               // insert given element at tail of the queue; grow array size as necessary
     
     if(isFull()){
      grow();                                                              //I directly have grown the array if the array is filled with queue and added the element at last
      A[tail]=x;
      tail++;
      }
     
     else if(tail==N){
       
      for(int i=0;i<size();i++){
        A[i]=A[i+head];                                                   //if the array is not filled but the tail is at the end,, then I shifted the entire queue to the start and changed the tail and the head
       }
       
      tail=size();
      head=0;
      A[tail]=x;
      tail++;
     }
     else if(tail!=N) {
      A[tail]=x;                                                           //if none of the conditions above staisfied,, then simply I added the element at last
      tail++;
     }
     };
  template <typename T> bool DynamicQueue<T>::QDelete(T *x){                // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
    if(!isEmpty()){
      *x=A[head];
      head++;
      return true;
     }
   else return false; 
  };

