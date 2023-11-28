#include <bits/stdc++.h>
#include "dictionary.h"
#include <string.h>
using namespace std;
int Dictionary::hashValue(char key[])
{
    unsigned int size = 0;
    int myx = 33;
    string str = key;
    int n = str.length();

    for (int i = n - 1; i >= 0; i--)
    {
        size = (size * myx + (key[i] - 97)) % (10000019);
    }
    double a = 0.618033988;
    double x = size * a;

    x = x - int(x);
    size = int(DICT_SIZE * x);
    int hashcode = size;
    return hashcode;
}

Dictionary::Dictionary()
{
    N = DICT_SIZE;
    A = new Entry[N];
}
int Dictionary::findFreeIndex(char key[])
{
    int k = hashValue(key);
    if (A[k].value1 < 0)
    {
        return k;
    }
    k = (k + 1) % DICT_SIZE;
    while (k != hashValue(key))
    {
        if (A[k].value1 < 0)
        {
            return k;
        }
        k = k + 1;
        k = k % DICT_SIZE;
    }
    return -1;
}
struct Entry *Dictionary::get(char key[])
{
    int k = hashValue(key);
    int count = 0;

    Entry *B = new Entry[DICT_SIZE];
    if (strcmp(A[k].key1, key) == 0)
    {
        B[count] = A[k];
        count++;
    }
    if (A[k].value1 == -1.0)
    {
        return NULL;
    }

    k = (k + 1) % DICT_SIZE;
    while (k != hashValue(key))
    {

        if (A[k].value1 < 0)
        {
            k = (k + 1) % DICT_SIZE;
            continue;
        }

        if (strcmp(A[k].key1, key) == 0)
        {
            B[count] = A[k];
            count++;
        }
        k = (k + 1) % DICT_SIZE;
    }
    if (count == 0)
    {
        return NULL;
    }

    return B;
}
bool Dictionary::put(struct Entry e)
{
    int k = findFreeIndex(e.key1);
    if (k == -1)
    {
        return false;
    }
    strcpy(A[k].key1, e.key1);
    strcpy(A[k].key2, e.key2);
    A[k].value1 = e.value1;
    A[k].value2 = e.value2;

    return true;
}
bool Dictionary::remove(char key[])
{
    if (get(key) != NULL)
    {
        get(key)->value1 = -2.0;
        return true;
    }
    return false;
}
