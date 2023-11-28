template <typename T>
bool DynamicQueue<T>::isEmpty()
{
    return (head == tail);// In Circular if head is equal to tail then it is empty.
}

template <typename T>
bool DynamicQueue<T>::isFull()
{
    return (tail + 1) % N == head;//Return true if Array is full. 
}


template <typename T>
void DynamicQueue<T>::grow()
{
    T *B;                        // Creates new Array
    B = new T[N + CONST_GROWTH]; // Assigns elements of previous array(A) to new array (B)
    for (int i = head; i < (head + N); i++)
    {
        B[i - head] = A[i % N];
    }
    A = B;
    head = 0;//In new array head is zero
    tail = N - 1;//As allraedy Array A is full so tail= N-1 because we are leaving 1 element for our convinence
    N = N + CONST_GROWTH;// Changes N value after growth
}

template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return (tail - head + N) % N;// modulo is used because, in circular list tail can occur before head
}

template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if (isFull())
    {
        grow();// Growing array size
    }
    A[tail] = x;//Inserts new element
    tail = (tail + 1) % N;//Grows tail by 1 after inserting an element using modulo
}

template <typename T>
bool DynamicQueue<T>::QDelete(T *x)
{
    if (isEmpty())
    {
        return (false);
    }
    *x = A[head];
    head = (head + 1) % N;//To delete element from array we only grow head size using modulo.
    return (true);
}
