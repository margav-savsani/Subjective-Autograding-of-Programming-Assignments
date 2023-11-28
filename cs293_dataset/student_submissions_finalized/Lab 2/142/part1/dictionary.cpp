#include<math.h>
#include"dictionary.h"
int m = 64;  //size of table
double B = (sqrt(5)-1)/2;

/*struct Entry{
	int value;
	char* key;
}*/
	// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int Dictionary:: hashValue(char key[]){
  	int x = 41;   //value taken to minimize number of collisions
  	int h, k = 0,i = 0;  //h = hash value
  	int *C;  //array of coefficients of polynomial
  	
  	while(key[i]!= NULL){
  		C[i] = int(key[i]);
  		i++;
  	}
  	// i+1 = number of letters in string
  	//A = [a_0,a_1,.....,a_i]
  	for(int j = 0; j <= i;j++){
  		k +=  C[i]*pow(x,i);  //'key[i]'(ascii value of all letters in string is the coefficient)
  	}
  	h = m* ((k*B)%1.0);
  	return h;
  }

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int Dictionary:: findFreeIndex(char key[]){
  	int i;
  	while(i< 64){
  		if(A[i] = NULL)return i;
  		i++;
  	}
  	if(A[i]){
  		return i;
    }
  	else return -1;
  }

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
   Entry *Dictionary:: get(char key[]){
  	Entry e;
  	for(int i= 0; i < 64; i++){
  		e = A[i];
  		if(e.key==key)return &e;
    }
  	return NULL;
  }

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool Dictionary:: put(struct Entry e){
  	if(findFreeIndex(e.key) == -1)return false;
  	A[findFreeIndex(e.key)] = e;
  	return true;
  }

  // Remove the given key; return true if success, false if failure (given key not present)
  bool Dictionary:: remove(char key[]){
  	if(get(key)==NULL)return false;
  	get(key)->value = -1;   //-1 marks the value of element as TOMBSTONE
  	return true;
  }