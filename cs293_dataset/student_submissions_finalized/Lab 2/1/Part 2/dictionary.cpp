//functions of the dictionary class
#include "planner.h"
#include "math.h"

void copy(char a[], char b[]){
    int i = 0;
    while(a[i] != '\0'){
        b[i] = a[i];
        i++;
    }
    b[i] = a[i];
}

bool compare(char a[], char b[]){ //helper func to compare 2 char arrays.
    int i = 0;
    bool same = true;
    while(a[i] != '\0'){
        if(a[i] != b[i]) return false;
        i++;
        if(i == 32) return false;
    }
    if(b[i] != '\0') return false;
    return true;
}

const int x = 33;
const double phi = (sqrt(5) - 1)/2;
double hash_frac(char key[]){ 
    if(key[0] == '\0'){return 0;}
    else{
        double z = key[0] * phi - int(key[0] * phi) + x * hash_frac(key + 1);
        return z - int(z);
    }
}

int dictionary::hashValue(char key[]){
    return floor(DICT_SIZE * hash_frac(key)); //hash value in [0, DICT_SIZE - 1]
}

//A value of 0 denotes an empty entry, 1 denotes a full entry
int dictionary::findFreeIndex(char key[]){
    int hash = hashValue(key);
    int probe = hash;
    while(A[probe].filled){
        //move ahead while the entry is not empty
        probe = (probe + 1) % DICT_SIZE; //circle around at the end.
        if(probe == hash) return -1; //if back to start, array full, return -1
    }
    return probe;
}

struct Station *dictionary::add(char start[]){ 
    int pos = findFreeIndex(start);
    if(pos == -1) return NULL; //array full, no more space
    else{
        copy(start, A[pos].station1);
        A[pos].filled = true;
        A[pos].num_journeys = 0;
        return A + pos; //return the added entry's address.
    }
}

struct Station *dictionary::get(char key[]){
    int hash = hashValue(key);
    int probe = hash;
    while(A[probe].filled){ //start at hash index
    //move ahead until available entry found
        //compare keys
        if(compare(key, A[probe].station1)){
            return A + probe; //if match return the entry's address
        }
        probe = (probe + 1) % DICT_SIZE; //move circularly
        if(probe == hash) return NULL; //if back to start, no matching key found.
    }
    return NULL;
}

void dictionary::display(){
    for(int i = 0; i < DICT_SIZE; i++){
        if(A[i].filled){
            A[i].display();
        }
    }
}



