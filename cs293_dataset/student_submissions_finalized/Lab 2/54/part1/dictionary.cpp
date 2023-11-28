#include<cmath>
#include "dictionary.h"
int Dictionary:: hashValue(char key[]){
	  double hash=0;
	  int i;
	  int k;
	  double a= (sqrt(5)-1)/2;
	  double b= (sqrt(5)+1)/2;
	  for(i=0;i<32;i++){
		 if  (key[i]=='\0') break;}
	  while(i>=0){
		  hash=a*(hash*3*b+(int)key[i]);
	          k =int(hash);
                  hash=hash-k;		  
	          i--;
	  }
          k=hash*64;
	  return k;
  }
  
  int Dictionary:: findFreeIndex(char key[]){
       int hash;
	 hash =hashValue(key);
	 int i;
	 for(i=hash;i<N;i++){
		 if ((A[hash].check=='E')||(A[hash].check=='T')) return i;
	 }
         for(i=0;i<hash;i++){
            if ((A[hash].check=='E')||(A[hash].check=='T')) return i;
         }
         return -1;}
  
Dictionary::Dictionary(){
	N=64;
      A =new Entry[64];
      for (int i=0;i<64;i++){
        A[i].check='E';} 
  }

 Entry* Dictionary:: get(char key[]){
  	  int hash=hashValue(key);
	  for(int i=hash;i<64;i++){
            if (A[i].check=='T') continue;		  
            if (A[i].check=='E') return NULL;		  
	    for (int j=0;j<32;j++){
            if (A[i].key[j]!=key[j]) break;}
	    return &A[i];
          }    
          for(int i=0;i<hash;i++){
            if (A[i].check=='E') return NULL;
            for (int j=0;j<32;j++){
            if (A[i].key[j]!=key[j]) break;}
            return &A[i];
          }
      return NULL;
 }	     
  bool Dictionary::put(struct Entry e){
	int i= findFreeIndex(e.key);
        if (i==-1) return false;
	for (int k=0;k<32;k++){
	A[i].key[k]=e.key[k];
	}
	A[i].value=e.value;
        A[i].check='O';
	return true;
  }
 
  bool Dictionary::remove(char key[]){
        Entry *B;
        B=get(key);
	int hash=hashValue(key);
	  if (B==NULL) return false;
        int k;
        for(k=hash;k<64;k++){
          if (B==&A[k]) break;}
	if (k==64) k=0;
	for(k=0;k<hash;k++){
          if (B==&A[k]) break;}		
	for(int i=0;i<32;i++){
	     A[k].key[i]='0';
	}
        A[k].check='T';
	return true;  
  }

