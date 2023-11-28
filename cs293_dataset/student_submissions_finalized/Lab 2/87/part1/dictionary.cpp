#include "dictionary.h"
#include <cmath>

int Dictionary::hashValue(char key[]){
        int a = 0;
        int b = 37;
        double c = (sqrt(5)-1)/2;
        for(int i=strlen(key)-1;i>=0;i--){
                a = int(key[i])+a*b;
        }
        double fractpart,intpart;
        fractpart = abs(modf(c*a,&intpart));
        return int(N*fractpart);
};


int Dictionary::findFreeIndex(char key[]){
	int i=hashValue(key);
    	while((A[i].index!=0)||(A[i].index!=-1)){
        	if((A[i].index==0)||(A[i].index==-1))
            	return i; 
        i=(i+1)%N;
        if(i == hashValue(key)){
            return -1;
        }
    }
    return i;
}

struct Entry* Dictionary::get(char key[]){
        int i = hashValue(key);
        if(strcmp(A[i].key,key)==0){
        return &A[i];
    }
        int j = i + 1;
    while(j != i && (A[j].index)!=0){
                if(strcmp(A[j].key,key)==0){
            return &A[j];
        }
                j = (j+1)%N;    
        }
        return NULL;    
}


bool Dictionary:: put(struct Entry e){
        int i = findFreeIndex(e.key);
        if(i == -1) return false;
        else   A[i] = e;
        return true;
}


bool Dictionary::remove(char key[]){
        if(N==0) return false;
        Entry* B = get(key);
        if(B==NULL) return false;
        B->index=-1;
        return true;
}

