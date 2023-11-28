#include "dictionary.h"
#include <cmath>

char NULLCHAR = '\0';
// hash functions maps strings to numbers between 0 and 63, so -2 can be used for the tombstone.
// -1 is being used to show that the spot is empty. 
double FIBONACCI = (sqrt(5) - 1)/2;
char* DEFAULT_KEY = "\0";


double hash_code(char key[]) { 
    // a_0 + a_1 x + a_2 x^2 + .... = a_0 + x(), where a_i = character codes (UNICODE) 
    // hash code map -- polynomial accumulation -- x = 33, 37, 39, 41

    double sum = 0;
    int x = 33; // this value worked best for me

    // key[] ends with '\0' and has a max length of 32
    
    int last = strlen(key);

    for (int i = last; i >= 0; i--) {
        
        sum = fmod(key[i]*FIBONACCI + sum*x, 1); 
    }
    
    return sum; 
}

int compression_map(double k) {

    // fibonacci hashing = [m(kA mod 1)], m = DICT_SIZE, A = root5 -1 /2
    // returns a number from 0 to m-1 i.e. 0 to 64. 

    int m = DICT_SIZE;
    //double intermediate1 = k*FIBONACCI;
    //double intermediate2 = intermediate1 - floor(intermediate1);
    int map = floor(m * k);
    return map;
}

int Dictionary::hashValue(char key[]) {
    
    // hash code map + compression map 
    
    double k = hash_code(key);
    int map = compression_map(k);

    return map;
}

int Dictionary::findFreeIndex(char key[]) {
    int index = hashValue(key);
    int result = 0;
    // checking for occupancy 
    
    if (A[index].EMPTY == true) {
        return index;
    }
    else {
        while (true)
        {
            index = (index+1)%DICT_SIZE;
            if (A[index].EMPTY == true) {
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
        A[i].EMPTY = true;
        A[i].TOMBSTONE = false;
    }
    
} 

struct Entry* Dictionary::get(char key[]){

    int index = hashValue(key);
    int result = 0;
    int counter = 0;
    if (A[index].key == key) {
        result = index;
    }
    else {
        while (true)
        {
            
            if (counter >= DICT_SIZE) break;
            if (strcmp(A[index].key, key)==0) {
                break;
            }
            if ((A[index].EMPTY == true)&&(A[index].TOMBSTONE == false)){
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
        A[index].EMPTY = false;
        return true;
    }
}

bool Dictionary::remove(char key[]) {
    Entry* entry = get(key);
    if (entry == NULL) { 
        return false;
    }
    else {
        entry->TOMBSTONE == true;
        entry->key = DEFAULT_KEY;
        return true;
    }
}