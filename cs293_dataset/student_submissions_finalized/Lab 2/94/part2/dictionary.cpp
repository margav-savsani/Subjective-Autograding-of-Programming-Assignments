#include"dictionary.h"
#include<cmath>
int Dictionary::hashValue(char key[]){
    double h=0;//hash value
    int i=0;
    int x=31;
    while(!(key[i]=='\0')){
        h=h*x+key[i];
        h=int(h)%143;
        i++;
    }
    h=h*0.5*(pow(5,0.5)-1);
    h=int((h-int(h))*DICT_SIZE);
    int k=h;
    return k;

}
int Dictionary::findFreeIndex(char key[]){
    int f=hashValue(key);
    if(strcmp(A[f].key,"")==0) return f;
    else{
        f=(f+1)%DICT_SIZE;
        while(!(f==hashValue(key))){
            if(strcmp(A[f].key, "") == 0||strcmp(A[f].key, "t")) return f;
            f=(f+1)%DICT_SIZE;
        }
        return -1;
    }

}

Dictionary::Dictionary(){
    N=DICT_SIZE;
    A=new Entry[N];
    for(int i=0;i<N;i++) strcpy(A[i].key,"");
}
struct Entry * Dictionary::get(char key[]){
    int f=hashValue(key);
    if(strcmp(A[f].key, "") == 0) return NULL;
    else if(strcmp(A[f].key,key) == 0) return &(A[f]);
    else{
        f=(f+1)%DICT_SIZE;
        while(!(f==hashValue(key))){
            if(strcmp(A[f].key, "t") == 0){
                f=(f+1)%DICT_SIZE;
                continue;
            }
            if(strcmp(A[f].key, "")==0) return NULL;
            if(strcmp(A[f].key,key) == 0) return &(A[f]);
            f=(f+1)%DICT_SIZE;
        }
        return NULL;
    }

}
bool Dictionary::put(struct Entry e){
    int f=findFreeIndex(e.key);
    if(f==-1) return false;
    else{
        A[f]=e;
        return true;
    }
}
bool Dictionary::remove(char key[]){
    Entry *a;
    a=get(key);
    if(a==NULL) return false;
    else{
        strcpy(a->key,"t");
        return true;
    }

}


