#include "dictionary.h"
#include <cmath>
using namespace std;

Dictionary :: Dictionary(){
    N = 64;
    A = new Entry[64];            // not including this resulted in seg fault
    for(int i=0;i<DICT_SIZE;i++){
        A[i].value = 0;
    }
}

int Dictionary :: hashValue(char key[]){
    double B = (sqrt(5.00)-1.00)/2.00;
    int x = 33;
    int poly = 0;
    string K = key;                  // char to string conversion to use length()
    int s = K.length();

    for (int i = s-1 ; i>=0 ;i--){
        int asval = key[i];
 	    poly = (poly*x + asval)%N;   // mod N is included here itself to avoid overflow 
    }
    double C = poly*B;
    int D = C;
    int hv = N*(C-D);
    return hv;
}

int Dictionary :: findFreeIndex(char key[]){
    int E = hashValue(key);
    bool free = true;
    for ( int i =0 ; i<N ; i++){
        if( A[i].value == 0 || A[i].value == -1 ) free = false ;break;    // value 0 means null entry and value -1  means tombstone
    }
    if(free == true)return -1;
    if (A[E].value != 0 || A[E].value != -1){
        E = ((E+1)%N) ;
    }
    return E;
}

struct Entry* Dictionary :: get(char key[]){
    char *F = key;
    int G = hashValue(F);
    for(int i=G;i<N;i++){
        if(strcmp(A[i].key , F) == 0){            // strcmp is used as we can't compare char=char
            return &A[i];
        }
    } 
    for(int i=0;i<G;i++){
        if(strcmp(A[i].key , F) == 0){
            return &A[i];
            }
        }

    return NULL;

}    


bool Dictionary :: put(struct Entry e){
    char *H = e.key;
    if(findFreeIndex(H)==-1) return false;       
    strcpy(A[findFreeIndex(H)].key , H );         //strcpy is used as key is char array
    A[findFreeIndex(H)].value = e.value;
    return true;       
}    
bool Dictionary :: remove(char key[]){
    char *I = key;
    Entry *J =get(I);
    if (J==NULL)return false;
    else 
        (*J).value = -1;
        return true;
}