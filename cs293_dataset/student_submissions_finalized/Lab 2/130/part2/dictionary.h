#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string.h>
#include "planner.h"

// Can change this value for debugging
#define DICT_SIZE 64

struct Entry {
    // define suitable fields here
    char *key;
    struct Station* value;
    bool empty;
    bool tomb;

    Entry() : key(new char[32]), empty(true), tomb(false) {}

    Entry(const char *str, struct Station* val) : key(new char[32]), value(val)
    {
        strcpy(key, str);
    }

    Entry(const Entry &other) : value(other.value), key(new char[32]), empty(empty), tomb(tomb)
    {
        strcpy(key, other.key);
    }

    Entry &operator=(const Entry &assign)
    {
        if (&assign == this)
            return *this;
        value = assign.value;
        empty = assign.empty;
        tomb = assign.tomb;
        strcpy(key, assign.key);
        return *this;
    }

    ~Entry()
    {
        delete[] key;
    }
};


class Dictionary {
private:
    int N;           // size of array A
    struct Entry *A; // Array of dictionary entries

public:
    // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
    int hashValue(const char key[]) const;

    // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
    int findFreeIndex(const char key[]) const;

    // Default constructor
    Dictionary();

    // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
    struct Entry *get(const char key[]);

    // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
    bool put(struct Entry e);

    // Remove the given key; return true if success, false if failure (given key not present)
    bool remove(const char key[]);
};

#endif
