#include <bits/stdc++.h>
#include "dictionary.h"
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
    for (int i = 0; i < N; i++)
    {
        A[i].value = -1;
       
    }
}
int Dictionary::findFreeIndex(char key[]){
    int k=hashValue(key);
    if(A[k].value <0){
        return k;
    }
    k=(k+1)%DICT_SIZE;
    while (k != hashValue(key)){
        if(A[k].value < 0){
            return k;
        }
        k=k+1;
        k=k%DICT_SIZE;
    }
    return -1;
    }
struct Entry *Dictionary::get(char key[])
{
    int k=hashValue(key);
    if(A[k].value != -2){
    if(strcmp(A[k].key,key) == 0){
        return &A[k];
    }
    if(A[k].value  == -1){
            return NULL;
        }
        }

    k=(k+1)% DICT_SIZE;
    while(k!=hashValue(key)){
        if(A[k].value  == -1){
            return NULL;
        }
        if(A[k].value == -2){
        	k=(k+1)%DICT_SIZE;
        	continue;
        	}
        if(strcmp(A[k].key,key) == 0){
            return &A[k];

        }
        k=(k+1)% DICT_SIZE;
    }
    return NULL;
    
}
bool Dictionary::put(struct Entry e)
{
     int k =findFreeIndex(e.key);
    if (k == -1)
    {
        return false;
    }
    strcpy(A[k].key,e.key);
    A[k].value=e.value;


    return true;
}
bool Dictionary::remove(char key[])
{
    if (get(key) != NULL)
    {
        get(key)->value = -2;
        return true;
    }
    return false;
}
