#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<cmath>
#include"planner.h"
#include<string.h>

using namespace std;

Journey :: Journey(){
    value=0;
}

Planner :: Planner(){
    N=64;
    A=new Journey[N];
    for(int i=0;i<N;i++){
      A[i].value = 0;
    }
}
float Planner :: duration(struct Journey J){
   float f= J.t1-J.t2;
   if(f<0)
     return f+2400;
   else
     return f; 
}

int Planner :: hashValue(char s1[]){
  long long unsigned int x=0;
  string y=s1;
  int l = y.length();
  double a = (sqrt(5)-1)/2;
  for(int i=l-1;i>=0;i--){
    int asc = s1[i];
    x= asc+x*5;
  }
  double h = x*a;
  long int hash = h;
  a = (N*(h - hash));
  return int(a);
}

int Planner :: findFreeIndex(char s1[]){
  int hash = hashValue(s1);
  int count = 0;
  while(1){
    if(A[hash].value==0 )
      return hash;
    hash=(hash+1)%64;
    count++;
    if(count==64)
      return -1;
  }

}
bool Planner :: put(struct Journey J){
    if(findFreeIndex(J.s1)==-1)
      return false;
    A[findFreeIndex(J.s1)]=J;
    A[findFreeIndex(J.s1)].value=1;
    return true;
    
}
struct Journey* Planner:: station(char s1[], float t){
	Journey* SN;
	SN = new Journey[N];
	int i=0;
	int h=hashValue(s1);
	while(A[h].value!=0){
		if(strcmp(A[h].s1,s1)==0 && A[h].t1>=t) SN[i]=A[h];
		i++;
		h=(h+1)%N;
	}
	return SN;
}

void Planner:: soonest(char s1[],float k,char s2[]){
   int x=hashValue(s1);
   float t=-1,d1;
    while(A[x].value!=0){
    if(strcmp(A[x].s1,s1)==0 && strcmp(A[x].s2,s2)==0 && A[x].t1>=k ){
       t=A[x].t1; break;       
      }
      x=(x+1)%N;
    }
    while(A[x].value!=0){
    if(strcmp(A[x].s1,s1)==0 && strcmp(A[x].s2,s2)==0 && A[x].t1>=k ){
       d1=A[x].t1; 
       t=min(d1,t);       
      }
      x=(x+1)%N;
    }
    char s[32];
    int p,f;
    float d2=-1,tm,a=2400,h;
    for(int i=0;i<N;i++){
     if(strcmp(A[i].s1,s1)==0 && A[i].t1>=k){
       tm=A[i].t1;
       p=i;
       for(int j=0;j<N;j++)
       if(strcmp(A[j].s1,A[i].s2)==0 && strcmp(A[j].s2,s2)==0) { 
         f=j;                
         if(t!=-1) tm=min(t,tm);
          d2=A[j].t1;
          a=min(d2,a); 
          if(a==d2) f=j;    
       }   
     }
    }
    
    if(d2!=-1)
     cout<<tm<<" "<<A[f].s1<<" "<<a<<endl;
    else if(t!=-1 && d2==-1) cout<<t<<endl;
    else cout<<"ERROR"<<endl;
    }


