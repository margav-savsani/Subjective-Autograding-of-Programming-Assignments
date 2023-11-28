#include <cmath>
#include <vector>
#include "dictionary.h"
using namespace std;

//Constructor 
Dictionary::Dictionary(){
	N = DICT_SIZE;
	A = new struct Journey[N];
	
	for(int i=0; i<N; i++)
	{
		struct Journey *j = new struct Journey;
		A[i] = *j;
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
		if(A[slot].empty) break;
		tries++;
		slot++;	
	}
	
	if(tries<DICT_SIZE) return slot;
	else return -1;
}


bool Dictionary::put(struct Journey j){

	//Calculating free slot in hash table
	int slot, tries = 0;
	char key[32];
	strcpy(key , j.from);
	slot = findFreeIndex(key);

	if(slot != -1) {
		j.empty = false;
		A[slot] = j;
		return true;
	}	
	else return false;
}


vector<struct Journey*> Dictionary::get(char key[]){
	
	int slot = hashValue(key), tries = 0;
	vector<struct Journey*> result;
	
	while(!A[slot].empty && tries<DICT_SIZE)
	{
		tries++;	
		
		// Checks if two keys are same.	
		bool areTwoKeySame = false;
		char *key1 = A[slot].from , *key2 = key;	
		if(strcmp(key1, key2) == 0) areTwoKeySame = true;
		
		if(areTwoKeySame) result.push_back(&A[slot]);
		
		slot = (slot+1)%DICT_SIZE;
	}
	
	return result;
}			 
