#include "dictionary.h"
#include <iostream>
#define fib 0.6180339

// returns (key[0] + key[1]*val + key[2]*val^2 ... key[n-1]*val^(n-1)) % mod
int hash_code_map(const char key[], int val, int mod)
{
    int ans = 0;
    for(int i = strlen(key) - 1; i>=0; --i)
    {
        ans *= val;
        ans += static_cast<int>(key[i]);
        ans %= mod;
    }
    return ans;
}

// returns fractional part of a double
double frac(double val)
{
    return val - static_cast<int>(val);
}

// Default constructor
// If Entry::empty is true, the Entry is Empty
// If the Entry::tomb is true, it is a tombstone. If Entry::tomb is true, Entry::empty will always be false
Dictionary::Dictionary(): A(new Entry[DICT_SIZE]), N(DICT_SIZE) {}

// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
int Dictionary::hashValue(const char key[]) const
{
    return static_cast<int>(N*frac(hash_code_map(key, 37, 701)*fib)); // use 37 for polynomial accumulation, and take mod 701
}


// Find the position where given key can be inserted (after resolving hash collision if any); 
// return value between 0 and N-1 if free location present; 
// return -1 if no free location
int Dictionary::findFreeIndex(const char key[]) const
{
    int hv = hashValue(key);
    int probe = hv;
    while(!A[probe].empty && !A[probe].tomb)
    {
        probe = (1 + probe) % N;
        if(probe == hv) return -1;
    }
    return probe;
}

// Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
struct Entry* Dictionary::get(const char key[])
{
    int ohv = hashValue(key);
    int hv = ohv;
    while(true)
    {
        if(A[hv].empty) return nullptr;
        if(!A[hv].tomb && strcmp(key, A[hv].key) == 0) return (A+hv);
        hv = (1 + hv)%N;
        if(hv == ohv) return nullptr;
    }
}

// Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
bool Dictionary::put(struct Entry e)
{
    int ind = findFreeIndex(e.key);
    if(ind == -1) return false;
    A[ind] = e;
    A[ind].empty = false;
    A[ind].tomb = false;
    return true;
}

// Remove the given key; return true if success, false if failure (given key not present)
bool Dictionary::remove(const char key[])
{
    if(get(key) == nullptr) return false;
    get(key)->empty = false;
    get(key)->tomb = true;
    return true;
}