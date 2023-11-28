#include <iostream>
#include "dictionary.h"
#include <math.h>
using namespace std;

int total_numbers = 0;

int Dictionary::hashValue(char key[])
{
    int sum = 0;
    int i = 0;

    while (key[i] != '\0')
    {

        sum = (sum + int(key[i])) * 37;
        i++;
    }

    double final_hash, a = (sqrt(5) - 1) / 2;
    final_hash = sum;
    final_hash *= a;
    final_hash = (final_hash - floor(final_hash)) * N;
    final_hash = floor(final_hash);
    return final_hash;
}


int Dictionary::findFreeIndex(char key[])
{
    int index = hashValue(key);
    for (int i = 0; i < N; i++)
    {
        if(A[index].check == false)
            return index;
        else 
            index = (index + 1)%N;
    }
    return -1;
}
struct Entry *Dictionary::get(char key[])
{
    for (int i = 0; i < N; i++)
    {
        if (A[i].key == key)
        {
            if (A[i].check == true)
                return &A[i];
        }
    }
    return NULL;
}

bool Dictionary::put(struct Entry e)
{
    int s_ind = findFreeIndex(e.key); 
    if (s_ind = -1)
        return false;
    else
    {
        A[s_ind] = e;
        A[s_ind].check = true;
        A[s_ind].tombs = !A[s_ind].check;
        return true;
    }
}

bool Dictionary::remove(char key[])
{
    if (get(key) == NULL)
        return false;
    for (int i = 0; i < N; i++)
    {
        if (A[i].key == key)
        {
            if (A[i].check == true)
            {
                A[i].tombs = true;
                A[i].check = !A[i].tombs;
                return true;
            }
        }
    }
}