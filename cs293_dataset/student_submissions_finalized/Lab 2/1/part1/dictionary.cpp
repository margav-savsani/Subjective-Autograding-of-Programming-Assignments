#include "dictionary.h"
#include "math.h"

const int x = 33;
const double phi = (sqrt(5) - 1)/2;

/*
The hash function is floor(DICT_SIZE * (phi * I_0) mod 1)
Also, I_i = key[i] + x * I_(i+1), where I_1 is the polynomial from key[1]
so (phi * I_0) mod 1 = {key[0] * phi + x * [(phi * I_1) mod 1]} mod 1
Using this I have defined a recursive fucnction to compute (phi * I_0) mod 1.
No overflow happens in this scheme.
*/

double hash_frac(char key[]){ 
    if(key[0] == '\0'){return 0;}
    else{
        double z = key[0] * phi + x * hash_frac(key + 1);
        return z - floor(z);
    }
}

int Dictionary::hashValue(char key[]){
    return floor(DICT_SIZE * hash_frac(key)); //hash value in [0, DICT_SIZE - 1]
}

//A value of INT_MAX denotes an empty entry, INT_MIN denotes an tombstone.
int Dictionary::findFreeIndex(char key[]){
    int hash = hashValue(key);
    int probe = hash;
    while(A[probe].value != INT_MAX && A[probe].value != INT_MIN){
        //move ahead while the entry is not empty and not a tombstone
        probe = (probe + 1) % DICT_SIZE; //circle around at the end.
        if(probe == hash) return -1; //if back to start, array full, return -1
    }
    return probe;
}

bool Dictionary::put(struct Entry e){
    int pos = findFreeIndex(e.key);
    int hash = hashValue(e.key);
    if(pos == -1) return false; //array full
    else{
        int i = 0;
        while(e.key[i] != '\0'){
            A[pos].key[i] = e.key[i]; //copy character wise into the dict
            i++;
        }
        A[pos].value = e.value; //copy value
        return true;
    }
}

bool compare(char a[], char b[]){ //helper func to compare 2 char arrays.
    int i = 0;
    bool same = true;
    while(a[i] != '\0'){
        if(a[i] != b[i]) return false;
        i++;
        if(i == 32) return false;
    }
    if(b[i] != '\0') return false;
    return true;
}

struct Entry* Dictionary::get(char key[]){
    int hash = hashValue(key);
    int probe = hash;
    while(A[probe].value != INT_MAX){ //start at hash index
    //move ahead until available entry found
        //if the entry is not a tombstone, compare keys
        if(A[probe].value != INT_MIN && compare(key, A[probe].key)){
            return A + probe; //if match return the entry's address
        }
        probe = (probe + 1) % DICT_SIZE; //move circularly
        if(probe == hash) return NULL; //if back to start, no matching key found.
    }
    return NULL;
}

bool Dictionary::remove(char key[]){
    struct Entry *entry = get(key);
    if(entry == NULL) return false; //no matching key
    else{
        entry->value = INT_MIN; //set it to be a tombstone (also, available since value != INT_MAX)
        return true;
    }
}



