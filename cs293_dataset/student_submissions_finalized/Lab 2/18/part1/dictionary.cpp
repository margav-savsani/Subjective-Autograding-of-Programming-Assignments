#include "dictionary.h"
#include<cmath>

Dictionary::Dictionary(){
    N=64;
    A = new Entry[N];
    for(int i=0; i<N; i++){
        A[i].key[0]='\0';
        A[i].value=-1;
    }
}

int Dictionary::hashValue(char key[]){
    int *a;
    a = new int[32];
    for(int i=0; key[i]!='\0'; i++){
        a[i]=key[i];
    }
    int x = 39; //considering x in polynomial accumulation to be 39
    long int k = 0; //k represents the result of the polynomial accumulation, i.e, the int representing the string key
    for(int i=0; key[i]!='\0'; i++){
        double p = (pow(x,i));
        int q = round(p);
        k += q*a[i];
    }
    //A in Fibonacci hashing is reciprocal of golden ratio which is nearly 0.61803399
    double A = 0.61803399;
    double kA = k*A;
    int kA_floor = int(kA);
    double fractional = kA - kA_floor;
    double N_fractional = N*fractional;
    int floor_N_fractional = int(N_fractional);
    return floor_N_fractional;
}

int Dictionary::findFreeIndex(char key[]){
    int probe = hashValue(key);
    if(A[probe].key[0]=='\0') return probe; //free location at hash value itself
    while((A[probe].key[0]!='\0')){
        if(probe<(N-1)) probe++;
        else probe=0; //circular fashion
    }
    if(probe==hashValue(key)) return -1; //no free location
    return probe; //free location at probe
}

struct Entry* Dictionary::get(char key[]){
    int find = hashValue(key);
    while(!((A[find].key[0]=='\0')&&(A[find].value==(-1)))){
        if(A[find].key[0]!='\0'){
        int a = strlen(key);
        int b = strlen(A[find].key);
        if(a=b){
            int i;
            for(i=0; i<a; i++){
                if(A[find].key[i]!=key[i]) break;
            }
            if(i==a) return &A[find];
        }
        }
        if(find<N-1) find++;
        else find=0;
        if(find == hashValue(key)) break;
    }
    return NULL;
}

bool Dictionary::put(struct Entry e){
    int index = findFreeIndex(e.key);
    if (index==(-1)){
        return false;
    }
    A[index].value = e.value;
    A[index].key = e.key;
    return true;
}

bool Dictionary::remove(char key[]){
    if(get(key)==NULL) return false;
    Entry *e = get(key);
    e->value = 0; //tombstone value
    e->key[0] = '\0';
    return true;
}