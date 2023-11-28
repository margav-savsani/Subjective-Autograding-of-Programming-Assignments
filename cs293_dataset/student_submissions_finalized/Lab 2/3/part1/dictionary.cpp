#include<iostream>
#include<string.h>
#include<math.h>
#include"dictionary.h"

using namespace std;

const int const_variable = 2;
const double febonci = ((pow(5,0.5) - 1)/2);

int Dictionary :: hashValue(char key[])
{
    int sum = 0;
    for(int i=0;i<32,key[i] != '\0';i++)
    {
        sum = sum + (key[i]*pow(const_variable,i));
    }
    double k = sum%64;
    int m = k* febonci;
    k = k*febonci;
    k = k - m;
    k = k*64;
    m = k;
    return m;
}

int Dictionary :: findFreeIndex(char key[])
{
    int hash = hashValue(key);
    int a = -1;

    for(int i = hash,j=0;j<64;j++)
    {   
        if(A[i].key == NULL || A[i].key == "$")
        {
            a=i;
        }
        i = (i+1)%64;
    }
    return a;
}

struct Entry* Dictionary :: get(char key[])
{
    int hash = hashValue(key);
    for(int i = hash,j=0;j<64;j++)
    {   
        if(A[i].key == key)
        {
            struct Entry *B;
            *B = A[i];
            return B;
        }
        else if (A[i].key == "$")
        {
            i++;
        }
        else if (A[i].key == NULL)
        {
            return NULL;
        }
        else i = (i+1)%64;
    }
    return NULL;
}

bool Dictionary :: put(struct Entry e)
{
    int hash = hashValue(e.key);
    for(int i = hash,j=0;j<64;j++)
    {
        if (A[i].key == NULL || A[i].key == "$")
        {
            A[i] = e;
            return true;
        }
        else i = (i+1)%64;
    }
    return false;
}

bool Dictionary :: remove(char key[])
{
    if(get(key) != NULL)
    {
        get(key)->key == "$";
        return true;
    }
    return false;
}