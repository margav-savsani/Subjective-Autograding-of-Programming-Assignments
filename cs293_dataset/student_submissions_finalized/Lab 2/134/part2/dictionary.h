#include<iostream>
#include<string.h>


#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
int DICT_SIZE = 64;
struct journey{
  char init_station[32];
  float init_time;
  char dest_station[32];
  float dest_time;

void operator=(journey j){
  strcpy(init_station, j.init_station);
  init_time = j.init_time;
  strcpy(dest_station, j.dest_station);
  dest_time = j.dest_time;
}
  /*journey(char is[]=, float it=0, char ds[]=0, float dt=0){
    strcpy(init_station, is);
    init_time = it;
    strcpy(dest_station, ds);
    dest_time = dt;
  }*/
};



struct Entry {
  // define suitable fields here
  char *key;  // key or name
  bool null;  // this boolean solely represent if the entry is empty(NULL)  
  bool tombstone; // this boolean represents if this position of entry is tombstone
  journey *value;

  void operator=(Entry e){
    strcpy(key, e.key);
    null = e.null;
    tombstone = e.tombstone;
    value = e.value;
  }
  
  Entry(){
    tombstone = false; // default
    key = new char[32]; // initialising as per question statement
    null = true; // its taken null by default
    value = new journey;
  }
};

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[]);
  bool get(char key[], float time, Entry *elelist, int *len);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);
};


#endif
