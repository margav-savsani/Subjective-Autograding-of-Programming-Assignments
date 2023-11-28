template <typename T> bool DynamicQueue<T>::isEmpty(){
    return(tail==head); //empty when tail==head
}

template <typename T> bool DynamicQueue<T>::isFull(){
    return (size()==N-1);//max size allowed is N-1 so that we can reserve the tail=head condition for isEmpty
}

template <typename T> void DynamicQueue<T>::grow(){
    T* B,*temp;
    temp=A;
    B=new T[nextSize()];//new array
    for(int i=0;i<N;i++){
        B[i]=A[(i+head)%N];//copyong elements form old to new array
    }
    head=0;tail=N-1;
    delete[] temp;//clearing memory of old array
    A=B;
    N=nextSize();
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    return (N+tail-head)%N;//%because here tail can be less than head,tail=head gives zero
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    //here array will seem to full only when it is unlike the linearQueue where tail can be at N and still array is not full
    if(size()<N-1){
        A[tail]=x;tail=(tail+1)%N; //moving the tail in circular fashion
    }
    else{
        grow();
        A[tail]=x;tail=(tail+1)%N;
    }
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()){
        return false;
    }
    else{
        *x=A[head];
        head=(head+1)%N; //moving the head in circular fashion
        return true;
    }
}