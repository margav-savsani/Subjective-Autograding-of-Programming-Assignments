#include <iostream>
#include <string>
#include <string.h>


#ifndef DICTIONARY_H
#define DICTIONARY_H

struct Journey {
    std::string start_station;
    double departure_time {};
    std::string end_station;
    double arrival_time {};
};

// Can change this value for debugging
int DICT_SIZE = 64;
const int VALUE_SIZE = 100;

struct Entry { 
  // define suitable fields here
  std::string key;
  Journey* value;  // Will contain all the journeys from the station "key"
  int size { VALUE_SIZE };  // size of the array
  int num_ele {};  // number of elements in the array

  // Allocate some space at the start
  Entry (std::string k = "__empty__") : key { k } {
    value = new Journey[VALUE_SIZE];
  }

  // Add an journey to the entry
  void add(Journey j) {
    if (num_ele == size) grow();  // Grow the array if needed
    value[num_ele++] = j;
  }

  // Grows the array if there is no space left
  void grow() {
    Journey* new_array = new Journey[2*size];
    for (int i=0; i<size; i++) new_array[i] = value[i];
    delete[] value;
    value = new_array;
    size *= 2;
  }
};

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(std::string key);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(std::string key);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(std::string key);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(std::string key);
};

#endif
