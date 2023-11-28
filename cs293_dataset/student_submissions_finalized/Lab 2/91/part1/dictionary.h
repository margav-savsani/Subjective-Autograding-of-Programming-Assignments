#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string.h>

// Can change this value for debugging
int DICT_SIZE = 5;

struct Entry {
    char* key;
    int value;

    Entry()
    {
        key = new char[32];
        key[0] = '\0';
    }
    
    Entry(Entry const& e)
    {
      /*  key = new char[32];
        int i = 0;
        for (i = 0; e.key[i] != '\0'; i++)
            key[i] = e.key[i];
        key[i] = '\0';
        */
        key = e.key;
        value = e.value;
    }
/*
    ~Entry()
    {
        delete[] key;
    }
    */
};

class Dictionary {
  private:
    int N; // size of array A
    Entry* A; // Array of dictionary entries

  public:
    // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
    int hashValue(char key[]);

    // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
    int findFreeIndex(char key[]);
    
    // Default constructor
    Dictionary(); 

    // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
    Entry* get(char key[]);

    // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
    bool put(Entry e);

    // Remove the given key; return true if success, false if failure (given key not present)
    bool remove(char key[]);
};

#endif
