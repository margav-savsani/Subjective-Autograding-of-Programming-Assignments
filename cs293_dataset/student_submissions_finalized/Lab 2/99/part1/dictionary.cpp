#include <iostream>
#include "dictionary.h"
#include <cmath>
#include <climits>
#include <cstring>

using namespace std;

const double x = 33;
const double fibval = (sqrt(5) - 1)/2; 

//INT_MAX means null
//INT_MIN means tombstone

// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
int Dictionary::hashValue(char key[])
{
    //cout << "hashValue\n";
    double sum = 0;
    int i = 0;
    while (key[i] != '\0')
    {
        double add = fibval*key[i];
        add = add - int(add);
        sum = sum*x + add;
        sum = sum - int(sum);
        i++;
    }
    int hv = (sum * 64);
    //hv = hv % 64;
    return hv;
}

// Find the position where given key can be inserted (after resolving hash collision if any); 
//return value between 0 and N-1 if free location present; return -1 if no free location
int Dictionary::findFreeIndex(char key[])
{
    //cout << "findFreeIndex\n";
    int start = hashValue(key);
    while (start < 64)
    {
        if (A[start].value == INT_MAX || A[start].value == INT_MIN) return start;
        start++;
    }
    return -1;
}
  
// Default constructor
Dictionary::Dictionary()
{
    //cout << "constructor\n";
    N = 64;
    A = new Entry[64];
    for (int i = 0; i < 64; i++)
    {
        A[i].value = INT_MAX;
    }
    //cout << "consend\n";
} 

// Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
struct Entry * Dictionary::get(char key[])
{
    //cout << "get\n";
    int start = hashValue(key);
    while (A[start].value != INT_MAX && start < 64)
    {
        //char arr[A[start].key.length() + 1];
        //strcpy(arr, A[start].key.c_str())
        if (A[start].value == INT_MIN) continue;
        string tmp1(key), tmp2(A[start].key);
        if (tmp1 == tmp2) return &A[start];
        start++;
    }
    return NULL;
}

// Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
bool Dictionary::put(struct Entry e)
{
    //cout << "put\n";
    //char arr[e.key.length() + 1];
    //strcpy(arr, e.key.c_str());
    int p = findFreeIndex(e.key);
    if (p == -1) return 0;
    for (int i = 0; i < 32; i++)
    {
        A[p].key[i] = e.key[i];
    }
    A[p].value = e.value;
    return 1;
}

// Remove the given key; return true if success, false if failure (given key not present)
bool Dictionary::remove(char key[])
{
    //cout << "remove\n";
    int start = hashValue(key);
    while (A[start].value != INT_MAX && start < 64)
    {
        if (A[start].value == INT_MIN) 
        {
            start++;
            continue;
        }
        string tmp1(key), tmp2(A[start].key);
        if (tmp1 == tmp2)
        {
            A[start].value = INT_MIN;
            return 1;
        }
        start++;
    }
    //cout << "here\n";
    return 0;
}