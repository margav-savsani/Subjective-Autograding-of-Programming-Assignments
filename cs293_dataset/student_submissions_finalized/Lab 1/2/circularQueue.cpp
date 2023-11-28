//function for checking condition of empty of circularqueue.
template <typename T> bool DynamicQueue<T>::isEmpty(){
	if(head == -1) 
      return true;
    else 
       {if(head == tail)
          {front = size-1}
              elseif
                 {head = N-1
                    retun true;}
}
}
//function for checking condition of full of circularqueue.
template <typename T> bool DynamicQueue<T>::isFull(){
    return ((tail == N-1 && head == 0) || (tail == head-1));
}
//function for incresaing size  of circularqueue.
template <typename T> void DynamicQueue<T>::grow(){
      N =  N+CONST_GROWTH;
      T *B;
      B = new T[N];
       for(int i = head; i<tail; i++)
           B[i] = A[i];
       A=B;
}
//to apply insert operation in circularqueue.
template <typename T> void DynamicQueue<T>::QInsert(T X){
    if (isFull()) {
     return true;
    } else {
      if (head== -1) head= 0;
      tail = (tail+ 1) % N;
      A[tail] = X;
      }
      }
//to apply delete operation in cirularqueue.
template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if (head == -1)) {
     
      return (-1);
    } else {
      X = A[head];
      if (head == tail) {
        head = -1;
        tail = -1;
      }
      // Q has only one element,
      // so we reset the queue after deleting it.
      else {
        head = (head+ 1) % N;
      }
      return (X);
    }
  }
