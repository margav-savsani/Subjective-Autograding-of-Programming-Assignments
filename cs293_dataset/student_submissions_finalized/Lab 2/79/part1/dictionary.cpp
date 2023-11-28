#include "dictionary.h"
#include<math.h>
int Dictionary :: hashValue(char key[]){

    //hash value calculation
    const int x = 33;
    const int m = 64;
    int hashValue = 0;
    for(int i = 31; i >= 0; i--){
        hashValue = (hashValue*x + key[i]); // Polynomial Accumulation Scheme
    }


    // compression mapping
    double A = (sqrt(5)-1)/2; //inverse of Golden Ratio
    double intPart, fracPart;
    fracPart = modf(hashValue*A, &intPart); // returns fractional part and stores integer part in the pointer provided
    int reducedHashValue = fracPart*m;
    return reducedHashValue;
}
int Dictionary :: findFreeIndex(char key[]){
    int i = 0;
    for(i = 0; i < 64; i++) {
        if(A[i].key == key) break; // finding index for the key
    }
    if((A[i].value) == -1) return i;// if that index is not already occupied, return the index
    else{
        int j = 0;
        while(A[i].value != -1){
            
        }
    }

}
Dictionary :: Dictionary(){
    
}
struct Entry Dictionary :: *get(char key[]){
    
}
bool Dictionary :: put(struct Entry e){
    
}
bool Dictionary :: remove(char key[]){
    
}