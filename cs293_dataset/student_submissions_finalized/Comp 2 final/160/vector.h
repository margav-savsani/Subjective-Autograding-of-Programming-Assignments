#include "std_headers.h"
// using namespace std;

template <class T>
class Vector
{
private:
    unsigned int my_size;     // size till now
    unsigned int my_capacity; // capacity of vector
    T *buffer;                // storing array

public:
    Vector();
    ~Vector();

    unsigned int capacity() const;
    unsigned int size() const;
    bool empty() const;
    void push_back(const T &value); // insert
    bool find(T a);                 // find
    void reserve(unsigned int capacity);
    void resize(unsigned int size);
    T max(); // max of vector
    T &operator[](unsigned int index);
    Vector<T> &operator=(const Vector<T> &);
    void clear();
};

// Your code goes here ...
template <class T>
Vector<T>::Vector()
{
    my_capacity = 0;
    my_size = 0;
    buffer = 0;
}
template <class T>
T Vector<T>::max()
{
    T a = buffer[0];
    for (int i = 1; i < size(); i++)
    {
        if (a < buffer[i])
            a = buffer[i];
    }
    return a;
}

template <class T>
bool Vector<T>::find(T a)
{
    for (int i = 0; i < my_size; i++)
    {
        if (buffer[i] == a)
            return true;
    }
    return false;
}

template <class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &v)
{
    delete[] buffer;
    my_size = v.my_size;
    my_capacity = v.my_capacity;
    buffer = new T[my_size];
    for (unsigned int i = 0; i < my_size; i++)
        buffer[i] = v.buffer[i];
    return *this;
}

template <class T>
void Vector<T>::push_back(const T &v)
{
    if (my_size >= my_capacity)
        reserve(my_capacity + 5);
    buffer[my_size++] = v;
}

template <class T>
void Vector<T>::reserve(unsigned int capacity)
{
    if (buffer == 0)
    {
        my_size = 0;
        my_capacity = 0;
    }
    T *Newbuffer = new T[capacity];
    // assert(Newbuffer);
    unsigned int l_Size = capacity < my_size ? capacity : my_size;
    // copy (buffer, buffer + l_Size, Newbuffer);

    for (unsigned int i = 0; i < l_Size; i++)
        Newbuffer[i] = buffer[i];

    my_capacity = capacity;
    delete[] buffer;
    buffer = Newbuffer;
}

template <class T>
unsigned int Vector<T>::size() const //
{
    return my_size;
}

template <class T>
void Vector<T>::resize(unsigned int size)
{
    reserve(size);
    my_size = size;
}

template <class T>
T &Vector<T>::operator[](unsigned int index)
{
    return buffer[index];
}

template <class T>
unsigned int Vector<T>::capacity() const
{
    return my_capacity;
}

template <class T>
Vector<T>::~Vector()
{
    delete[] buffer;
}
template <class T>
void Vector<T>::clear()
{
    my_capacity = 0;
    my_size = 0;
    buffer = 0;
}
