#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H	
#include "planner.h"
#endif

using namespace std;


int *Planner::computeHMatrixForKMP(string pattern) {
   
  int length=pattern.length(); 
  int harray[length];
  int a=0;
  for(int i=1; i<length; i++){
    if(pattern[i]==pattern[length]){
        a++; 
        harray[i]=a;
        }
    else{
       if(a!=0) 
         {
           a=harray[a-1];
           i--;
          }
       else harray[i]=0;
       }
   }                    
  return harray;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int t_size=text.length();
  int p_size=pattern.length();
  int harray[p_size];
  harray=computeHMatrixForKMP(pattern);
  int i=0,j=0;
  while((t_size-i) >= (p_size-j)){
     if(text[i] == pattern[j])
      {
        i++;
        j++;
       }
     if(p_size == j)
      {
        j=harray[j-1];
        return i-j;  
       }
     else if (i<t_size && pattern[j]!=text[i])
       {
         if(j!=0) j=harray[j-1];
         else i=i+1;
        }
    }         
  return -1;
}

#endif
