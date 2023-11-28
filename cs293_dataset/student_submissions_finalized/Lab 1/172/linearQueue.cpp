  
  template <typename T> bool DynamicQueue<T>::isEmpty(){             // is the queue empty?
    if(head==tail) return true;     // returns true if the queue is empty, else false
    else return false;
  } 
  template <typename T> bool DynamicQueue<T>::isFull(){              // is the queue full?
    if(tail==N && head==0) return true;  // returns true if the queue is full, else false
    else return false;	
  }
  template <typename T> void DynamicQueue<T>::grow(){ 
    int a;
    a=N;              
    N=this->nextSize();                    // grow the queue to its next size 
    T *B;                                  //new array
    B=new T[N];                            //memory of size new N is allocated to it
    for(int i=0; i<a;i++){                 //copying elements of A into B
        B[i]=A[i];
    }
    A=B;      
  }               
  template <typename T> unsigned int DynamicQueue<T>::size(){        // return the current number of elements in the queue
    return tail-head;
  }
  template <typename T> void DynamicQueue<T>::QInsert(T x){          // insert given element at tail of the queue; grow array size as necessary
    if(tail==N){              
       if(head==0){                //if the Queue is full
         this->grow();
         A[tail]=x;
         tail++;
       }
       if(head!=0 && head!=N){                //the tail has reached the end but head is not at 0
         T* B;
         B=new T[N]; 
         for(int i=head; i<tail; i++){   //copying elements of A into B          
            B[i-head]=A[i];
         }
         A=B;
         tail=tail-head;            //tail reduces
         A[tail]=x;
         tail=tail+1;
         head=0;  
       }  
       if(head==N){
         A[0]=x;
         head=0;
         tail=1;
       }
    }
    else{                           //if the Queue is not full
       A[tail]=x;
       tail++;
    }
  } 
  template <typename T> bool DynamicQueue<T>::QDelete(T *x){        // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
    if(head==tail){
        return false;
    }
    else{
        *x=A[head];
        A[head]=0;          // assigning value 0 to the element which has to be deleted
        head++;       
        return true;
    }
  } 
