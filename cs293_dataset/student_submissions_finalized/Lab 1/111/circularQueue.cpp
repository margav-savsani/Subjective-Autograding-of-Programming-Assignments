  template <typename T>
  bool  DynamicQueue<T>::isEmpty(){
        //return (head==0);        
       if(head == 0)//Empty queue 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
  template <typename T>
  bool DynamicQueue<T>::isFull(){
        if(head == 1 && tail == N)//if first position of queue is occupied by head and last position is occupied by tail then queue is full  
        {
            return true;
        }
        if(head == tail + 1) //Handles case if head index is greater than tail
        {
            return true;
        }
        return false;
    }
  template <typename T> 
  void DynamicQueue<T>::grow(){
    unsigned int *x = new unsigned int[nextSize()];
    int k;
    k=head;
    for(int i=0;i<N-1;++i){
        k=(k+i)%N;
        x[head+i]=A[k];
    }
    tail = head+(N-1);
    delete[] A;
    N= nextSize();
    A=new  int[N];
    for(int i=head;i<tail;++i){
        A[i]=x[i];
    }
    delete[] x;
  }  
  template <typename T>
  unsigned int DynamicQueue<T>::size(){
    if(tail >= head) //In a circular queue if tail iindex is greater than head just return tail-head
    {
        return (tail - head) + 1;
    }
    else
    {
        return (N- (head - tail) + 1);//else return this if tailindex is less than head index
    }
}
 template <typename T> 
 void DynamicQueue<T>::QInsert(T x){
    if(isFull())
    {
        return ;
    } 
    else 
    {
        if(head == 0)
        {   
            head = 1;
        }
        tail = (tail + 1) % N;   // going round and round concept
        // inserting the element
        A[tail] = x;
    }
}

 template <typename T> 
 bool DynamicQueue<T>::QDelete(T *x)
  {
    //int y;
    
    if(isEmpty())
    {
        return false;
    } 
    else 
    {
        *x = A[head];
        if(head == tail)
        {
            // only one element in queue, reset queue after removal
            head = 0;
            tail = 0;
        }
        else 
        {
            head = (head+1) % N;
            return false;
        }
        return false;
    }
}

 // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
