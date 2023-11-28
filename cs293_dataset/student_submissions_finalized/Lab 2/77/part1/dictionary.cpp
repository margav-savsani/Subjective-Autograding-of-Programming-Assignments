#include <iostream>
#include "dictionary.h"
#include <cmath>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const double FIBB = (sqrt(5) - 1) / 2; // Fibbonacci constant
const int X = 37;                      // I have chosen value of X as 37

// TOMBSTONE : I defined int TOMBSTONE in the Entry struct.
// WORKING :  TOMBSTONE = 0 - while defining the constructor
// TOMBSTONE =-1 - for tombstone
// TOMBSTONE = 1 - if position is occupied by an element.

int Dictionary::hashValue(char key[])
{
    double sum = 0;
    int i = strlen(key);//To find lenth of the key.
    // Polynomial accumulation
    for (int j = i; j >= 0; j--)// I used property of modulo(fmod here) expansion over the sum.
    {
        sum = fmod((fmod((FIBB * key[j]), 1) + fmod((sum * X), 1)), 1); // as modulo(%) function is not defined for floating point numbers so I have used fmod.
    }
    double product = DICT_SIZE * sum;
    int hash_val = floor(product); // floor function returns integer
    return (hash_val);             // Returns hash value
}
int Dictionary::findFreeIndex(char key[])
{
    int k = hashValue(key);
    for (int i = 0; i < DICT_SIZE; i++)
    {
        if (A[k].TOMBSTONE == 0 || A[k].TOMBSTONE == -1)// checks if any place/position is empty or not.
        {
            return k;
        }
        k = (k + 1) % DICT_SIZE;// To move in circular way, modulo is used.
    }

    return -1;// If there is no free index it returns -1.
}
Dictionary::Dictionary()
{ 
    N = 0;
    A = new Entry[DICT_SIZE];// Creates the array of struct Entry of size DICT_SIZE.
    for (int i = 0; i < DICT_SIZE; i++)
    {
        A[i].TOMBSTONE = 0;// Initialised TOMBSTONE to zero for every position in the array.
    }
}
struct Entry *Dictionary::get(char key[])
{
    int val = hashValue(key);
    for (int i = 0; i < DICT_SIZE; i++)
    {
        if ((strcmp(A[val].key, key) == 0) && A[val].TOMBSTONE == 1)//Checks whether both keys are equal or not and is it a valid occupied element or not.
            return &A[val];
        val = (val + 1) % DICT_SIZE;
    }
    return NULL;// Returns NULL if element is not there.
}
bool Dictionary::put(struct Entry e)
{
    int val = findFreeIndex(e.key);
    A[val] = e;
    A[val].value = e.value;
    strcpy(e.key, A[val].key);// Copies value of e.key to A[val].key
    if (val == -1)
    {
        return false;
    }
    else
    {
        A[val] = e;
        A[val].TOMBSTONE = 1;// Changes TOMBSTONE from 0 or -1 to 1;
        return true;
    }
}
bool Dictionary::remove(char key[])
{
    if (get(key) == NULL)//If no such element/place exists it
    {
        return false;
    }
    get(key)->TOMBSTONE = -1;// Changes the TOMBSTONE value from 1 to -1.
    return true;
}