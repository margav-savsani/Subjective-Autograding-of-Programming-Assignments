#include "dictionary.h"
using namespace std;

int hashX = 33;
double fibboConst = (pow(5, 0.5) - 1)/2;

double hashMap(char EntryKey[])
{
    if(EntryKey[1]==0) return hashX*EntryKey[0];

    return (EntryKey[0] + hashX*hashMap(&EntryKey[1]));
}

Dictionary::Dictionary()
{
    N = DICT_SIZE;
    A = new Entry[N];
    for(int i = 0; i<N; i++)
    {
        strcpy(A[i].key, "EMPTY");
    }
}

int Dictionary::hashValue(char key[])
{
    double num = hashMap(key)*fibboConst;
    double fracPart = num - int(num);

    return int(N*fracPart);
}

int Dictionary::findFreeIndex(char key[])
{
    int num_key = hashValue(key);
    int j = 0;
    for(int i = num_key; true; (i++)%N)
    {
        if(string(A[i].key)=="EMPTY") return i;
        if(string(A[i].key)=="TOMB") continue;

        if(i == N-1) j++;
        if(j==1) break;   
    }

    return -1;
}

struct Entry* Dictionary::get(char key[])
{
    int num_key = hashValue(key);

    if(string(A[num_key].key) == string(key)) return &A[num_key];
    else return NULL;
}

bool Dictionary::put(struct Entry e)
{
    int num_key = hashValue(e.key);
    int j=0;
    for(int i = num_key; true; (i++)%N)
    {
        if(string(A[i].key) =="EMPTY")
        {
            strcpy(A[i].key, e.key);
            return true;
        }
        if(string(A[i].key)=="TOMB") continue;
        if(i==N-1) j++;
        if(j==1) break;
    }

    return false;
}

bool Dictionary::remove(char key[])
{
    int num_key = hashValue(key);
    int j=0;
    for(int i = num_key; true; (i++)%N)
    {
        if(string(A[i].key)== string(key))
        {
            strcpy(A[i].key, "TOMB");
            return true;
        }
        if(i==N-1) j++;
        if(j==1) break;
    }

    return false;
}