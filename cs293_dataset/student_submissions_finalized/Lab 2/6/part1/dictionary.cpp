#include "dictionary.h"
#include<cmath>
float frac(float num)
{
    return num - floor(num);
}
float power_mod(int coeff, int base, int pow)
{
    if(pow==0)
    return frac(coeff);
    int value = 0;
    for(int i = 0; i<pow; i++)
    value = frac(value*base);
    value = frac(value*coeff);
    return value;
}

Dictionary:: Dictionary()
{
    N = DICT_SIZE;
    for(int i=0; i<N; i++)
    {
        A[i].present = false; A[i].TOMB_STONE = false;
        A[i].value = -1; //A[i].key = '\0';
    }
}

int Dictionary:: hashValue(char key[])
{
    int sz =0;
    for(int i=0;i<32;i++)
    {
        if (key[i]!='\0') sz++;
        else break;
    }
    int Num[sz];
    for(int i=0; i<sz; i++)
    {
        Num[i] = (int)key[i];
    }
    int x = 37;
    int ans = 0;
    float fib_const = (sqrt(5) - 1)/2;
    for(int j=0; j<sz; j++)
    {
        ans = frac(ans + power_mod(fib_const*Num[j], x, j));
    }
    int hash_ = floor(N*ans);
    return hash_;
}

int Dictionary:: findFreeIndex(char key[])
{
    int hash_ = hashValue(key);
    int up_val = hash_;
    int count = 0;
    while(A[up_val].present)
    {
        (up_val+1)%N; count++;
    }
    if(count>=N) return -1;
    A[up_val].present = true;  A[up_val].TOMB_STONE = false;
    //A[up_val].key = key; A[up_val].value = up_val;
    return up_val;
}

struct Entry* Dictionary::get(char key[])
{
    for(int i=0; i<N; i++)
    {
        if(strcmp(A[i].key,key)==0 && A[i].present) return &A[i];
    }
    return NULL;
}

bool Dictionary:: put(struct Entry e)
{
    int hash_ = hashValue(e.key);
    int pos = findFreeIndex(e.key);
    if(pos!=-1)
    {
        A[pos] = e;
        A[pos].present = true;
        return true;
    }
    return false;
}

bool Dictionary:: remove(char key[])
{
    if(get(key)==NULL) return false;
    for(int i=0; i<N; i++)
    {
        if(A[i].key==key && A[i].present)
        {
            A[i].TOMB_STONE = true;
            A[i].present = false;
            return true;
        }
    }
    return false;
}
