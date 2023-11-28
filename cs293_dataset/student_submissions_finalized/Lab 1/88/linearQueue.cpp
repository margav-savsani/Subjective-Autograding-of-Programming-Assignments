template <typename T> bool DynamicQueue<T>::isEmpty()
{
    return size() == 0; // empty queue has size zero 
}

template <typename T> bool DynamicQueue<T>::isFull()
{
    return size() == N; // filled queue has max array size
}

template <typename T> void DynamicQueue<T>::grow()
{
    T *B = new T[nextSize()]; // creating new container
    unsigned int N2 = nextSize();
    
    for(int i = 0; i < N; i++){
        B[i] = A[i]; // copying all eleents to new queue
    }

    // updating variables and freeing up old space
    delete[] A; 
    A = B;
    N = N2;
}

template <typename T> unsigned int DynamicQueue<T>::size()
{
    return tail - head; // linear queue size
}

template <typename T> void DynamicQueue<T>::QInsert(T x)
{
    if(isFull()){
        grow(); // checks if growth is required
    }
    else if(tail==N){ 
        for(int i=0; i<size(); i++){
            A[i] = A[head+i]; // if queue is not full but is shifted to end of array, 
        }                     // it is shifted to  beginning of array
        tail = size();
        head = 0;
    }
    A[tail] = x; // insertion at end of queue
    tail++;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x)
{
    if (isEmpty()) return false; // error if trying to remove from empty queue
    *x = A[head]; // putting the head of the queue inside the pointer
    head++; // removing head from the queue
    return true;
}