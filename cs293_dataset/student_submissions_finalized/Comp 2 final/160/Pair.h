#include "std_headers.h"
template <typename T>
class Pair // class for pair node
{
public:
    T first;
    T second;
    Pair(T a, T b)
    {
        first = a;
        second = b;
    }
    Pair()
    {
    }
};
template <typename T>
bool operator==(Pair<T> obj1, Pair<T> obj2) // overloaded operator
{
    return (obj1.first == obj2.first && obj1.second == obj2.second);
}

// this is second one '!='
template <typename T>
bool operator!=(Pair<T> obj1, Pair<T> obj2) // overloaded operator
{
    return !(obj1.first == obj2.first && obj1.second == obj2.second);
}
template <typename T>
Pair<T> make_pair(T a, T b) // make pair when first and second are given
{
    return Pair<T>(a, b);
}