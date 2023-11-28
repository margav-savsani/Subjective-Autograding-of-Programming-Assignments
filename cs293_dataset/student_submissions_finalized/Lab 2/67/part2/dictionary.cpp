//kartikn
//cs293
//lab2
//210050083 = 11071 * 18973
#include"dictionary.h"
using namespace std;
const int PRIME_POLY = 41;
const int PRIME_MOD = 18973;
const double PHINV= 0.618033988;
// Return the hash value (between 0 and N-1) of the given string assume string is null terminated and of max length 32
int Dictionary::hashValue(char key[]){
    unsigned int code= 0;
    for(int i=0; key[i]!='\0';i++){ //horner's rule iteratively in reverse order
        code=(code*PRIME_POLY)%PRIME_MOD;//using mode to 1- keep number small for calc frac part, 2- no overflows
        code+=key[i];    
    }
    
    float garb;//collecting integral part of next function, garbage essentially
    //float rem=modf(code*PHINV,&garb);
    // int (size*(code*A mod 1))
    int hash = (modf(code*PHINV,&garb))*N;
    //cout<<rem<<'\t'<<garb<<endl;
    return hash;
}

  // Find the position where given key can be inserted (after resolving hash collision if any) return value between 0 and N-1 if free location present return -1 if no free location
int Dictionary::findFreeIndex(char key[]){
    int hashval= hashValue(key);
    for (int i=0;i<N ;i++){
        if (A[(hashval+i) %N].key[0]=='\0'||(strcmp(A[(hashval+i) %N].key,"__X__")==0))//free or tombstone
            return (hashval+i)%N;
    }
    return -1;
}
  
  // Default constructor
Dictionary::Dictionary() {
    N = DICT_SIZE;
    A = new Entry[N];
}
Dictionary::~Dictionary() {
    delete[] A;
}

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
struct Entry * Dictionary::get(char key[]){
    int hashval= hashValue(key);
    for (int i=0;i<N ;i++){
        if (A[(hashval+i) %N].key[0]=='\0') //empty, unfilled space
            return NULL;
        if (strcmp(A[(hashval+i)%N].key,key)==0) // equal to key
            return (A + (hashval +i)%N);
    }
    return NULL;
}

  // Put the given entry in the appropriate location (using hashing) in the dictionary return true if success, false if failure (array is full)
bool Dictionary::put(struct Entry e){
    int free= findFreeIndex(e.key); //-1 if none, otherwise the index
    if (free==-1) return false;
    A[free] = e;
    return true;
}

  // Remove the given key return true if success, false if failure (given key not present)
bool Dictionary::remove(char key[]){
    Entry *found = get(key);
    if (found == NULL) return false;
    strcpy(found->key,"__X__"); //tombstone
    return true;
}
//char *strcpy(char *dest, const char *src)
