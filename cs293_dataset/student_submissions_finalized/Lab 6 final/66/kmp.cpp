#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int hvalue(int *h, int x,int i,string p){
    if(x==0) { 
         if(p[0]==p[i]) {return 1;}
         else return 0;
     }
    else {
         if(p[x]==p[i]) {return x+1;}
         else {return hvalue(h,h[x-1],i,p);}
    } 
}

int *Planner::computeHMatrixForKMP(string pattern) {

  int n=pattern.size(); int* h=new int[n]; h[0]=0;
  
  for(int i=1;i<n;i++){
      h[i] = hvalue(h,h[i-1],i,pattern);
  }
  
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  int l1=text.size(),l2=pattern.size();
  if( l1<l2 ) {return -1;}
  else { int x=-2;
      for(int i=0;i<l2;i++){ 
           if(text[i]!=pattern[i]) {x=i;break;}
      }
      if(x==-2) {return 0;}
      else { int index,shift;
             if(x==0) shift=1;  
             else shift=x-hMatrix[x-1];
             
             index= KMPMatch(text.substr(shift,l1-shift),hMatrix,pattern);
             
             if(index==-1) { return -1; }
             else { return shift+index; }         
      }
  }
}

#endif
