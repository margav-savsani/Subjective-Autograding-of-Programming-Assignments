
//function for checking condition of empty of Linearqueue.
template <typename T> bool DynamicQueue<T>::isEmpty(){
	if(head == tail) return true;
    else return false;
}
//function for checking condition of full of Linearqueue.
template <typename T> bool DynamicQueue<T>::isFull(){
    return ((head == 0) && (tail == N-1));
}
//function for incresaing size  of Linearqueue.

template <typename T> void DynamicQueue<T>::grow(){
      N =  N+CONST_GROWTH;
      T *B;
      B = new T[N];
       for(int i = head; i<tail; i++)
           B[i] = A[i];
       A=B;
}
//to apply insert operation in Linearqueue.
template <typename T> void DynamicQueue<T>::QInsert(T X){
    if((tail ==N-1)){
        grow();
        QInsert(X);
    }
    else{
         tail++;
         A[tail] = X;     
       }  
}
//to apply delete operation in Linearqueue.
template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(head == tail) return false;
    else{
        *x = A[head];
        head++;
        return true;

}
}
















  

















  
