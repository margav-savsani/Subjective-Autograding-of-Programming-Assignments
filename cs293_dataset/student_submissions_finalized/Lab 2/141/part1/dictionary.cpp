#include "dictionary.h"
#include <cmath>

char NULLCHAR = '\0';
int OVERFLOW = 2000;
// hash functions maps strings to numbers between 0 and 63, so -2 can be used for the tombstone.
// -1 is being used to show that the spot is empty. 

int TOMBSTONE = -2; 
int EMPTY = -1;
char* DEFAULT_KEY = NULL;

int last_index (char key[]) {

    int result = 0;
    // returns the index of string containing the null character
    for (int idx = 0; idx <= 32; idx++) {
        if (key[idx] == NULLCHAR) {
            result = idx;
            break;
        }
    }
    return result;
}

int hash_code(char key[]) { 
    // a_0 + a_1 x + a_2 x^2 + .... = a_0 + x(), where a_i = character codes (UNICODE) 
    // hash code map -- polynomial accumulation -- x = 33, 37, 39, 41

    int sum = 0;
    int x = 33;

    // key[] ends with '\0' and has a max length of 32
    
    int last = last_index(key);

    for (int i = last - 1; i > 0; i--) {
        int a = (int)key[i];
        sum = a + sum*x; 
        sum = sum % OVERFLOW; // to keep overflow in check. 
    }
    
    return sum; 
}

int compression_map(int k) {

    // fibonacci hashing = [m(kA mod 1)], m = DICT_SIZE, A = root5 -1 /2
    // returns a number from 0 to m-1 i.e. 0 to 64. 

    double FIBONACCI = (sqrt(5) - 1)/2;
    int m = DICT_SIZE;
    double intermediate1 = k*FIBONACCI;
    double intermediate2 = intermediate1 - floor(intermediate1);
    int map = floor(m * intermediate2);

    return map;
}

int Dictionary::hashValue(char key[]) {
    
    // hash code map + compression map 
    
    int k = hash_code(key);
    int map = compression_map(k);

    return map;
}

int Dictionary::findFreeIndex(char key[]) {
    int index = hashValue(key);
    int result = 0;
    // checking for occupancy 
    
    if (A[index].value == EMPTY) {
        return index;
    }
    else {
        while (true)
        {
            index = (index+1)%DICT_SIZE;
            if (A[index].value == EMPTY) {
                return index;
            }
            if (index == hashValue(key)) {
                return -1;
            }
        }
    }
   
}

Dictionary::Dictionary() {

    // Entry has a key and a corresponding value. 
    // key = string, value = integer. 
    // initialises all slots to empty, creates a hash table of size DICT_SIZE. 
    // the key attribute of entry is used for putting it in the dictionary/hash table
    
    A = new Entry[DICT_SIZE];
    N = DICT_SIZE;
    for (int i = 0; i < DICT_SIZE; i++){
        A[i].key = DEFAULT_KEY;
        A[i].value = EMPTY;
    }
    
} 

struct Entry* Dictionary::get(char key[]){

    int index = hashValue(key);
    int result = 0;
    if (A[index].key == key) {
        result = index;
    }
    else {
        while (true)
        {
            
            if (A[index].key == key) {
                break;
            }
            if (A[index].value == EMPTY) {
                return NULL;
            }
            
            index = (index+1)%DICT_SIZE;
            if (index == hashValue(key)) {
                return NULL;
            }
        }
        result = index;
    }
    return &(A[result]);
}

bool Dictionary::put(struct Entry e) {
    char* key = e.key;
    int index = findFreeIndex(key);

    if (index == -1) return false;

    else {
        A[index].key = key;
        A[index].value = e.value;

        return true;
    }
}

bool Dictionary::remove(char key[]) {
    Entry* entry = get(key);
    if (entry == NULL) { 
        return false;
    }
    else {
        entry->value = TOMBSTONE;
        entry->key = DEFAULT_KEY;
        return true;
    }
}