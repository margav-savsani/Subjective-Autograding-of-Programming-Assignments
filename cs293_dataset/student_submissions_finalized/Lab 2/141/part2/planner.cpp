#include<iostream>
#include<string.h>
#include<cmath>
#include "planner.h"
// Can change this value for debugging
int DICT_SIZE = 64;


class Dictionary {
 private:
  int N; // size of array A
  struct Journey* journeys;

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char station1[]);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Journey *get(struct Query);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Journey j);

};

char NULLCHAR = '\0';
double FIBONACCI = (sqrt(5) - 1)/2;
// hash functions maps strings to numbers between 0 and 63, so -2 can be used for the tombstone.
// -1 is being used to show that the spot is empty. 


char* DEFAULT_KEY = "\0"; // important fix


double hash_code(char key[]) { 
    // a_0 + a_1 x + a_2 x^2 + .... = a_0 + x(), where a_i = character codes (UNICODE) 
    // hash code map -- polynomial accumulation -- x = 33, 37, 39, 41

    double sum = 0;
    int x = 33; // this value worked best for me

    // key[] ends with '\0' and has a max length of 32
    
    int last = strlen(key);

    for (int i = last-1 ; i >= 0; i--) {
        
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
    //std::cout << A[index].key << std::endl;
    if (journeys[index].EMPTY == true) {
        return index;
    }
    else {
        while (true)
        {
            //std::cout << index << std::endl;
            index = (index+1)%DICT_SIZE;
            if (journeys[index].EMPTY == true) {
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
    
    journeys = new Journey[DICT_SIZE];
    N = DICT_SIZE;
    for (int i = 0; i < DICT_SIZE; i++){
        strcpy(journeys[i].station1, DEFAULT_KEY);
        strcpy(journeys[i].station2 , DEFAULT_KEY);
        journeys[i].EMPTY =true;
        journeys[i].TOMBSTONE = false;
    }
    
} 

bool equal(char * str1, char* str2) {
    
    for (int i = 0; (str1[i]!='\0') || (str2[i]!='\0'); i++) {
        if (str1[i] != str2[i]) return false;
    }
    return true;
}

// modified get to return an array of journeys depending on Query q. 
struct Journey* Dictionary::get(Query q){
    //std::cout << "inside get" << std::endl;
    int index = hashValue(q.station.station);
    
    Journey* result = new Journey[DICT_SIZE+1]; // atmost 64 journeys stored in dictionary
    int counter = 0; // counts number of elements added till now. 

    // run a loop over all possible linear probes. i.e. till we encounter an EMPTY but not tombstone element, or we circle back. 

    
    
    while (true)
    {
        if (counter >= DICT_SIZE) break;
        //std::cout << "Control OUTSIDE passed" << " current index : "<< index << std::endl;
        //std::cout << "Equal strings : "  << equal(journeys[index].station1, q.station.station) <<  " " << journeys[index].station1 << " " << q.station.station << std::endl;
        if (equal(journeys[index].station1, q.station.station) && (journeys[index].start > q.start)) {
          //std::cout << "Control inside time passed" << std::endl;
          result[counter] = journeys[index];
          counter++;
          //std::cout << "equal" << std::endl;
          //std::cout << result << std::endl;
        }
        
        if ((journeys[index].EMPTY == true) && (journeys[index].TOMBSTONE == false)) {
            
            break;
        }
        index = (index+1)%DICT_SIZE;
        if (index == hashValue(q.station.station)) {
            // avoids looping back.
            break;
        }
    }
    
    // last element will have time = -1 : signalling last journey in the output 
    result[counter].start = -1;
    //std::cout << "outside get" << std::endl;
    return result;
}

bool Dictionary::put(struct Journey e) {
    char* key = e.station1;
    int index = findFreeIndex(key);

    if (index == -1) return false;

    else {
        strcpy(journeys[index].station1, key);
        strcpy(journeys[index].station2, e.station2);
        journeys[index].start = e.start;
        journeys[index].end = e.end;
        journeys[index].EMPTY = false;
        journeys[index].index = index;
        return true;
    }
}


