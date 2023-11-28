

template <typename T>
bool DynamicQueue<T>::isEmpty()
{ // is the queue empty?
    return (tail == head);
}
template <typename T>
bool DynamicQueue<T>::isFull()
{ // is the queue full?
    return size() == N - 1;
}
template <typename T>
void DynamicQueue<T>::grow()
{ // grow the queue to its next size
    if (isFull())
    { // unnecesary condition check
        tail = size();
        N += CONST_GROWTH;
        T *B = new T[N];
        for (int i = 0; i < size(); i++)
            B[i] = A[(head + i) % (N - CONST_GROWTH)];
        head = 0;
        delete A;
        A = B;
    }
}
template <typename T>
unsigned int DynamicQueue<T>::size()
{ // return the current number of elements in the queue
    return (N - head + tail) % N;
}
template <typename T>
void DynamicQueue<T>::QInsert(T x)
{ // insert given element at tail of the queue; grow array size as necessary
    if (!isFull())
    {
        A[tail] = x;
        tail = (tail + 1) % N;
        return;
    }
    else
    {
        grow();
        QInsert(x);
        return;
    }
}
template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{ // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
    if (isEmpty())
        return false;
    head = (head + 1) % N;
    return true;
}
