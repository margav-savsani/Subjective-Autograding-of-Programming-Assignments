#include <iostream>
#include "dictionary.h"
#include <cmath>
#include <climits>
#include <string.h>
using namespace std;

//Constructor 
Dictionary::Dictionary(){
	N = DICT_SIZE;
	A = new Entry[N];
	
	for(int i=0; i<N; i++)
	{
		struct Entry *e = new Entry;
		A[i] = *e;
	}
}		

//TIME COMPlexity = O(size of key)
int Dictionary::hashValue(char key[]){
	//First convert key(string) to key(int) using ASCII values of characters and horners rule.
        //Implementation of hash code map using x=33
        unsigned int keyInt, keySize = 0, x = 39, m = INT_MAX;

        //Size of key which is a string
        while(key[keySize] != '\0'){
                keySize++;
        }

        keyInt = (int)key[keySize-1];

        for(int i=keySize-2; i>=0; i--)
        {
                keyInt = ((keyInt*x)%m + (int)key[i])%m;
        }

        //Implementation of hash compression map

        double A = (sqrt(5) - 1)/2;

        // This is fibonacci hashing

        double hashKey;
        hashKey = keyInt*A;
        hashKey = DICT_SIZE*(hashKey - int(hashKey));

        return (int)hashKey;

}

int Dictionary::findFreeIndex(char key[]){
	
	//Compute slot value where data can be entered
	int slot = hashValue(key), tries = 0;
	
	//until we find a slot which is null and number of tries is less than DICT_SIZE, we keep probing. Since hash table is of size DICT_SIZE, if tries is greater than DICT_SIZE, then it means that we have circularly moved around in the array, so that means no empty slot. 
	while(tries<DICT_SIZE)
	{	
		if(A[slot].value == INT_MIN || A[slot].checkForTombStone()) break;
		
		
		
		// Checks if two keys are same.	
		bool areTwoKeySame = true;
		char *key1 = A[slot].key, *key2 = key;	
		
		int key1Size = 0, key2Size = 0;
	
		//Calculating key1 size
		while(key1[key1Size] != '\0'){
			key1Size++;
		}
	
		//calculating key2 size
		while(key2[key2Size] != '\0'){
			key2Size++;
		}
	
		// If different size, then can't be same keys
		if(key1Size != key2Size) areTwoKeySame = false;
		
		//Same size
		for(int i = 0; i < key1Size ; i++)
		{
			//If any key different, then false
			if(key1[i] != key2[i]) {
				areTwoKeySame = false;
				break;
			}
		}

		//If same key is again tried to enter dictionary, then give same slot to override the given entry, else check for next slot
		if(areTwoKeySame) return slot;
		else {
			slot = (slot+1)%DICT_SIZE;
			tries++;
		}	
	}
	
	if(tries<DICT_SIZE) return slot;
	else return -1;
}


bool Dictionary::put(struct Entry e){

	//Calculating free slot in hash table
	int slot, tries = 0;
	char key[32];
	strcpy(key,e.key);
	slot = findFreeIndex(key);

	if(slot != -1) {
		A[slot] = e;
		return true;
	}	
	else return false;
}


struct Entry* Dictionary::get(char key[]){
	
	int slot = hashValue(key), tries = 0;
	
	while(A[slot].value != INT_MIN && tries<DICT_SIZE)
	{
		tries++;
		//if it is a tombstone, then skip it
		if(A[slot].checkForTombStone())
		{
			slot = (slot+1)%DICT_SIZE;
			continue;
		}	
		
		// Checks if two keys are same.	
		bool areTwoKeySame = false;
		char *key1 = A[slot].key, *key2 = key;	
		if(strcmp(key1, key2) == 0) areTwoKeySame = true;
		
		if(areTwoKeySame) return &A[slot];
		
		slot = (slot+1)%DICT_SIZE;
	}
	
	return NULL;
}


bool Dictionary::remove(char key[]){

	int slot = hashValue(key), tries = 0;
	
	while(A[slot].value != INT_MIN && tries<DICT_SIZE)
	{	
		tries++;
		if(A[slot].checkForTombStone())
		{
			slot = (slot+1)%DICT_SIZE;
			continue;
		}	
		
		// Checks if two keys are same.
		bool areTwoKeySame = false;	
		char* key1 = A[slot].key, *key2 = key;	
		
		if(strcmp(key1 , key2 ) == 0) areTwoKeySame = true;
		
		//If key found, then return entry
		if(areTwoKeySame)
		{
			struct Entry *e = new Entry;
			A[slot] = *e;
			A[slot].makeTombStone();
			return true;
		}	
		
		slot = (slot+1)%DICT_SIZE;
	}
	
	return false;
}			 
