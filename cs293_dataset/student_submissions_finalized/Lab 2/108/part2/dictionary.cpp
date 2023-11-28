#include "dictionary.h"

// Initializes the dictionary to the 
// appropriate size
Dictionary::Dictionary() {
    N = DICT_SIZE;
    A = new Entry[N];
}

// Calculates the hash value for a given key
int Dictionary::hashValue(std::string key) {
    const int x { 33 };
    const int M { 1000000007 };  // Used to prevent overflow

    // First convert char[] into and integer by polynomial accumulation
    long long int_key {};
    int index {};
    while (key[index]) {
        int_key = static_cast<long long>(key[index]) + x*int_key;
        int_key %= M;
        index++;
    }
    // int_key = ((x^n-1)key[0] + (x^n-2)key[1] ... (x^0)key[key_length - 1])%M
    // where key[i] denotes the ascii value of that character

    // Use Fibonacci hashing to calculate final value
    const double K { 0.6180339887498949 };  // (sqrt(5)-1)/2
    double h = int_key*K;
    return N*(h - static_cast<int>(h));
}

// Returns the location at which an entry corresponding to 
// key can be inserted. Return -1 if no such location 
// exists
int Dictionary::findFreeIndex(std::string key) {
    int hash { hashValue(key) };
    int loc { hash }; // Holds the location checked
    while (A[loc].key != "__empty__" && A[loc].key != "xx__tombstone__xx") { // Check for no element or tombstone
        loc++;
        if (loc == N) loc -= N; // Circle around the array
        if (loc == hash) return -1; // If the entire array is checked then return -1
    }
    return loc;
}

// Returns a pointer to the entry corresponding
// to a particular key
struct Entry* Dictionary::get(std::string key) {
    int hash { hashValue(key) };
    int loc {hash};  // Holds the location to be checked
    while (A[loc].key != "__empty__") {
        if (key == A[loc].key && A[loc].key != "xx__tombstone__xx") return &A[loc];  // Match keys
        loc++;
        if (loc == N) loc -= N; // Circle around the array
        if (loc == hash) break; // If the entire array is checked then stop
    }
    return NULL;  // return NULL if no entry was found
}

// Inserts an entry e into the dictionary
// or updates the value for a pre-existing key
// 
// Returns the status of insertion, true if 
// element was inserted or update and false if 
// not(no space left in the array)
bool Dictionary::put(struct Entry e) {
    Entry* key_present = get(e.key);
    if (key_present) {  // Check if the key already exists or not
        key_present->value = e.value;
        return true;
    }

    int empty { findFreeIndex(e.key) };  // Find an empty place to insert the new element
    if (empty != -1) {
        A[empty] = e;
        return true;
    } else return false;
}

// Removes an element from the dictionary
//
// Returns the status of deletion
//
// Doesn't actually remove the element 
// instead marks it as a tombstone by 
// setting its' value appropriately(-1)
bool Dictionary::remove(std::string key) {
    Entry* element { get(key) };
    if (element) {
        element->key = "xx__tombstone__xx";
        return true;
    }
    else return false;
}