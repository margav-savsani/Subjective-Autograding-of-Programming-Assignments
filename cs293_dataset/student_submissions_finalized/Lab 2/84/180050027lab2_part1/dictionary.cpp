#include <iostream>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <stdio.h>
#include "dictionary.h"
using namespace std;
	

struct Entry::Entry{
	map<char key, int value> Entry;  /// Entry -> (key, value)
}


Dictionary::Dictionary(){    /// contructor
	int N = DICT_SIZE;
	struct Entry *A = new char[N]; 
}



/*int hash_fun(char* s, int n) {   //defining a hash function
    const int p = 31, m = 1e9 + 9;
    int hash = 0;
    long power = 1;
    for (int i = 0; i < n; i++) {
        hash = (hash + (int(s[i]) + 1) * power) % m;
        power = (power * p) % m;
    }
    return hash;
}*/

// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
int Dictionary::hashValue(char key[]){
	const int p = 37, m = 1e9 + 9;
	int hash = 0;
	int power = 1;

	for (int i = 0; i < N; i++){	
		hash = (hash + (int(s[i]))*power) % m; 
		power = (power*p) % m;
	}



}


// Find the position where given key can be inserted (after resolving hash collision if any); 
// return value between 0 and N-1 if free location present; return -1 if no free location
int Dictionary::findFreeIndex(char key[]){ 


 }


// Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
struct Dictionary::Entry *get(char key[]){ 



 }


 // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
bool Dictionary::put(struct Entry e){


  }

   // Remove the given key; return true if success, false if failure (given key not present)
bool Dictionary::remove(char key[]){


  }