#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int* h;
  string s="$"+pattern+"$"; // created a new string where s[i] gives ith char in pattern.
  int n=pattern.size();
  h=new int[n+1];
  h[0]=-1;
  h[1]=0;
  if(s[2]==s[1]){
    h[2]=1;
  }
  else{
    h[2]=0;
  }
  for(int j=3;j<=n;j++){   // implemented using standard failure function
    int k=h[j];
    while(true){  
      if(s[j+1]==s[k+1]){  // if s[j+1] and s[k+1] matches then h[j+1] = 1+k,where k is a parameter changing through each iteration
        h[j+1]=1+k;
        break;
      }
      if(k==0){        //if k=0,then h[1+j] becomes 0.    
        h[j+1]=0;
        break;
      }
      k=h[k];
    }
  }

  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  hMatrix[0]=-1;
  int szt=text.size();
  int szp=pattern.size();
  string t="$"+text;
  string p="$"+pattern;
  int i=1;
  int j=1;
  while(i<=szt){
    if(t[i]==p[j]){      // matches chars from text and pattern
      if(j==szp){        // if all chars of pattern matches,return i-szp ,from where pattern matches to text
        return (i-szp);
      }
      i++;
      j++;
    }
    else{               // if not matched at middle of pattern,now shift pattern according to correct failure function
      int shift=j-1-hMatrix[j-1];
      if(j==1){
          i+=1;
      }
      if(j>1){
         j=j-shift;
      }
    }
  }
  return -1;
}

#endif
