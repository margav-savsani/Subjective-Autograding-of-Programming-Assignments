#include <iostream>
using namespace std;
#include "dictionary.h"
#include <cmath>

Dictionary::Dictionary()
{
    N = 64;                             //Max Dict Size
    A = new Entry[DICT_SIZE];
    for (int i = 0; i < N; i++)
    {
        strcpy(A[i].key, "");           //Initialising all keys to be ""
    }
}

int Dictionary::hashValue(char key[])
{
    int x = 2;
    double pseudo_key = 0;
    int size;
    for (size = 0; size < 32; size++)
    {
        if (key[size] == '\0')
        {
            break;
        }
    }
    double A = (sqrt(5) - 1) / 2;
    size--;
    for (; size >= 0; size--)
    {
        pseudo_key = (key[size] - '\0') * A + pseudo_key * x;
        pseudo_key = pseudo_key - int(pseudo_key);                      //taking mod to avoid overflow
    }
    int hash_value = DICT_SIZE * pseudo_key;
    return hash_value;
}

int Dictionary::findFreeIndex(char key[])
{
    int l = hashValue(key);
    for (int i = 0; i < 64; i++)
    {
        if (strcmp(A[l].key, "") == 0)
        {
            return l;
        }
        else if (strcmp(A[l].key, "TOMB") == 0)
        {
            return l;
        }
        l = (l + 1) % N;
    }
    return -1;
}
struct Entry *Dictionary::get(char key[])
{
    int l = hashValue(key);
    for (int i = 0; i < 64; i++)
    {
        if (strcmp(A[l].key, key) == 0)
        {
            return &A[l];
        }
        if (strcmp(A[l].key, "") == 0)
        {
            return NULL;
        }
        l = (l + 1) % N;
    }
    return NULL;
}
struct same_start Dictionary::get_all(char s1[])            //specifically for planner it returns all values corresponding to a given key
{
    int l = hashValue(s1);
    same_start S;
    int s = 0;
    for (int i = 0; i < 64; i++)
    {
        if (strcmp(A[l].key, s1) == 0)
        {
            S.entries[s] = A[l];
            s++;
        }
        else if (strcmp(A[l].key, "") == 0)
        {
            break;
        }
        l++;
    }
    S.n = s;
    return S;
}
bool Dictionary::put(struct Entry e)
{
    int l = findFreeIndex(e.key);
    if (l == -1)
    {
        return false;
    }
    A[l] = e;
    return true;
}

bool Dictionary::remove(char key[])
{
    struct Entry *k = get(key);
    if (k)
    {
        strcpy(k->key, "TOMB");
        k->value1 = 0;
        k->value2 = 0;
        return true;
    }
    return false;
}