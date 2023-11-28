template <typename T>
bool DynamicQueue<T>::isEmpty()
{
    return head == tail;
}
template <typename T>
bool DynamicQueue<T>::isFull()
{
    return size() == N - 1; // as isEmpty cannot be checked if all can be occupied
                            // as head again becomes equal to tail
}
template <typename T>
void DynamicQueue<T>::grow()
{
    T *newarray;
    newarray = new T[N + CONST_GROWTH];
    if (head < tail)
    {
        for (int i = 0; i < N - 1; i++)
        {
            newarray[i] = A[i]; // similar to linear queue
        }

    }
    if (head > tail)
    {
        for (int i = 0; i < tail; i++)
        {
            newarray[i] = A[i];
        } // from index 0 to start being copied into newarray
        for (int i = head; i < N; i++)
        {
            newarray[i + CONST_GROWTH] = A[i]; // sending the elements from head to a new head
                                               // so that it remains continous
        }
         head=head+CONST_GROWTH;
    }
   
    N = N + CONST_GROWTH;
    A = newarray;
}
template <typename T>
unsigned int DynamicQueue<T>::size() { return (N + tail - head) % N; }

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (isFull())
    {
        grow(); // growing the size of array when its full
    }
    A[(tail)] = x;
    tail = (tail + 1) % N;
}
template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (isEmpty())
    {
        return false;
    }
    *x = A[head];
    head=(head+1)%N;

    return true;
}
