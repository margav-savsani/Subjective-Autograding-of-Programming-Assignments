#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;
int Planner::compute_failure_function(int* arr,int i,string pattern){
  if(i==0){
    if(pattern[0]==pattern[i+1]){
      return 1;
    }
    return 0;
  }
  else if(pattern[i+1]==pattern[arr[i]+1]){
    return arr[i]+1;
  }
  else {
    compute_failure_function(arr,arr[i],pattern);
  }
 return 0;
}
int *Planner::computeHMatrixForKMP(string pattern) {
   int a=pattern.length();
   int *arr=new int[a];
   arr[0]=0;
   for(int i=1;i<a;i++){
      arr[i]=compute_failure_function(arr,i-1,pattern);
   }
  return arr;
}
int Planner::number_of_occurences(string text, int *hMatrix,string pattern,int p){
  if(text.length()-p+1<pattern.length()){
    return 0;
  }
   for(int i=p;i<text.length();i++){
  for(int j=0;i<pattern.length();j++){
    if(pattern[j]!=text[p+j]){
      return number_of_occurences(text,hMatrix,pattern,p+hMatrix[j]);
    }
  }
  return 1+number_of_occurences(text,hMatrix,pattern,p+hMatrix[pattern.length()-1]);
 }
 return 0;
}
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
 
  return number_of_occurences(text,hMatrix,pattern,0);
}

#endif
