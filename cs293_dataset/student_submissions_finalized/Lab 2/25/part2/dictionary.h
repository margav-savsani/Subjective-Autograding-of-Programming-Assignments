#include <iostream>
#include <string.h>
using namespace std;

#ifndef DICTIONARY_H
#define DICTIONARY_H

// Can change this value for debugging
int DICT_SIZE = 64;

struct Journey {
    int start;
    int end;
    char dest[32];
    Journey(){};
    Journey(char st[], int start, int end) : start(start), end(end) {
        strcpy(dest, st);
    }
};

struct Entry {
    // define suitable fields here
    char station[32];
    Journey jour;
};

struct Query {
    char src[32];
    char dest[32];
    int start;
    Query(int start, char s[], char d[]): start(start) {
        strcpy(src, s);
        strcpy(dest, d);
    }
};

class Dictionary {
    // define suitable fields here
private:
    int N;           // size of array A
    struct Entry *A; // Array of dictionary entries

public:
    // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
    int hashValue(char key[]);

    // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
    int findFreeIndex(char key[]);

    // Default constructor
    Dictionary();

    // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
    void get(char key[], int start);

    // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
    bool put(struct Entry e);

    void plan(Query* q);

};

#endif
