#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int l=pattern.length();
  int h[l];
  int len=0;
  h[0]=0;
  for(int i=1;i<l;i++){
        if(pattern[i]==pattern[len]){
            len++;
            h[i]=len;
            }
         else{
              if(len!=0){
                 len=h[len-1];
                 i--;}
         else{
            h[i]=0;
            }
            }
            }
     return h;}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
 int t=text.length();
 int p=pattern.length();
 int h[p];
 h=computeHMatrixForKMP(pattern);
 int i=0;
 int j=0;
 while((t-i)>=(p-j)){
      if(pattern[j]==text[i]){
              j++;
              i++;}
      if(j==p){
               j=h[j-1];
               return i-j;}
      else if(i<t && pattern[j]!=text[i]){
        if(j!=0)
            j=h[j-1]
        else 
            i=i+1;
            }
            }
   return -1;
}

#endif
