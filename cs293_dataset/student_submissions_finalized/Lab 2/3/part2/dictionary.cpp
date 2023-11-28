#include<iostream>
#include<string.h>
#include<math.h>
#include"dictionary.h"

using namespace std;

int Dictionary :: hashValue(char key[])
{
    int sum = 0;                          // for polynomial sum
    for(int i=0;key[i] != '\0';i++)
    {
        sum = const_variable*sum + key[i];
        sum = sum%1111117;
    }
    double k = sum%1111117;
    int m = k* febonci;
    k = k*febonci;
    k = k - m;                                      // to get fractional part
    k = k*DICT_SIZE;
    m = k;
    return m;
}

int Dictionary :: findFreeIndex(char key[])
{
    int hash = hashValue(key);
    int a = -1;

    for(int i = hash,j=0;j<N;j++)
    {   
        if(A[i].key[0]==empty || A[i].key[0]==tomb) // checks for free space
        {
            a=i;
	        break;
        }
        i = (i+1)%N;                                // so that it searchs all places
    }
    return a;
}

struct Entry* Dictionary :: get(char key[])
{
    int hash = hashValue(key);
    for(int i = hash,j=0;j<DICT_SIZE;j++)
    {
        if(strcmp(A[i].key, key) == 0)              // check if the key matches
        {
            return &A[i];
        }
        else if (A[i].key[0]==empty)                // means it doesnt contain a tomb or a key
        {
            return NULL;
        }
        else i = (i+1)%DICT_SIZE;
    }
    return NULL;
}

bool Dictionary :: put(struct Entry e)              // ins an element
{
    int hash = hashValue(e.key);
    for(int i = hash,j=0;j<DICT_SIZE;j++)
    {
        if (A[i].key[0]==empty || A[i].key[0]==tomb)// checks for free space
        {
            A[i] = e;
            return true;
        }
        else i = (i+1)%DICT_SIZE;
    }
    return false;
}

bool Dictionary :: remove(char key[])               // dels element
{
    if(get(key) != NULL)
    {       
        get(key)->key[0]=tomb;                      // creates a tomb
        return true;
    }
    return false;
}
