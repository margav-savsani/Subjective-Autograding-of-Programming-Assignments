#include<iostream>
#include<string.h>

#ifndef DICTIONARY_H
#define DICTIONARY_H

using namespace std;

// Can change this value for debugging
int DICT_SIZE = 64;
constexpr int NUM_JOURNEYS = 64; //the maximum number of journeys there can be for a station

template <typename T>
class vector{
	//wrapper class for a fixed length array
private:
	T arr[NUM_JOURNEYS];
	int sz = 0; //stores the number of elements stored in the array
public:
	void push_back(T j){
		if(sz==NUM_JOURNEYS) //throw an exception if the vector is full
			throw "array full exception";
		arr[sz] = j;
		sz++;
	}
	T& at(int i){
		if(i>=sz)
			throw "invalid index";
		return arr[i];
	}
	T* begin(){
		//Used by the range based for loop
		return arr;
	}
	T* end(){
		//Used by the range based for loop
		return arr+sz;
	}
	int size(){
		return sz;
	}
};

struct Journey {
	// define suitable fields here
	char src_station[32];
	char dest_station[32];
	float start_time;
	float end_time;
	Journey (){}
	Journey(const Journey& j){
		strcpy(src_station, j.src_station);
		strcpy(dest_station, j.dest_station);
		start_time = j.start_time;
		end_time = j.end_time;
	}
	Journey& operator = (const Journey& j){ //assignment operator overload
		strcpy(src_station, j.src_station);
		strcpy(dest_station, j.dest_station);
		start_time = j.start_time;
		end_time = j.end_time;
    return *this;
	}
};

struct Entry {
  // define suitable fields here
    char key[32];  
    vector<Journey> j; //stores the journeys with the same source stations
    int value; //useless
    Entry(){
        key[0]='\0';
    }
    Entry(Journey k){
        j.push_back(k);
        strcpy(key, k.src_station);
    }
    Entry& operator = (Entry& a){     //assignment operator definition
        strcpy(key, a.key);
        j = a.j;
        return *this;
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

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]);
};

#endif
