

template <typename T>
bool DynamicQueue<T>::isEmpty()
{ // is the queue empty?
    return (head == tail);
}
template <typename T>
bool DynamicQueue<T>::isFull()
{ // is the queue full?
    return (tail - head) == N;
}
template <typename T>
void DynamicQueue<T>::grow()
{ // grow the queue to its next size
    if (isFull())
    {
        N += CONST_GROWTH;
        T *B;
        B = new T[N];
        for (int i = 0; i < (N - CONST_GROWTH); i++)
            B[i] = A[i];
        delete A;
        A = B;
    }
    return;
}
template <typename T>
unsigned int DynamicQueue<T>::size()
{ // return the current number of elements in the queue
    return (tail - head);
}
template <typename T>
void DynamicQueue<T>::QInsert(T x)
{ // insert given element at tail of the queue; grow array size as necessary
    if (tail != N - 1)
    {
        A[tail++] = x;
        return;
    }
    if (tail == N - 1 && !isFull())
    {
        for (int i = 0; i < size() - 1; i++)
            A[i] = A[head + i];
        head = 0;
        tail = size() - 1;
        QInsert(x);
        return;
    }
    if (isFull())
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
    *x = A[head++];
    return true;
}
