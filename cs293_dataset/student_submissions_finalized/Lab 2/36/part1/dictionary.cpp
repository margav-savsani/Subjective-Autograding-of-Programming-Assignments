#include "dictionary.h"
#include <cmath>
using namespace std;

int Dictionary::hashValue(char key[])
{
    int hash_v = 0;
    int x = 33;
    int y = 1;
    int lastindex;
    for (int i=0;i<32;i++) {
        if (key[i]=='\0') {lastindex=i;break;}
    }
    for (int i=lastindex-1;i>0;i--) {
        hash_v=(hash_v +key[i])*x;
        hash_v=hash_v%DICT_SIZE;
    }
    hash_v+=key[0];
    return hash_v%DICT_SIZE;
}

int Dictionary::findFreeIndex(char key[])
{   int t=0;
    int hash_v = hashValue(key);
    while (t<DICT_SIZE)
    {
        if (A[hash_v].tombstone != 2)
        {
            return hash_v;
        }
        else
            hash_v++;
            t++;
    }
    return -1;
}

Dictionary::Dictionary()
{
    N = 0;
    A = new struct Entry[DICT_SIZE];
}

struct Entry *Dictionary::get(char key[])
{
    int hash_v = hashValue(key);
    while (A[hash_v].tombstone != 0 && A[hash_v].tombstone !=1)
    {
        if (strcmp(A[hash_v].key, key)==0)
        {
            return &A[hash_v];
        }
        hash_v++;
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
    A[index].tombstone = 2;
    N++;
    return true;
}

bool Dictionary::remove(char key[])
{
    if (get(key) == NULL)
    {   
        return false;
    }
    int hash_v = hashValue(key);
    while (&A[hash_v].tombstone != 0)
    {
        if (strcmp(A[hash_v].key , key)==0)
        {
            A[hash_v].tombstone = 1;
            N--;
            return true;
        }
        hash_v++;
    }
    return false;
}