template <typename T> bool DynamicQueue<T>::isEmpty(){
    return(tail==head);//tail==head implies empty list
}

template <typename T> bool DynamicQueue<T>::isFull(){
    return (size()==N);//full when size is equal to max size
}

template <typename T> void DynamicQueue<T>::grow(){
    T *B,*temp;
    temp=A;
    B=new T[nextSize()];//new array 
    for(int i=0;i<N;i++){
        B[i]=A[i];//copying into new array
    }
    delete[] temp;//clear previous memory
    A=B;
    N=nextSize();
}

template <typename T> unsigned int DynamicQueue<T>::size(){
    return tail-head;
}

template <typename T> void DynamicQueue<T>::QInsert(T x){
    if(tail<N){       //when tail is not at the end
        A[tail]=x;
        tail+=1;
    }
    else if (isFull()){ //when array is full we grow then insert
        grow();
        A[tail]=x;
        tail+=1;
    }
    else { //when tail is at end but array is not full, we shift the elements.
        for (int i=0;i<size();i++){
            A[i]=A[head+i];//shifting
        }
        tail=size();head=0;
        A[tail]=x;
        tail+=1;
    }
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x){
    if(isEmpty()){
        return false;
    }
    else{
        *x=A[head];
        head+=1;//moved index of head
        return true;
    }
}