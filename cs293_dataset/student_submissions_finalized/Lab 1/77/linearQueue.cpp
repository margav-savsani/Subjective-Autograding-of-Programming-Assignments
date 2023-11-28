template <typename T>
bool DynamicQueue<T>::isEmpty()
{
    return (head == tail);// In linear if head is equal to tail then it is empty.
}

template <typename T>
bool DynamicQueue<T>::isFull()
{
    return (size() == tail - head);//Return true if Array is full. 
}

template <typename T>
void DynamicQueue<T>::grow()
{
    T *B;                        // Creates new Array
    B = new T[N + CONST_GROWTH]; // Assigns elements of previous array(A) to new array (B)
    for (int i = 0; i < N; i++)
    {
        B[i] = A[i];
    }
    head = 0;//In new array head is zero
    tail = N;//As allraedy Array A is full so tail= N
    A = B;
    N = N + CONST_GROWTH; // Changes N value after growth
}

template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return (tail - head);// size is tail- head
}

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (size() == N)
    {
        grow(); // Growing array size
    }
    else if (tail == N)// If tail is N but head is not zero then it shifts all element backwards
    { 
        for (int i = 0; i < tail - head; i++)
        { 
            A[i] = A[head + i];
        }
        tail = tail - head;// As elements are shifted backwards tail becomes tail-head
        head = 0;
    }
    A[tail] = x;//Inserts new element
    tail++;//Grows tail by 1 after inserting an element
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (isEmpty())
    {
        return (false);
    }
    else
    {
        *x = A[head];
        head++;//To delete element from array we only grow head size.
        return (true);
    }
}