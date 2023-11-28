template <typename T>
bool DynamicQueue<T>::isEmpty(){
//if head==tail==0 then it is empty
   return head==tail;
}

template <typename T>
bool DynamicQueue<T>::isFull(){
//if tail==N then it means the elements are filled till index N-1, and array is full
   return (tail==N&&head==0);
}

template <typename T>
void DynamicQueue<T>::grow(){
//creating a temperory array and copying all elements to the array
    T* B=new T[N];
    for(int i=head;i<tail;i++){
    	B[i]=A[i];
    }
//defining a new one of nextsize    
    N=nextSize();
    A=new T[N];
    for(int i=head;i<tail;i++){
    	A[i]=B[i];
    }
    delete[] B;
}

template <typename T>
unsigned int DynamicQueue<T>::size(){
   return tail-head;
}

template <typename T>
void DynamicQueue<T>::QInsert(T x){
    if(isFull()){
        grow();//if array is full then grow the array and then add the element
    }
    else if(tail==N){//if array tail reaches the end and it is not full then shift the array to the front
        //creating a temperory array and copying all elements to the array
        T* B=new T[N];
        int j=0;
        for(int i=head;i<tail;i++){
    	    B[j]=A[i];
            j++;
        }
        tail=size();
        head=0;
        for(int i=head;i<tail;i++){
    	    A[i]=B[i];
        }
        delete[] B;
    }
    A[tail]=x;
    tail++;
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *p){
//if array is empty return false
    if(head==tail){
        return false;
    }
    *p=A[head];
   //increasing the head
    head++;
    return true;
}