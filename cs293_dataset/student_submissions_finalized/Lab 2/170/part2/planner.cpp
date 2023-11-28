#include<iostream>
#include<cmath>

using namespace std;
#include"planner.h"

float C=(sqrt(5)-1)/2.0;

Journey:: Journey(){
	value=0;
}

Planner:: Planner(){
	N=100;
	A= new Journey[N];
	for(int i=0; i<N; i++){
		A[i].value=0;
	}
}

float Planner:: duration(struct Journey j){
	float f=j.et-j.st;
	if(f<0) return f+2400;
	else return f;
}

int Planner:: hashValue(char key[]){
	int asc;
	string s=key;
	int l=s.length();
	float f;
	long long unsigned int h=0;
	for(int i=l-1; i>=0; i--){
		asc=key[i];
		h=asc+h*5;
	}
	float k=h*C;
	long long int m=k;
	f=k-m;
	int z=N*f;
	return z;
}

int Planner:: findFreeIndex(char key[]){
	int h=hashValue(key);
	int iteration=0;
	while(true){
		if(A[h].value==0)return h;
		h=(h+1)%N;
		iteration++;
		if(iteration==N){return -1;}
	}
}

bool Planner:: put(struct Journey j){
	int i=findFreeIndex(j.s1.s);
	if(i==-1)return false;
	 else {
	 	A[i]=j;
	 	A[i].value=1;
	 	return true;
	 }
}

struct Journey* Planner:: get(char key[], float t){
	Journey* SN;
	SN = new Journey[N];
	int i=0;
	int h=hashValue(key);
	while(A[h].value!=0){
		if(strcmp(A[h].s1.s,key)==0 && A[h].st>=t) SN[i]=A[h];
		i++;
		h=(h+1)%N;
	}
	return SN;
}

void Planner:: soonest(char station1[],float k,char station2[]){
   int x=hashValue(station1);
   float t1=-1,d1;
    while(A[x].value!=0){
    if(strcmp(A[x].s1.s,station1)==0 && strcmp(A[x].s2.s,station2)==0 && A[x].st>=k ){
       t1=A[x].st; break;       
      }
      x=(x+1)%N;
    }
    while(A[x].value!=0){
    if(strcmp(A[x].s1.s,station1)==0 && strcmp(A[x].s2.s,station2)==0 && A[x].st>=k ){
       d1=A[x].st; 
       t1=min(d1,t1);       
      }
      x=(x+1)%N;
    }
    char s[32];
    int p,f;
    float d2=-1,t2,a=2400,h;
    for(int i=0;i<N;i++){
     if(strcmp(A[i].s1.s,station1)==0 && A[i].st>=k){
       t2=A[i].st;
       p=i;
       for(int j=0;j<N;j++)
       if(strcmp(A[j].s1.s,A[i].s2.s)==0 && strcmp(A[j].s2.s,station2)==0) { 
         f=j;                
         if(t1!=-1) t2=min(t1,t2);
          d2=A[j].st;
          a=min(d2,a); 
          if(a==d2) f=j;    
       }   
     }
    }
    
    if(d2!=-1)
     cout<<t2<<" "<<A[f].s1.s<<" "<<a<<endl;
    else if(t1!=-1 && d2==-1) cout<<t1<<endl;
    else cout<<"ERROR"<<endl;
    }
