template <typename T>
bool DynamicQueue<T>::isEmpty()
{
    return head == tail;
}
template <typename T>
bool DynamicQueue<T>::isFull()
{
    return N == size();
}
template <typename T>
void DynamicQueue<T>::grow()
{
    T *newarray;
    newarray = new T[N + CONST_GROWTH];
    for (int i = 0; i < N; i++)
    {
        newarray[i] = A[i + head]; // bringing the elements from head to 0 index
    };
    tail = size();
    head = 0;
    N = N + CONST_GROWTH;
    A = newarray;
}
template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return (tail - head);
}

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (size() == N)
    {
        grow(); // growing the size of array after it's full
    }
    if (tail == N)
    {
        for (int i = 0, j = head; i < N; i++, j++)
        {
            A[i] = A[j]; // moves the head to zero when tail reaches the end of array
        }
        tail = tail - head;
        head = 0;
    }
    A[tail] = x;
    tail++;
}
template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (isEmpty())
    {
        return false;
    }
    *x = A[head];
    head++;
    return true;
}
