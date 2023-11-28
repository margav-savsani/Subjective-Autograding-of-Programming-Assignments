#include<iostream>
#include<cmath>
#include<string.h>


#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
int DICT_SIZE = 64;

struct Entry
{
  char key[64];
  int value = -99999;
};



class Dictionary
{
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:


  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[])
  {
  	const int p=31, modn=67;
  	int hashValue = 0;
  	long int pow=1;

  	for(int i=0;key[i]!='\0';i++)
    {
  		hashValue = (hashValue + (key[i] +1 -'a')*pow);
  		pow = (pow*p)%modn;
    }

  	float fracin = 0.618034* hashValue;
  	float frac = fracin - floor(fracin);
  	hashValue = floor(N*frac);
  	return hashValue;

  };

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[])
  {
  	char tombstone[]="TOMBSTONE";

  	int location = hashValue(key);
  	int initloc = location;

  	while(strcmp(A[location].key,tombstone)!=0 and A[location].value != -99999)
    {
      location++;
      location = location%DICT_SIZE;

  	  if (initloc == location)
      return -1;
    }

  	return location;
  };

  // Default constructor
  Dictionary()
  {
  	N= 64;
    A = new struct Entry[64];
  }

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry* get(char key[])
  {
  	int location = hashValue(key);
  	int index = location;

  	while(strcmp(A[location].key,key)!=0 )
    {
      location++;
  	  if (index == location)
      return NULL;
    }

  	return A+location;
  }

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e)
  {
  	int position = findFreeIndex(e.key);

  	if(position == -1)
    {
      return false;
    }

  	else
    {
      A[position] = e;
      return true;
    }

  };

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[])
  {
  	int location = hashValue(key);
  	int init_loc = location;

  	while(strcmp(A[location].key,key)!=0 )
    {
      location++;
      location = location%DICT_SIZE;

  	  if (init_loc == location)
      return false;
    }

  	char tombstone[]="TOMBSTONE";
  	strcpy(A[location].key,tombstone);

  	return true;

  };
};

#endif
