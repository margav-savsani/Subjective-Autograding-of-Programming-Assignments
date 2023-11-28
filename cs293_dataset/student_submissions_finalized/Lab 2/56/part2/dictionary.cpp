#include "dictionary.h"
#include <cmath>
#define GR (sqrt(5)-1)/2
#include <iostream>

float frac_part(float x){   //calculates the fractional part (num -gif(num))
    return (x - int(x));
}

int hash_code_map(char* key){    //converts the string to int(hash code)
    if(int(*key) == 0){
        return 0;
    }                                           //choosing x as 37 in the polynomial hash code map
    return (int(*key) + 37*(hash_code_map(key+1)))%131071;    //mod with a prime to prevent overflow - recursive hash code map
}

int Dictionary::hashValue(char key[]){     //calculate the hash value using the hash code and compression map
    return int(64*frac_part(GR*hash_code_map(key)));  //A = GR, m = 64
}

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Station[N];     //allocate space for N Entries
    for(int i = 0; i < N; i++){
        A[i].id='e';     //'e' corresponds to empty entry
        strcpy(A[i].key, "");
    } 
}

int Dictionary::findFreeIndex(char key[]){   //finds the first free index
    int ind = hashValue(key);
    for(int i = ind; i < N; i = (i+1)%N){     //calculate the hash of the key and linearly probe
        if(A[i].id != 'f'){                     //if a non-filled entry is found, return that index
                                                //'f' corresponds to a filled entry
            return i;
        }
    }
    return -1;
}

struct Station* Dictionary::get(char key[]){    //gets the Station by key
    int ind = hashValue(key);
    for(int i = ind; i < N && A[i].id != 'e'; i = (i+1)%N){   //check until an empty entry is found 
        if(strcmp(A[i].key, key) == 0){     //key found
            return (A+i);
        }
    }
    return NULL;   //key not found
}

bool Dictionary::put(struct Station e){  //inserting in the dictionary-not considering the case when two entries having same key and value are being inserted
    int ind = hashValue(e.key);
    int free = findFreeIndex(e.key);
    if(free == -1){             //no free index
        return false;
    }
    A[free] = e;     
    A[free].id = 'f';    //'f' states that the entry is filled
    return true;
 }

bool Dictionary::remove(char key[]){    //removes an entry and inserts a tombstone
    int ind = hashValue(key);
    for(int i = ind; i < N && A[i].id != 'e'; i = (i+1)%N){        //keep searching till empty element is found
    
        if(strcmp(A[i].key, key) == 0){   //once found, clear the entry
            A[i].id = 't';    //'t' is the id of a tombstone entry
            strcpy(A[i].key, "");
            return true;
        }
        
    }
    return false;
}


