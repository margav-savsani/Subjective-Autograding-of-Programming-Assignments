#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;
//int *
 int * Planner::computeHMatrixForKMP(string pattern) {
  int j=0;
  for(j=0;j<pattern.length();j++)pattern[j]=toupper(pattern[j]);

  int* hArray = new int[pattern.length()];

  string W = pattern;
  W[0]='$';

  (hArray[0])=0;
  int k = 0;
  for(int i=1;i<pattern.length();i++){
    
    while(pattern[i]!=pattern[k] && k>0){
      k=hArray[k-1];
    } 
    if(pattern[k]==pattern[i]){
      k=k+1;
    }
    hArray[i]=k;
  }



  return hArray;
}
//Planner::
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  int m=0, n=0;
  int text_len=text.length();
  int string_len=pattern.length();

  while((string_len- n )>= (text_len - m)){
    if(pattern[n]==text[m]){m+=1;n+=1;}
    if(n==string_len) return m;

    else if(m<text_len and pattern[n]!=text[m]){
      if(n!=0){
        n = hMatrix[n-1];
      }
      else{
        m++;
      }
    }
    cout<<"in pat: "<<n<<" in text:"<< m;
  }

  return -1;
}

#endif
