
  template <typename T> bool DynamicQueue<T>::isEmpty(){                // is the queue empty?
    if(head==tail) return true;
    else return false;
  } 
  template <typename T> bool DynamicQueue<T>::isFull(){                 // is the queue full?
    if((tail+1)%N==head) return true;                        
    else return false;
  }
  template <typename T> void DynamicQueue<T>::grow(){   
    int a;
    a=N;              
    N=this->nextSize();                      // increasing the size
    T *B;                                    //new array
    B=new T[N];                              //memory of size new N is allocated to it
    for(int i=0; i<a; i++){
        B[i]=A[i];
    }                     
    A=B;            
  } 
  template <typename T> unsigned int DynamicQueue<T>::size(){          // return the current number of elements in the queue
    return (N-head+tail)%N;
  }  
  template <typename T> void DynamicQueue<T>::QInsert(T x){            // insert given element at tail of the queue; grow array size as necessary
    if((tail+1)%N==head){                            // if the queue is full(size=N-1)
        A[tail]=x;
        T *B;
        B=new T[N];                                  //defining a new array
        for(int i=head; i<N; i++){                   //copying elements of A into B
           B[i-head]=A[i];
        }
        for(int i=N-head; i<N; i++){                 //copying elements of A into B
           B[i]=A[i-(N-head)];
        }
        A=B;  
        tail=N;
        head=0;      
    }
    else if(tail==N && head==0){                    // if the size of array=N then the grow function to accomodate the inserting element
        this->grow();
        A[N]=x;
        tail++;
    }
    else{
        A[tail]=x;
        tail++;
    } 
  }
  template <typename T> bool DynamicQueue<T>::QDelete(T *x){ // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
    if(tail==head)return false;
    else{
        *x=A[head];
        A[head]=0;            //assigning value 0 to the deleted element
        head=(head+1)%N;
        return true;
    }
  }      


