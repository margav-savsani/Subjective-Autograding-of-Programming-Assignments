#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int res[pattern.length()] = { 0 }; //the array to store the h(i) temperorarily initialised with all elements as 0
  res[0]=0; // first element is manually added 
  for(int i=1;i<pattern.length();i++){
    int tru[i] = { 0 }; // an array to store all the matching parts from which later only the max of all would be taken  
    for(int j=0;j<i;j++){
        int i1=i;
        int j1=j; //defined variables so that changes made wont affect the actual values
        int x=0; //which calculate the length of the part of the pattern which matching or the part which we need
      while(i1!=-1 && j1!=-1){
        if(pattern[j1] == pattern[i1]){
        x=x+1;
        j1=j1-1;
        i1=i1-1;
        }
        else {
        break;}
      }
      if(x==j+1){
        tru[j]=x;
        x=0;
      }
    }
    for(int k=0;k<i;k++){
      if(tru[k]>res[i]) res[i]=tru[k]; // finding the max of all the matching parts for a particular "i" and overriding it in the "res" array
    }
  }
  int *a;
  a=res;
  return a; // returns the address of the array
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int j=0; //index of the array text
  while(j+pattern.length()-1 <text.length()){
    int i=0; // index of the array pattern
    if(text[j]==pattern[i]){
      while(i < pattern.length() && text[j]==pattern[i]){
        i=i+1;
        j=j+1;
      } // going as long as the pattern and text matches 
      if(i==pattern.length()){
        return j-pattern.length()+1;
      } // if the whole pattern matches
      else {
        j=j-hMatrix[i];
      } // else shifting the pattern forward
    }
    else{
        j=j+1;
    }
  }
  return -1; //if the matching part is not found
}

#endif
