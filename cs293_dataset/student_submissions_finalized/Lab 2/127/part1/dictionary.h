#include<iostream>
#include<string>
#include<vector>


#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
const int DICT_SIZE = 64;

struct Entry {
  char key[32];
  std::string value;
};

class Dictionary {
 private:
  int N=DICT_SIZE; // size of array A
  struct Entry A[DICT_SIZE]; // Array of dictionary entries
  int hash_prime=41; //prime for hashing

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[]);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);
};


struct Entry_float {
  std::string key;
  std::vector<float> value;
};

class Dictionary_float {
 private:
  int N=DICT_SIZE; // size of array A
  struct Entry_float A[DICT_SIZE]; // Array of dictionary entries
  int hash_prime=41; //prime for hashing

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(std::string key);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(std::string key);
  
  // Default constructor
  Dictionary_float(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  std::vector<float> get(std::string key);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(std::string key, float values);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(std::string key, float value);
};

struct Entry_string {
  std::string key;
  std::vector<std::string> value;
};

class Dictionary_string {
 private:
  int N=DICT_SIZE; // size of array A
  struct Entry_string A[DICT_SIZE]; // Array of dictionary entries
  int hash_prime=41; //prime for hashing

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(std::string key);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(std::string key);
  
  // Default constructor
  Dictionary_string(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  std::vector<std::string> get(std::string key);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(std::string key, std::string values);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(std::string key, std::string value);
};

#endif
