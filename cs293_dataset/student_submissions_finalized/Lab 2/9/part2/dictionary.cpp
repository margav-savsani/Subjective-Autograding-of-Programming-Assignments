#include <iostream>
#include <string.h>
#include "dictionary.h"
#include <cmath>
using namespace std;

Dictionary::Dictionary()
{
    N = DICT_SIZE;
    A = new Entry[N];

    for (int i = 0; i < N; i++)
    {
        A[i].key[0] = 0;
    }
}

int Dictionary::hashValue(char key[])
{
    int mult = 1;
    double p = 0;
    // random prime for polynomial accumulation
    int x = 31;
    double A = (sqrt(5) - 1) / 2;
    int m = N; // pow(2, 6);
    int hv;
    int i = 0;
    while (key[i] != 0)
    {
        // polynomial accumulation
        p += (key[i] - 'a' + 1) * mult;
        i++;
        // compression
        p = p * A;
        p = p - (int)p;
    }

    hv = m * p;
    return hv;
}

int Dictionary::findFreeIndex(char key[])
{
    int hv = hashValue(key);
    int i = hv;
    while (hv != (i + 1) % N)
    {
        if (strcmp(A[i].key, key) == 0)
        {
            cout << "Key already exists.\n";
            return -1;
        }
        if (A[i].key[0] == 0 or A[i].key[0] == 95)
        {
            return i;
        }
        i++;
        i %= N;
    }
    return -1;
}

struct Entry *Dictionary::get(char key[])
{
    int i = hashValue(key);
    while (A[i].key[0] != 0)
    {
        if (strcmp(A[i].key, key) == 0)
        {
            return A + i;
        }
        i++;
        i %= N;
    }
    return NULL;
}

bool Dictionary::put(Entry e)
{
    int i = findFreeIndex(e.key);
    A[i] = e;
    return 1;
}

bool Dictionary::remove(char *key)
{
    if (get(key) == NULL)
    {
        return 0;
    }
    // _ (underscore) is the tombstone
    get(key)->key[0] = 95;
    return 1;
}
