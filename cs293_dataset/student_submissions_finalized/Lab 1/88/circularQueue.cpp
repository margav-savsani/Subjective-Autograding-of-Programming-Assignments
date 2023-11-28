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
    
    for(int i = 0; i < size(); i++){
        B[i] = A[(i + head) % N]; // copying all elements to new queue
    }

    delete[] A; // updating previous variables and freeing up space
    tail = size();
    head = 0;
    A = B;
    N = N2;
}

template <typename T> unsigned int DynamicQueue<T>::size()
{
    if (tail == N+1) return N; // checks if tail has the special value
    else return (N + tail - head) % N; // otherwise evaluates normally
}

template <typename T> void DynamicQueue<T>::QInsert(T x)
{
    if(isFull()){
        grow(); // checks if growth is required
        
    }
    A[tail] = x; // adding new element to end of queue
    if (size() == N-1) tail = N+1; // gives special value to tail if size is N
    else tail = (tail + 1) % N;
}

template <typename T> bool DynamicQueue<T>::QDelete(T *x)
{
    if (isEmpty()) return false; // error if trying to remove from empty queue
    *x = A[head]; // putting the head of the queue inside the pointer
    head = (head + 1) % N; // removing head from the queue
    return true;
}