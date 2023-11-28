#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int l=pattern.length();
  int*h=new int[l];
  h[0]=-1; //taking base cases
  h[1]=0; //taking base cases
  for(int i=2;i<l;i++){
    bool done=false;
    int k=h[i-1];
    while(k>=0){
      if(pattern[i]==pattern[k]){ //checking last element with p[h[i-1]]
        h[i]=k+1;
        done=true;
        break;
      } 
      else{
        k=h[k];// updating  k
      }
    }
    if(!done) h[i]=0; //equating it to zero if there is no possible suffix
  }



  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int m=text.length();
  int n=pattern.length();
  int a=0;
  int b=n-1;
  while(a<=m-n){
    int k=check(text,pattern,a,b); //returns the index in text where there is mismatch
    if(k==-1) return a;
    else{
      a=k-hMatrix[k-a];     // shifting a by k-a-h[k-a]           
      b=a+n-1;
    }
  }
  return -1;
}
int Planner::check(string text,string pattern,int a,int b){
  for(int i=a;i<=b;i++){
    if(text[i]==pattern[i-a]) continue;
    else return i; // returning the mismatched index in text
  }
  return -1;

}

#endif
