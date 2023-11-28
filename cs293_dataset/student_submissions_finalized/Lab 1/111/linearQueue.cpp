  template <typename T>
  bool  DynamicQueue<T>::isEmpty(){

    if(head==tail) //If head and tail are same then queue is empty
    {
      return true;
    }

    return false;

  }
  template <typename T>
  bool DynamicQueue<T>::isFull(){
    if(tail-head==N-1) //In a linear queue if head occupy first block of imaginary queue and tail occupy last block then the queue is full 
    {
      return true;
    }
    return false;
  }
  template <typename T> 
  void DynamicQueue<T>::grow(){
    unsigned int *x = new unsigned int[nextSize()];//nextSize()->grows the size of queue
    int k;
    k=head;
    for(int i=0;i<N-1;++i){
        k=(k+i)%N;
        x[head+i]=A[k];//stores every element of previous array in new array
    }
    tail = head+(N-1);
    delete[] A;
    N= nextSize();
    A=new  int[N];
    for(int i=head;i<tail;++i){
        A[i]=x[i];//again  the previous array size has been increased so store every elemnt here
    }
    delete[] x;
  } // grow the queue to its next size 
  template <typename T>
  unsigned int DynamicQueue<T>::size()
    {
      return tail-head;
    
  } // return the current number of elements in the queue
 template <typename T> 
 void DynamicQueue<T>::QInsert(T x){
    if(!isFull())
    {
      A[tail]=x;      //If list is not full then store element at the tail of queue
      tail=(tail+1)%N;
    }
    else
    {
      grow(); //if queue is full then first grow the queue then insert element at the tail of new queue
      A[tail]=x;
      tail=(tail+1)%N;

    }
  } // insert given element at tail of the queue; grow array size as necessary
 template <typename T> 
 bool DynamicQueue<T>::QDelete(T *x)
  {
    if(isEmpty())  //If empty then nothing to delete
    {
      return false;
    }
    else
    {
      *x=A[head]; //If not empty then delete element at the head of queue
      for(int i=0;i!=tail;i++)
      {
        A[head+i]=A[head+i+1]; // shift the entire queue to right 
        return true;
      }
     return false;
    }
  }