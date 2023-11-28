#include "iostream"
using namespace std;
//Implementing my own vector class

// Template class to create V 
template <typename T>
class V 
{
private:
    T* arr;
    // Variable to store the current capacity of the V
    int capacity; 
    // Variable to store the length of V
    int length;
 
public:
    explicit V(int = 100);
    int push_back(T);  // Function that returns the number of elements in array after pushing the data
    int size() const; // Function that return the size of V 
    T& operator[](int);
 
};
 
// Template class to return the size of V 
template <typename T>
V<T>::V(int n)
    : capacity(n), arr(new T[n]), length(0)
{}
 
// Template class to insert the element in V
template <typename T>
int V<T>::push_back(T v)
{
    if (length == capacity) 
    {
        T* old = arr;
        arr = new T[capacity = capacity * 2];
        copy(old, old + length, arr);
        delete[] old;
    }
    arr[length] = v;
    length++;
    return length;
}


// Template class to return the size of V
template <typename T>
int V<T>::size() const
{
    return length;
}
 
// Template class to return the element of V at given index
template <typename T>
T& V<T>::operator[](int index)
{
    // return value at that index
    return *(arr + index);
}

