#include "dictionary.h"
#include <cmath>

int Dictionary::hashValue(char key[]){
    int x = 33;
    int i = 0; 
    std::string s = key;
    long int sum = 0;
    for ( int i = s.length()-1 ; i>=0 ; i-- ){
       	sum = ((sum*x)+int(key[i]))%879190747;                              //A very large prime number not near power of 2, to prevent overflow
    }
    double n = 3;
    int fib = floor(DICT_SIZE * ( modf( sum * 0.615 , &n)) );               //Fib thing
    return fib;
}

int Dictionary::findFreeIndex(char key[]){                                  //Finds index for insertion
    int hash = hashValue(key);          
    int count = 0;
    while( (A[hash].is_assigned || A[hash].is_tomb) && (!(A[hash].is_assigned && A[hash].is_tomb) ) ){
 	hash = ( hash + 1 ) % DICT_SIZE;
        count++;
        if( count == DICT_SIZE+1 ){
            return -1;
        }
    }
    return hash;
}

struct Entry *Dictionary::get(char key[]){                                  //Returns the Entry, given the key
    int hash = hashValue(key);
    int count = 0;
    for (int i = 0 ; i < DICT_SIZE + 1 ; i++ ){
	if(!A[hash].is_assigned){
		return NULL;
	}
	if(A[hash].is_assigned && strcmp(A[hash].key,key)==0 && !A[hash].is_tomb ){
		return &A[hash];
	}
	else{
		hash = (hash+1 )%DICT_SIZE;
	}

    }
    return NULL;
}

Dictionary::Dictionary(){                                                   //Default Constructor
    N = DICT_SIZE;
    A = new Entry[N];
};

bool Dictionary::put(struct Entry e){                                       //Used to insert element into array
    int hash = findFreeIndex(e.key);
    if(hash==-1){
	    return false;
    }
    A[hash].value = e.value;
    std::string s = e.key;
    for ( int i = 0 ; i < s.length() ; i++ ){
	    A[hash].key[i] = e.key[i];
    }
    A[hash].is_tomb = false;
    A[hash].is_assigned=true;
    return 1;
}

bool Dictionary::remove(char key[]){                                        //Used to remove element from array
    int hash = hashValue(key);
    int count = 0;
    while(1){
        if(strcmp(A[hash].key,key)==0 && !A[hash].is_tomb){
            A[hash].is_tomb=true;
            return true;
        }
        hash = (hash+1)%DICT_SIZE;
        if (count==DICT_SIZE+1){
            return false;
        }
        count++;
    }
}
