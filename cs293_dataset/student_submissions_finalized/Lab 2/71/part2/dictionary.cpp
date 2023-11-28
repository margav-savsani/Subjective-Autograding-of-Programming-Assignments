#include <iostream>
#include <cmath>
#include "dictionary.h"
using namespace std;

int Dictionary::hashValue(char key[])
{
    long long int hash = 0;
    long long int x = 1;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash += (x * int(key[i]));
        x *= 33;
    }
    long double temp1 = hash * ((sqrt(5) - 1) / 2), int_part;
    double temp2 = modf(temp1, &int_part);
    int final = int(DICT_SIZE * temp2);
    return final;
}

int Dictionary::findFreeIndex(char key[])
{
    int hash = hashValue(key);
    if ((A[hash].key()[0] == '\0') || (A[hash].get_t() == true))
        return hash;
    int i = (hash + 1)%N;
    while (i != hash)
    {
        if ((A[i].key()[0] == '\0') || A[i].get_t() == true)
            return i;
        i = (i + 1) % N;
    }
    return -1;
}

Dictionary::Dictionary()
{
    N = DICT_SIZE;
    A = new Entry[DICT_SIZE];
}

Entry *Dictionary::get(char key[])
{
    int i=hashValue(key);
    while(A[i].key()[0]!='\0'){
        if (string(A[i].key()) == string(key)&&(A[i].get_t()==false)) return &A[i];
        i=(i+1)%N;
    }
    return NULL;
}

bool Dictionary::put(Entry e)
{
    int z = findFreeIndex(e.key());
    if (z == -1)
        return false;
    else
    {
        A[z] = e;
        return true;
    }
}

bool Dictionary::remove(char key[])
{
    if (get(key) == NULL)
        return false;
    else
    {
        get(key)->get_t() = true;
        return true;
    }
}