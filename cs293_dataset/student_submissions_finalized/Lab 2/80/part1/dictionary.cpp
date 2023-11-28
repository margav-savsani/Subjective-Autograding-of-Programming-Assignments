#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include"dictionary.h"
using namespace std;



//constructor
Dictionary::Dictionary(){
	N = DICT_SIZE;
	A = new Entry[64];
}


// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
int Dictionary::hashValue(char key[]){
	int x = 37;
	int m = DICT_SIZE;
	float A = 0.618;
	float calc = A*x - int(A*x);
	string key1(key);
	int sz = key1.size();
	for(int i = sz-1; i > 0; i--){
		//cout << key[i] << " " << key[i-1] << " ";
		calc = A*key[i-1] + calc*key[i] - int(A*key[i-1] + calc*key[i]);
		//cout << calc << endl;
	}
	return int(m*calc);
	
}

// Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
int Dictionary::findFreeIndex(char key[]){
	int position = hashValue(key);
	int position_init = position;
	while (A[position].give_property() != 0){//while the next entry is not empty
	
		if ((position == position_init - 1) || (position_init == 0 && position == N-1)){ //if it has gone over the dict but not found empty space
			return -1;
		}
		
		position += 1;
		
		if (position == N){//if on adding 1 it crosses beyond the last element
			position = 0;
		}

	}
	
	return position; //that us the free index where the key can be inserted.
	
	
}


// Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
struct Entry *Dictionary::get(char key[]){
	int position = hashValue(key);
	int position_init = position;
	string my_key(key);
	while(A[position].give_property() != 0){//while next position is not empty

		
		char* stored_key = A[position].give_key();	
		string stored_key1(stored_key);
		if(my_key==stored_key1 && A[position].give_property() != 2){//if value matches and it isn't a tombstone then return pointer to that entry
			return &A[position];
		}
		
		if ((position == position_init - 1) || (position_init == 0 && position == N-1)){ //if it has gone over the dict but not found empty space
			return NULL;
		}
		
		position += 1;
		if (position == N){//if on adding 1 it crosses beyond the last element
			position = 0;
		}
		
	}
	return NULL;
	
	

}

// Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
bool Dictionary::put(struct Entry e){
	char* key_req = e.give_key();
	int position = findFreeIndex(key_req);
	if(position == -1){
		return false;
	}
	A[position] = e;
	A[position].make_non_empty();
	return true;
}

// Remove the given key; return true if success, false if failure (given key not present)
bool Dictionary::remove(char key[]){
	Entry *my_entry;
	my_entry = get(key);
	if (my_entry == NULL){
		return false;
	}
	
	(*my_entry).make_tombstone();
	return true;
	
	
}

/*
int main(){
	cout << "run" << endl;
	char myword[] = { 'h', 'e', 'l', 'l', 'e','p', '\0' }; 
	Entry e(myword,5);
	cout << e.give_val() << endl;
	char* word = e.give_key();
	
	int pos = 0;
  	while(word[pos] != '\0'){
    		cout << word[pos];
    		pos += 1;
  	}
  	cout << endl << "done" << endl;
  	
  	Dictionary d;
  	int val = d.hashValue(myword);
  	cout << val << endl;
  	

}
*/













