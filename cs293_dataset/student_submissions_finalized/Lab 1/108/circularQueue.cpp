#include <cstring>  // for memcpy function

// Checks if the queue is empty or not
template <typename T>
bool DynamicQueue<T>::isEmpty() {
    return head == tail;
}

// Checks if the queue is full or not
template <typename T>
bool DynamicQueue<T>::isFull() {
    return tail == N;  // tail is N when queue is full
}

// Returns number of elements currently in the queue
template <typename T>
unsigned int DynamicQueue<T>::size() {
    int sz = isFull() ? N : tail-head;
    if (tail < head) sz += N;  // If the queue is circling around then add length of array
    return sz;
}

// Grows the array that holds the values in the queue by a 
// constant amount.
//
// It allocates memory for a new array, then copies all 
// elements from head to the end of the old array, followed 
// by elements from start to tail(head). 
// In the end, it frees up the memory of the old array and 
// makes the old array pointer point to the new array.
template <typename T>
void DynamicQueue<T>::grow() {
    T *Q = new T[N + CONST_GROWTH];
    std::memcpy(Q, A+head, (N-head)*sizeof(T));
    std::memcpy(Q+N-head, A, head*sizeof(T));
    head = 0;
    N += CONST_GROWTH;
    delete[] A;
    A = Q;
}

// Inserts a new element at the appropriate place(at tail) 
//
// When the array becomes full tail is set to N, since when
// the array will grow, the new insert will be at location N.
template <typename T>
void DynamicQueue<T>::QInsert(T x) {
    if (isFull()) grow();
    if (isEmpty()) head = tail;
    A[tail++] = x;
    if (tail == N) tail -= N;  // If tail reaches end then circle around
    if (head == tail) tail = N;  // If array becomes full then set tail to N
}

// Removes the approptiate element(element at the location head) from the queue and returns 
// the success of deletion, if the queue is empty then returns false and vice versa.
// Also, sets the parameter x to be the removed element
template <typename T>
bool DynamicQueue<T>::QDelete(T* x) {
    if (isEmpty()) return false;
    if (tail == N) tail = head;  // Update tail if array was full
    *x = A[head++];
    if (head == N) head -= N;  //If head reaches the end, then circle around

    return true;
}