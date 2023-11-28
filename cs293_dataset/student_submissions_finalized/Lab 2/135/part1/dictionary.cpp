#include "dictionary.h"
#include <cmath>

using namespace std;

int Dictionary::hashValue(char key[]){
    int a = 0, x = 37;
    for(int i=0; key[i]!='\0'; i++){
        a = a*x + int(key[i]);
    }
    double fibA = 2*a/(sqrt(5)-1);
    double fracA = fibA - floor(fibA);
    int compressedA = floor(fracA*N);
    cout << a << " " << fibA << " " << fracA << " " << compressedA << "\n";
    a = 0;
    return compressedA;
}
int Dictionary::findFreeIndex(char key[]){
    int startIndex = hashValue(key);
    int index = startIndex;
    while(A[index].key[0] != '\0'){
        // cout << A[index].key << "\n";
        index = (index + 1)%N;
        if(index == startIndex){
            return -1;
        }
    }
    return index;
}
Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
}
struct Entry* Dictionary::get(char key[]){
    int startI = hashValue(key);
    int i = startI;
    while(strcmp(A[i].key,key) != 0){
        i = (i+1)%N;
        if((A[i].key[0] == '\0' && !A[i].tomb) || i == startI){
            return NULL;
        }
    }
    return &A[i];
}
bool Dictionary::put(struct Entry e){
    int index = findFreeIndex(e.key);
    if(index<0) return false;
    A[index] = e;
    return true;
}
bool Dictionary::remove(char key[]){
    Entry* toBeRemoved = get(key);
    if(toBeRemoved == NULL) return false;
    int startI = hashValue(key);
    int i = startI;
    while(strcmp(A[i].key,key) != 0){
        i = (i+1)%N;
    }
    A[i] = *(new Entry);
    A[i].tomb = 1;
    cout << i << ", " << A[i].key << ", " << A[i].value << " " << A[i].tomb << "\n";
    return true;
}