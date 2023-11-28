#include "dictionary.h"
#include <cmath>
using namespace std;
Dictionary :: Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
}

int Dictionary :: hashValue(char key[]){
    int hcm = 0; //hashcodemap value
    float fib = (pow(5,0.5)-1)/2;
    int count = 0;
    while(key[count] != '\0'){
        hcm += (key[count])*int(pow(2,count));
        count++;
    }
    float fp = fib*hcm - long(fib*hcm); //fractional part
    return (int(N*fp));

}

int Dictionary :: findFreeIndex(char key[]){
    int index = hashValue(key);
    int initial_index = index;
    while(A[index].value != 0 && A[index].value != -1){
        index = (index+1)%N;
        if(index == initial_index) return -1;
    }
    return index;
    

}

bool Dictionary :: put(struct Entry e){
    int index = findFreeIndex(e.key);
    if(index == -1){
        return false;
    }
    else{
        A[index] = e;
        return true;
    }
    
    
}
bool Dictionary :: isequal(char key[],int index){
    int i=0;
    while(key[i] != '\0'){
        if(key[i] != A[index].key[i]) return false;
        i++;
    }
    if(A[index].key[i]!='\0') return false;
    return true;
}

struct Entry * Dictionary :: get(char key[]){
    int index = hashValue(key);
    int initial_index = index;
    
    while(!isequal(key,index)|| A[index].value <0){
        index = (index + 1)%N;
        if(index == initial_index || (A[index].value == 0)){
            return NULL;
        }
    }
    return &A[index];
    
}

bool Dictionary :: remove(char key[]){
    struct Entry *B;
    B = get(key);
    if(B == NULL)
        return false;
    else{
         B->value = -1;
        return true;
    }
}


