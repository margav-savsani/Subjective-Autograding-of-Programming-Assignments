#include "dictionary.h"
#include "math.h"
using namespace std;
const double phi = 1.6180339887;    // fibonacchi number 

Dictionary::Dictionary(){
    this->N = DICT_SIZE;
    this->A = new Entry [N];
}
int Dictionary::hashValue(char key[]){
    unsigned int x = 31;            // 31, 39 etc give good results 
    int h = 0;                      // for storing output of polynomial map
    int i = 0;
    while(key[i] != '\0'){          // polynomial accumulation 
        h = (h*x + (int)key[i]);
        i++;
    }
    double c = 0;
    double a = modf(h*phi, &c);     // fibonacchi compression map
    int b = a*N;
    if (b >= 0){
        return b;
    }
    return -b;
}

/* I am representing a NULL (or empty) with Entry.key[0] = '\0' and tombstone value with Entry.key[0] = 1*/

int Dictionary::findFreeIndex(char key[]){
    int a = hashValue(key);
    for (int i = 0; i < N; i++){
        if (A[(i+a)%N].key[0] == '\0' || A[(i+a)%N].key[0] == 1){
            return (i+a)%N;
        }
    }
    return -1;
}
Entry* Dictionary::get(char k[]){
    int b = hashValue(k);
    int a = b;
    while (A[a%N].key[0] != '\0'){
        if (strcmp(A[a%N].key, k) == 0){
            return &A[a%N];
        }
        else if (b == a%N && a != b){
            return nullptr;
        }
        a += 1;
    }
    return nullptr;
}
bool Dictionary::put(Entry e){
    int b = findFreeIndex(e.key); 
    if (b == -1){
        return 0;
    }
    A[b] = e;
    return 1;
}

bool Dictionary::remove(char key[]){
    Entry* E = get(key);
    if (E == nullptr){
        return 0;
    }
    E->key[0] = 1;
    return 1; 
}