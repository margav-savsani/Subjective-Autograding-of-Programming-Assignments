#include "dictionary.h"
#include <cmath>
using namespace std;

const int PRIME = 37;   //const prime for polynomial hashing
const int MOD = 10000007;   //const for polynomial hashing
const double FIB = (sqrt(5) - 1)/2; //A value for fibonacci hashing

int Dictionary::hashValue(char key[]){
    long int hash_val = 0;  //initializing the calculated hash value to zero
    long int power_prime = 1;   //to prevent the overflow we will do modulo along with each addition and multiplication step

    int i=0;
    while (key[i]!='\0'){   //updating hash value till the end of string is reached i.e. null char
        hash_val = (hash_val + key[i]*power_prime)%MOD; //rolling hash logic
        power_prime = (power_prime*PRIME)%MOD;  //updating it for next run but also taking modulo to prevent overflow
        i++;    //updating the index
    }
    hash_val = floor(N*((FIB*hash_val) - floor(FIB*hash_val))); //doing fibonacci hash
    return hash_val;    //returning the hash value
}

int Dictionary::findFreeIndex(char key[]){
    int hash_val = hashValue(key);  //getting the hash value of the key
    int current_index = hash_val;   //creating an variable to store the possible free index

    while (A[current_index].tag == 1){  //tag defines whether the place is deleted/empty or full. see dictionary.h
        current_index += 1; //until we reach an empty or deleted index increasing the index
        if (current_index == hash_val){ //if somehow index comes bach to the original hash value then no space left and so return -1
            return -1;
        }
    }

    return current_index;

}

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new struct Entry[N];
}

struct Entry * Dictionary::get(char key[]){
    int hash_val = hashValue(key);  //doing same thing as done in findFreeIndex function
    int current_index = hash_val;

    while (A[current_index].tag != 0 && (strcmp(A[current_index].key , key)||A[current_index].tag == -1)){//traversing the array untill we reach empty location
    //or if we reach location where key matches

        current_index++;
        if (current_index==hash_val){ //same as in findFreeIndex
            return NULL;
        }
    }
    
    if (!strcmp(A[current_index].key , key) && A[current_index].tag == 1){ //if we found the key then returning the address of entry
        return &A[current_index];
    }
    else{
        return NULL;
    }

}

bool Dictionary::put(struct Entry e){
    int index=findFreeIndex(e.key); //finding the index to store the entry
    if (index==-1){
        return false; //if no index available then return false
    }
    A[index] = e;   //updating the index if available
    A[index].tag = 1;   //and changing the tag to 1 => full
    return true;
}

bool Dictionary::remove(char key[]){
    struct Entry *e = get(key); //searching the key using get function
    if (e==NULL){   //if no entry available then returing false
        return false;
    }
    e->key[0] = '\0'; //and updating variable in Entry to empty values
    e->value = 0;
    e->tag = -1;    //tag is changed to deleted => -1
    return true;
}