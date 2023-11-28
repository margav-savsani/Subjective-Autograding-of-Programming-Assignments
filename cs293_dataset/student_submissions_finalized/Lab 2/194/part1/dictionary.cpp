#include "dictionary.h"
#include "cmath"

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
    for(int i=0;i<N;i++){
        strcpy(A[i].key,"");
    }
}

int Dictionary::hashValue(char key[]){
    int prev_overflow = 1e7+19;
    int hash_val = 0;
    int x_pow=1;
    int x=37;
    for(int i=0; key[i]!='\0' && i<32 ; i++){
        hash_val=(hash_val+((key[i]-'a'+1)*x_pow))%prev_overflow;
        x_pow*=x;
    }
    int comp_val;
    double B= (sqrt(5)-1)/2;
    int m=64;
    double temp=(B*hash_val)-floor(B*hash_val);
    comp_val= (floor((temp)*m));
    comp_val=comp_val%m;
    return comp_val;
}

int Dictionary::findFreeIndex(char key[]){
    int hash_val=hashValue(key);
    for(int i=hash_val;  ; i=(i+1)%N){
        if((i+1)==hash_val){
            if((strcmp(A[i].key,"")==0)||strcmp(A[i].key,"X")==0){
                return i;
            }
            else{
                break;
            }
        }
        if((strcmp(A[i].key,"")!=0)||(strcmp(A[i].key,"X")!=0)){
            continue;
        }
        else{
            return i;
        }

    }
    return -1;
}

Entry* Dictionary::get(char key[]){
    int hash_val=hashValue(key);
    for(int i=hash_val; strcmp(A[i].key,"")!=0; i=(i+1)%DICT_SIZE){
        if(strcmp(A[i].key,key)==0){
            Entry *temp=new Entry();
            strcpy(temp->key,key);
            temp->value=A[i].value;
            return temp;
        }
        if((i+1)==hash_val){
            break;
        }
        else continue;
    }
    return NULL;
}

bool Dictionary::put(Entry e){
    int hash_val=hashValue(e.key);
    
    for(int i=hash_val;  ;i=(i+1)%N){
        if(strcmp("",A[i].key)==0){
            A[i]=e;
            return true;
        }
        if(i==hash_val-1){
            return false;
        }
    }
    return false;
}

bool Dictionary::remove(char key[]){
    int hash_val=hashValue(key);
    for(int i=hash_val; strcmp(A[i].key,"")!=0; i=(i+1)%N){
        if(strcmp(A[i].key,key)==0){
            strcpy(A[i].key,"X"); //tombstone
            A[i].value=0;
            return true;
        }
        if(i==hash_val-1){
            return false;
        }
    }  
    return false;
}
