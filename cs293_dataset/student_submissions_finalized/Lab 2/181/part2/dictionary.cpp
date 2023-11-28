#include <iostream>
#include "dictionary.h"
#include <math.h>
#include <string.h>
#include <cstring>
using namespace std;

Dictionary::Dictionary() // Default Constructor for Dictsize and array its going to save it in
{
    N = DICT_SIZE;    // Dictionary size
    A = new Entry[N]; // array in which entries are going to be saved
}

int Dictionary::hashValue(char key[]) // return as hash value
                                      //(random value for each specific key using some mathamatical equations)
{
    int x = 33;                       // variable for linear accumulation
    double A = (pow(5, 0.5) - 1) / 2; // fibonacci const given by knuth
    double j = 0;
    int i = strlen(key);
    for (int k = i; k > 0; k--)
    {
        j = fmod(fmod(A * key[k - 1], 1) + fmod(j * x, 1), 1); // linear accumulation without overflowing
    }

    return 64 * j; // returning the random value inside the array
}
int Dictionary::findFreeIndex(char key[]) // gives the index in which array entry is either none or a tombstone
{
    const int j = hashValue(key); // constant random value generated for the key using hash function to check if it comes back to it again in for loop
    int i = j;                    // hashvalue

    for (int k = 0; k < N; k++) // checking the whole array
    {
        if (A[i].isEmpty || A[i].tombstone) // returning the index if it is either empty or having a tombstone
        {
            return i; // index value
        }
        i = (i + 1) % N; //%N as it can start from 0 if it reaches the end
    }
    return -1; // if there is no index empty
}
struct Entry *Dictionary::get(char key[]) // function to get back the pointer of the entry made by key
{
    const int j = hashValue(key); // random value generated using hashfunction
    int i = j;                    // hashvalue
    for (int k = 0; k < N; k++)   // checking the whole array if its available anywhere
    {
        if (strcmp(A[i].key, key) == 0 && !A[i].tombstone) // if the key matches and its not a tombstone it returns its index
        {
            return (A + i); // returning the pointer at which the given key is present
        }
        if (A[i].isEmpty == true) // if it reaches an empty position there
                                  // cant be any with this hash value after this index so returning null
        {
            return NULL;
        }
        i = (i + 1) % N; // for circulating throughout the array if it wont stop before reaching the end
    }
    return NULL;
}
bool Dictionary::put(struct Entry e)
{
    if (findFreeIndex(e.key) >= 0) // if there is no free index it returns -1
    {
        A[findFreeIndex(e.key)] = e;
        strcpy(e.key, A[findFreeIndex(e.key)].key); // exactly copying the string
        A[findFreeIndex(e.key)].value = e.value;    // taking the value in entry
        A[findFreeIndex(e.key)].isEmpty = false;    // as it is no more empty
        A[findFreeIndex(e.key)].tombstone = false;  // if it was a tombstone it will be removed
        return true;
    }
    else
        return false;
}

bool Dictionary::remove(char key[]) // to remove the entry of the corresponding key in the array
{
    if (get(key) == NULL) // returning false if we get a null value for checking the key position in the array
    {
        return false;
    }
    else
    {
        get(key)->tombstone = true; // changing the entry to tombstone if there is a corresponding entry in the array
        return true;                // returning true as we are removing and adding a tombstone to the position it is removed from
    }
}
