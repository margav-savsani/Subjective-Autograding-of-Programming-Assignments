#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int n=pattern.length();
  
  //converting to lowercase
  string pattern2="";
  for(int i=0; i<n; i++){
    if('A'<=pattern[i] && pattern[i]<='Z'){
      pattern2+=pattern[i]-'A'+'a';
    }
    else{
      pattern2+=pattern[i];
    }
  }
  pattern=pattern2;

  //computing h1 array which has more relaxed constraints, to help in computing harray
  int *harray=new int[n];
  int *h1=new int[n];
  for(int i=0; i<n; i++){
    if(i==0){
      harray[i]=0;
      h1[i]=0;
      continue;
    }
    if(i==1){
      harray[i]=0;
      h1[i]=0;
      continue;
    }
    int prev=h1[i-1];
    if(pattern[i-1]==pattern[prev]){
      h1[i]=prev+1;
    }
    else{
      h1[i]=0;
      while(prev>0){
        prev=h1[prev];
        if(pattern[i-1]==pattern[prev]){
          h1[i]=prev+1;
          break;
        }
      }
    }
    prev=h1[i];
    if(pattern[i]!=pattern[prev]){ //checking additional constraint for harray
        harray[i]=h1[i];
    }
    else{
      harray[i]=0;
      while(prev>0){
        prev=h1[prev];
        if(pattern[i]!=pattern[prev]){
          harray[i]=prev;
          break;
        }
      }
    }
  }
  delete[] h1; // deallocating space
  return harray;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int n1=pattern.length(), n2=text.length();

  //converting everything to lowercase
  string pattern2="", text2="";
  for(int i=0; i<n1; i++){
    if('A'<=pattern[i] && pattern[i]<='Z'){
      pattern2+=pattern[i]-'A'+'a';
    }
    else{
      pattern2+=pattern[i];
    }
  }
  for(int i=0; i<n2; i++){
    if('A'<=text[i] && text[i]<='Z'){
      text2+=text[i]-'A'+'a';
    }
    else{
      text2+=text[i];
    }
  }
  pattern=pattern2;
  text=text2;
  
  int i=0,matched=0;
  int match_start_index;
  while(i<text.length()){
    if(text[i]==pattern[matched]){
      if(matched==0) match_start_index=i;
      matched++;
      i++;
      if(matched==pattern.length()){
        return match_start_index; // pattern found
      }
    }
    else{
      if(matched==0){
        i++;
      }
      else{
        int new_matched=hMatrix[matched];
        i+=matched-new_matched; // shift by amount dictated by harray
        matched=new_matched;
      } 
    }
  }
  return -1; //pattern not found
}

#endif
