#include<iostream>
#include "Dictionary.h"
#include<math.h>
#include<string>
#include<cstring>

using namespace std;

#define X 37
#define KNUTH_CONSTANT (sqrt(5)-1)/2

Dictionary::Dictionary(){
    int N;
    A=new Entry [N];
    for(int i=0;i<=N;++i){
        A[i] = Entry();
    } 
}
int Dictionary::hashValue(char *key){
    int b = 0;
    size_t keysize = strlen(key);
    long double pol = 0;
    for(int i=0;i<=keysize-1;++i){
        b=key[i];
        pol=pol*X+b;
        pol=pol*KNUTH_CONSTANT;
        long int j = (long int) pol;
        pol=pol-j;
    }
    return floor(N*(pol));
}
//find free index by using probing method
int Dictionary::findFreeIndex(char *key){
    int hv = hashValue(key);
    for(int i=0;i<=N;++i){
        if(A[hv].con==0 || A[hv].con==-1){
            return hv;
        }
        else{
            hv=(hv+1)%N;
        }
    }
    return -1;
}

struct Entry* Dictionary::get(char* key){
    int hv1 = hashValue(key);
    for(int i = 0;i<=N;++i){
    if(A[hv1].con==0)
        break;  
    if(A[hv1].con==1){
        if(strcmp(key, A[hv1].key)==0){
            return (&A[hv1]);    
        }
        hv1=(hv1+1)%N;
    }
    if(A[hv1].con==-1){
        hv1=(hv1+1)%N;
    }
    }
    struct Entry * q = new Entry();
    return q;
}

bool Dictionary::put(struct Entry e){
    char * s = e.key;
    cout<<hashValue(s);
    if(get(s)->key!=NULL){
        get(s)->f++;
        cout<<get(s)<<endl;
        return true;
    }
    int free = findFreeIndex(e.key);
    if(free==-1){return false;}
    else{
        char *b = e.key;
        A[free].key=b;
        A[free].f=1;
        A[free].con=1;
        N++;
        return true;
    }
}

bool Dictionary::remove(char *key){
    if(N==0){
        return false;
    }
    int hv2 = hashValue(key);
    for(int i = 0 ; i<= N;++i){
        if(A[hv2].con==1){
            if(strcmp(A[hv2].key,key)==0){
                A[hv2].key=NULL;
                A[hv2].con=-1;
                A[hv2].f=0;
                N--;
                return true;
            }
            hv2=(hv2+1)%N;
        }
        else if(A[hv2].con==-1){
            hv2=(hv2+1)%N;
        }
        else{
            break;
        }
    }
    return false;
} 
