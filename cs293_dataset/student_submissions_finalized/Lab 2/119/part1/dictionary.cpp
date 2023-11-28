#include "dictionary.h"
#include <math.h>

const int EMPTY_HASH_VAL = -1000;
const int TOMB_HASH_VAL = -2000;

int Dictionary::hashValue(char key[]) {
    int hash = 0, str_len=strlen(key);
    int alpha=33, beta=86743; //9973; //86743; //38083;     // these values seem to give good hash functions
    double A = (sqrt(5)-1)/2;

    int mult = 1;
    for(int i=0; i<str_len; i++){
        hash += (hash + (key[i])*(mult))%beta;              // taking mod to avoid overflows
        mult = (mult*alpha)%beta;                           // taking mod to avoid overflows
    }

    double frac = hash*A; frac = frac - (int) frac; 
    int h = N*frac;
    return h;
}

int Dictionary::findFreeIndex(char key[]){
    int hash = hashValue(key);

    int offset = 0;
    while(offset<N){
        if(A[(hash+offset)%N].value == EMPTY_HASH_VAL){     // if EMPTY, return index
            return (hash+offset)%N;                          
        }                                                   
        offset++;                                           // if TOMB or filled space, ignore
    }
    return -1;                                              // if array full, return -1
}
  
Dictionary::Dictionary(){
    N = DICT_SIZE; A = new Entry[N]; 
    Entry dfault; dfault.key = "this_is_my_personal_dfault_string"; dfault.value = EMPTY_HASH_VAL;
    // a dummy entry struct for EMPTY
    for(int i=0; i<N; i++){
        A[i] = dfault;
    }
} 

struct Entry* Dictionary::get(char key[]){
    int hash = hashValue(key);

    int offset = 0;
    while(offset<N){
        if(A[(hash+offset)%N].value == hash){               // if location found, return index
            return &A[(hash+offset)%N];
        }
        if(A[(hash+offset)%N].value == EMPTY_HASH_VAL){     // if EMPTY, return NULL
            return NULL;
        }
        offset++;                                           // if TOMB or filled space, ignore
    }
    return NULL;                                            // if not in array, return NULL
}

bool Dictionary::put(struct Entry e){
    int t = findFreeIndex(e.key);
    if(t==-1){                                              // if array full, return false
        return false;
    }
    A[t] = e;                                               // else put
    return true;
}

bool Dictionary::remove(char key[]){
    int index = hashValue(key);
    Entry *t = get(key);
    
    if(t==NULL){
        return false;                                       // if not in array, return false
    }
    Entry tomb; tomb.key = "this_is_my_personal_tomb_string"; tomb.value = TOMB_HASH_VAL;
    // a dummy entry struct for TOMB

    int index2 = (t-A+N)%N;
    A[index2] = tomb;                                       // else remove and put TOMB in place
    return true;
}