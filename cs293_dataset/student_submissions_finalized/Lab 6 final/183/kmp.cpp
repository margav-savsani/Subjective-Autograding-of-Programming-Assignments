#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int l=pattern.length();
  int *h;
  h=new int[l];
  int len=0; //length of previous longest prefix suffix
  h[0]=0;
  //loop calculates h[i] for i=1 to l-1
  for(int i=1;i<l;i++){
        if(pattern[i]==pattern[len]){
            len++;
            h[i]=len;
            }
        else{  //pattern[i]!=pattern[len]
          if(len!=0){
              len=h[len-1];
              i--; //shoud increase i here
          }
          else{ //if len==0
              h[i]=0;
          }
        }
  }
return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int t=text.length();
  int p=pattern.length();
  //creating h[] that will hold longest prefix suffix
  //values for pattern
  //Preprocess the pattern(calculate h[] array)
  hMatrix=computeHMatrixForKMP(pattern);
  int i=0; //index for text
  int j=0; //index for pattern
  while((t-i)>=(p-j)){
        if(pattern[j]==text[i]){
                j++;
                i++;
        }
        if(j==p){
                j=hMatrix[j-1];
                return i-j;}
        //mismatches after j matches
        else if(i<t && pattern[j]!=text[i]){
          //don't match h[0... h[j-1]] characters.
          //they will match anyway
          if(j!=0)
              j=hMatrix[j-1];
          else 
              i=i+1;
        }
  }
  return -1;
}

#endif
