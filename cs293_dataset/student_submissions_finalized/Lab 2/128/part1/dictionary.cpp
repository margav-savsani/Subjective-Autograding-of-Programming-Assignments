#include "dictionary.h"
#include <cmath>

char* null_marker = "";
char* tombstone = "\b";

int Dictionary::hashValue(char key[]){

    //calculate the hash code
    //x = 41, m = INT_MAX
    int x = 33;
    int modulus = INT32_MAX;
    int code = static_cast <int>(key[0]);
    int multiplier = 1;
    for (size_t i = 1; i < strlen(key) ; i++){
        multiplier *= x;
        multiplier %= modulus;

        code +=  static_cast<int>(key[i]) * multiplier;
        code %= modulus;
    }

    double a = (sqrt(5) - 1)/2;
    double frac = a * code;
    if(frac < 0){frac -= (static_cast<int> (frac)-1);}
    else frac -= static_cast<int> (frac); 

    if(static_cast<int>(frac * DICT_SIZE) < 0){std::cout<< "negative";}
    return static_cast<int> (frac * DICT_SIZE);
    

}

int Dictionary::findFreeIndex(char key[]){

  for(size_t index = hashValue(key); index < hashValue(key) + DICT_SIZE ; index++ ){
      if (strcmp(A[index % DICT_SIZE].key, null_marker) == 0 ){return index % DICT_SIZE;}
  }

  return -1;

}

Dictionary::Dictionary(){
    A = new Entry[DICT_SIZE];

    for (unsigned int i = 0; i < DICT_SIZE; i++){
      strcpy(A[i].key , null_marker);
    }
}

struct Entry* Dictionary::get(char key[]){

    for(unsigned int i = hashValue(key); i < hashValue(key) + DICT_SIZE; i++){

        if ( strcmp(A[i % DICT_SIZE].key, key) == 0 ) { return &A[i % DICT_SIZE]; }
    }

    return NULL;
}

bool Dictionary::put(struct Entry e){
    int index = findFreeIndex(e.key);

    if(index == -1){return false;}

    A[index] = e;
    return true;
}

bool Dictionary::remove(char key[]){
    Entry* entry = get(key);

    if(entry == NULL){return false;}

    strcpy(entry->key, tombstone);
    return true;
}
