template<typename T>
bool DynamicQueue<T>::isEmpty(){
    return(tail==head);
}
    
template<typename T>
bool DynamicQueue<T>::isFull(){
    if(tail==N & head==0) return true;
    else return false;
}
template<typename T>
unsigned int DynamicQueue<T>::size(){
    return tail-head;
}
template<typename T>
void DynamicQueue<T>::QInsert(T x){
    if(tail==N){
    grow();
    }
    else if(tail==N){
        for(int i=head;i<tail;i++){
            A[i-head]=A[i];
        }
        tail-=head;
        head=0;
    }
    A[tail]=x;
    tail++;
}
template<typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(!isEmpty()){
    *x=A[head];
    head=head+1;
    return true;
    }
    else return false;   
}
template<typename T>
void DynamicQueue<T>::grow(){
    T* S;
    N=nextSize();
    S=new T[N];
    for(int i=0;i<N-CONST_GROWTH;i++){
        S[i]=A[i];
    }
    A=S;
}

