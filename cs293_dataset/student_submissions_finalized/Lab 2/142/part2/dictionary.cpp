#include<cmath>
#include"dictionary.h"

using namespace std;

int m = 64;  //size of table
double B = (sqrt(5)-1)/2;

/*struct Entry{
	int value;
	char* key;
}*/
  Dictionary:: Dictionary(){
    N = DICT_SIZE;  
    A = new Entry [N];
    Entry e;
    e.key[0] = '\0';
    int i = 0;
    while(i < N){   //initialising all elements of array as e with key = "" to check if the location is empty 
      A[i] = e;
      i++;
    }
  } 

	// Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int Dictionary:: hashValue(char key[]){
  	int x = 41;   //value taken to minimize number of collisions
  	int h, k = 0,i = 0;  //h = hash value
  	// int *C;  //array of coefficients of polynomial
  	
  	while(key[i]!= '\0'){
  		//C[i] = int(key[i]);
  		k +=  int(key[i])*pow(x,i);//polynomial
  		i++;
  	}
  	// i+1 = number of letters in string
  	//A = [a_0,a_1,.....,a_i]

  	h = m* ((k*B) - int(k*B));
  	return h;
  }

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int Dictionary:: findFreeIndex(char key[]){
  	int i = hashValue(key);
  	while(true){
  		if(A[i].key[0] == '\0')return i;
      if(i == 63)i = -1;
      if(i == hashValue(key)-1)return -1;
  		i++;
  	}
  }

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
   Entry *Dictionary:: get(char key[]){
    int i = hashValue(key);
    for(int k=0; k<64; k++){
      char* temp = A[i+k].key;
      if(temp[0] == '\0' && A[i+k].value != 0){
        break;
      }
      if(!strcmp(temp, key)){
        return &A[i+k];
      }
    }
    return NULL;
  }

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool Dictionary:: put(struct Entry e){
    int x = findFreeIndex(e.key);
  	if(x == -1)return false;
  	A[x] = e;
  	return true;
  }

  // Remove the given key; return true if success, false if failure (given key not present)
  bool Dictionary:: remove(char key[]){
    Entry *e = get(key);
  	if(e==NULL)return false;
  	e->value = 0;   //0 marks the value of element as TOMBSTONE
    e->key[0] = '\0';
    return true;  
  }