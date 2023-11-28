template<typename T>
bool DynamicQueue<T>::isEmpty(){
    if(head==tail) return true;
    else return false;
}
template<typename T>
bool DynamicQueue<T>::isFull(){
    if(size()==N-1) return true;
    else return false;
}
template<typename T>
unsigned int DynamicQueue<T>::size(){
    return (N-head+tail)%N;
}
template<typename T>
void DynamicQueue<T>::QInsert(T x){
    if(size()==N-1){
    grow();
    A[tail]=x;
    tail=(tail+1)%N;
    }
    else{
        A[tail]=x;
        tail=(tail+1)%N;
    }
}
template<typename T>
bool DynamicQueue<T>::QDelete(T *x){
    if(!isEmpty()){
    *x=A[head];
    head=(head+1)%N;
    return true;
    }
    else return false;
    
}
template<typename T>
void DynamicQueue<T>::grow(){
    T* S;
    S=new T[nextSize()];
    if(tail<head){
        for(int i=head;i<N;i++){
            S[i-head]=A[i];
        }
        for(int i=0;i<head-1;i++){
            S[N+head+i]=A[i];
        }   
    }
    else {
        for(int i=0;i<N;i++){
            S[i]=A[i];
        }
    }
    tail=N-1;
    N=nextSize();
    head=0;
    A=S;
}
