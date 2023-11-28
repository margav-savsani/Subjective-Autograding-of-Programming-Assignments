
template <typename T>
bool DynamicQueue<T>::isEmpty()
{
    return (head == tail); // when the head and tail will have same value queue will empty
}

template <typename T>
bool DynamicQueue<T>::isFull()
{
    return (tail - head == N); // N-1 is the number of elements in between head and tail
}
template <typename T>
void DynamicQueue<T>::grow()
{   
    int *b = new int[nextSize()]; // i initilize  a queue b which store current queue
    for (int i = 0; i <N; i++)
    {
        b[i] = A[i];
    }
    head=0,tail=N;
    N = nextSize();
    A=b;
    
}
template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return tail - head; // the size will be difference between tail and head value
}
template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (isFull()==true)
    {
        grow();
    }
    else if (tail == N) // if tail reaches to end and still some element are empty then we shift
    // array element to left
    {
        for (int i = 0; i < tail - head; i++)
        {
            A[i] = A[head + i];
        }
        tail = N - head;
        head = 0;
    }
    A[tail] = x;
    tail = tail+1;
}
template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{

    if (isEmpty()==true)
    {
        return false;
    }
    *x = A[head];
    head += 1;

    return true;
}
