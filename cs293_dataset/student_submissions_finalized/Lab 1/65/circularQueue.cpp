template <typename T> unsigned int DynamicQueue<T>::size(){              // return the current number of elements in the queue
     if(tail >= head){
      return (tail-head);
     }
     else {
      return (N-head+tail);
     }
  }; 
template <typename T> bool DynamicQueue<T>::isEmpty(){                   // is the queue empty?
     if(size()==0) return true;
     else return false;
  };  
template <typename T> bool DynamicQueue<T>::isFull(){                    // is the queue full?
     if(size()==N-1) return true;
     else return false;
  };  
template <typename T> void DynamicQueue<T>::grow(){                      // grow the queue to its next size 
     T *B=A;
     A= new T[nextSize()];
     for(unsigned int i=0;i<size();i++){
       B[i]=A[i];
     }
     tail=size();
     head=0;
     N=N+CONST_GROWTH;
  };  
template <typename T> void DynamicQueue<T>::QInsert(T x){               // insert given element at tail of the queue; grow array size as necessary
     if(isFull()){
        int B[size()];
        int a=N-head;
        for(int i=0;i<a;i++){
            B[i]=A[i+head];
        } 
        for(int i=0;i<size()-a;i++){
            B[i+a]=A[i];
        }
        for(int i=0;i<size();i++){
            A[i]=B[i];
        }
        grow();
        A[tail]=x;
        tail++;
     }
     else if(tail==N-1){
        A[tail]=x;
        tail=0;
     }
     else{
        A[tail]=x;
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
