 #include "dictionary.h"
#include <string.h>
#include <cmath>
int X = 33; //value of x used in polynomial to calculate the integer in hash code map.
double fib = (sqrt(5)-1)/2; //stores Fibonacci constant used in compression

double frac(double x){
    //return fractional part of a number
    return x - floor(x);
}

Dictionary::Dictionary(){
    //default Constructor
    N = DICT_SIZE;
    A = new Entry[N];
}

int Dictionary::hashValue(char key[]){
    int string_length = 0;
    while(key[string_length]!='\0'){
        string_length++;
    }
    int coeffecients[string_length];
    for(int i = 0; i<string_length; i++){
        //calculate the coeffecients from ascii values
        if(key[i]>=97) coeffecients[i] = key[i]-97;
        else coeffecients[i] = key[i]-65;
    }
    int uncompressedValue(0);
    for(int i = string_length - 1; i>=0; i--){
        //calculation of polynomial using Horner's formula:
        uncompressedValue = uncompressedValue*X + coeffecients[i];

        //taking modulus with 10^9+7(a prime number) so that the value doesn't overflow:
        uncompressedValue = uncompressedValue%(1000000007); 
    }
    int hashVal = floor(DICT_SIZE*frac(uncompressedValue*fib)); //compression
    return hashVal;
}

int Dictionary::findFreeIndex(char key[]){
    int hashVal = hashValue(key);
    int initialHashValue = hashVal;
    while(!A[hashVal].null_struct){
        //keep moving forward till you find a free index
        hashVal = (hashVal+1)%DICT_SIZE;
        if(hashVal == initialHashValue){
            //return -1 if you reach the starting position again
            return -1;
        }
    }
    return hashVal;
}
struct Entry * Dictionary::get(char key[]){
    int hashVal = hashValue(key);
    int initialHashValue = hashVal;
    while(!A[hashVal].null_struct){
        if(strcmp(A[hashVal].key,key)==0&&A[hashVal].tombstone==false){
            //return the struct if key is matched and the element isn't a tombstone
            return &A[hashVal];
        }
        hashVal = (hashVal+1)%DICT_SIZE;
        if(hashVal == initialHashValue){
            //return NULL if given entry not found in whole array
            return NULL;
        }
    }
    return NULL; //return NULL if free value encountered and no key matched
}
bool Dictionary::put(struct Entry e){
    int index = findFreeIndex(e.key);
    if(index == -1) return false; //return false when all array is occupied by elements or tombstones
    A[index] = e;
    A[index].null_struct = false;
    return true;
}
bool Dictionary::remove(char key[]){
    Entry* entry = get(key);
    if(entry==NULL) return false; //cannot delete if elment not present

    //Make the removed element a tombstone
    entry->null_struct = false;
    entry->tombstone = true;

    return true;
}