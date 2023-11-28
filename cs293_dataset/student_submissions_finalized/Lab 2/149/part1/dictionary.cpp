#include <iostream>
#include "dictionary.h"
#include <cmath>
using namespace std;

int Dictionary::hashValue(char *key)
{   
    int i, sum = 0, x = 33;
    for (i = 0; i < 31; i++)
    {   
        if(key[i] == '\0') break;
        sum += (key[i]-50)*pow(x,i);
    }
    double hash = sum * (sqrt(5) - 1) / 2;
    hash = abs(hash - (int)hash);
    hash = hash * N;
    hash = floor(hash);
    return hash;
}

int Dictionary::findFreeIndex(char *key)
{
    int ind = hashValue(key);
    int k = ind;
    while (true)
    {
        if (A[ind].value == -1)
            return ind;
        else
            ind++;
        if (ind == N)
        {
            ind = 0;
        }
        if (ind == k)
        {
            return -1;
        }
    }
}

bool Dictionary::put(struct Entry e)
{
    int x = findFreeIndex(e.key);
    if (x == -1)
        return false;
    else
    {
        A[x] = e;
        return true;
    }
}

bool Dictionary::remove(char key[])
{
    Entry *e = get(key);
    if(e == NULL)return false;
    else{
        e->value = -1;
        return true;
    }
}

Entry* Dictionary::get(char key[])
{
    for (int i = 0; i < N; i++)
    {
        if (strcmp(A[i].key, key) == 0 && A[i].value != -1)
        {
            return &A[i];
        }
    }
    return NULL;
}