#include"dictionary.h"
#include<iostream>
#include<cmath>
using namespace std;
int polynomial_accumulation (char key[32],int n,int x,int i,int N){
    if(i==n-1){return key[n-1];}
    return (int(key[i])%N+(x*polynomial_accumulation(key,n,x,i+1,N))%N)%N;
}
int Dictionary::hashValue(char starting_station[32]){
    int a=0;
    for(int i=0;starting_station[i]!=0;i++){
        a++;
    }
    
    double b=polynomial_accumulation(starting_station,a,33,0,N);
    
    double f=(sqrt(5)-1)/2;
    
   int g=int(N*(f*b-int(f*b)));
   
    return g;
    
}

Dictionary::Dictionary(){
    N=DICT_SIZE;
  A=new Entry[N];
    
    for(int i=0;i<N;i++){
        A[i].starting_time=-1;
        A[i].ending_time=-1;
        
    }
    
}
bool arra(char key[],char b[]){
    for(int i=0;key[i]!=0;i++){
        if(key[i]!=b[i]) return false;
    }
    return true;
}

bool Dictionary::put(struct Entry e){
    int a=hashValue(e.starting_station);
    for(int i=a;i!=(a-1);i=(i+1)%N){
       if( A[i].starting_time==-1&&A[i].ending_time==-1){
        A[i]=e;
        
        return true;}

    }
    return false;
}


    

