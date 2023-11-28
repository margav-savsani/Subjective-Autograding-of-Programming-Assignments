#include <iostream>
#include <cmath>
#include <cstring>
#include "dictionary.h"
using namespace std;

Dictionary ::Dictionary()
{
    N = DICT_SIZE;
    A = new Entry[N];
    for(int i=0; i<N; i++)
    {
        A[i].key=NULL;
    }
}
int Dictionary ::hashValue(char key[])
{
    const int p = 33;
    int k = 0;
    for (int i = 0; sizeof(key[0]); i++)
    {
        k = k + key[i]*pow(p, i);
    }
    int A = (sqrt(5) - 1) / 2;
    int m = DICT_SIZE;
    int hashValue = floor(m * ((k * A) % 1));
    return hashValue;
}
int Dictionary ::findFreeIndex(char key[])
{
    int size = sizeof(key[0]);
    int hashIndex = hashValue(key);
    while (A[hashIndex].key != NULL)
    {
        if ((A[hashIndex].key == NULL) || (A[hashIndex].key == "deletd"))
            return hashIndex;

        // go to next cell
        ++hashIndex;

        // wrap around the table
        hashIndex %= size;
    }
    return -1;
}
struct Entry *Dictionary ::get(char key[])
{
    int hashIndex = hashValue(key);
    struct Entry * ptr;
    while (A[hashIndex].key != NULL)
    {
        if ((A[hashIndex].key == key) || (A[hashIndex].key == "deletd"))
            *ptr = A[hashIndex];
            return ptr;

        // go to next cell
        ++hashIndex;

        // wrap around the table
        hashIndex %= N;
    }
    return NULL;
}
bool Dictionary ::put(struct Entry e)
{
    if(findFreeIndex(e.key) == -1)
    {
        return false;
    }
    int free = findFreeIndex(e.key);
    A[free] = e;
    return true;
}
bool Dictionary ::remove(char key[])
{
    if(findFreeIndex(key) == -1)
    {
        return false;
    }
    int hashIndex = hashValue(key);
    while (A[hashIndex].key != NULL)
    {
        if (A[hashIndex].key == key)
            A[hashIndex].key="deleted";

        // go to next cell
        ++hashIndex;

        // wrap around the table
        hashIndex %= N;
    }
    return true;
}