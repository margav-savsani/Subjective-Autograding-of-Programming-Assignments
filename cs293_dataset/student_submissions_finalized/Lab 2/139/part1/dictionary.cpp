#include "dictionary.h"
#include <iostream>
#include <string.h>
using namespace std;

Dictionary::Dictionary()
{
    N = DICT_SIZE;
    A = new Entry[N];
}

int Dictionary::hashValue(char key[])
{
    int hash = 0, p = 33;
    int a = 2, b = 3;
    long p_degree = 1;
    int n = 0;
    while (key[n] != '\0')
    {
        n++;
    }
    for (int i = 0; i < n; ++i)
    {
        hash = (hash + (key[i] - 'a' + 1) * p_degree);
        p_degree = (p_degree * p);
    }
    return (a * (hash) + b) % N;
}

int Dictionary::findFreeIndex(char key[])
{
    int hash_value = hashValue(key);

    for (int i = hash_value; i < N; i++)
    {
        if (A[i].status == 0 || A[i].status == 2)
        {
            return i;
        }
    }
    return -1;
}

struct Entry *Dictionary::get(char key[])
{
    int hash_value = hashValue(key);
    while (A[hash_value].status != 0)
    {
        int i = 0;
        bool a = true;
        while (key[i] != '\0')
        {
            if (A[hash_value].key[i] != key[i])
            {
                a = false;
            }
            i++;
        }
        if (a && A[hash_value].status == 1)
            return &A[hash_value];
        hash_value++;
    }
    return NULL;
}
bool Dictionary::put(struct Entry e)
{
    int index = findFreeIndex(e.key);
    if (index == -1)
    {
        return false;
    }
    A[index] = e;
    A[index].status = 1;
    return true;
}

bool Dictionary::remove(char key[])
{
    struct Entry *X = get(key);
    if (X == NULL)
    {
        return false;
    }
    X->status = 2;
    return true;
}