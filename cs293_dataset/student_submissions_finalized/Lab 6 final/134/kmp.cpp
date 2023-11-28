#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#include<bits/stdc++.h>
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  /*int *HMatrix = new int[pattern.size()];
  for(int i=0; i<pattern.length(); i++){
    for(int val=HMatrix[i]; val>=0; val--){
      bool found=true;
      for(int k=0; k<val; k++){
        if(pattern[k] != pattern[k+i-val+1]){
          found=false;
          break;
        }
      }
      if(found){
        HMatrix[i]=val;
        break;
      }
    }
  }
  
  return HMatrix;*/

  int i=1;
  int j=0; // last index of similar str which has
  int *HMatrix = new int[pattern.size()];
  HMatrix[0] = 0;
  while(i<pattern.length()){
    if(pattern[j] == pattern[i]){
      // when indices j and i are equal, we can increase the len of similarstr by 1 and proceed to next comp 
      HMatrix[i] = j+1;
      i++;
      j++;
    }
    else if(j!=0) // if indices are not equal we replace the th largest suffix with similar str
      j = HMatrix[j-1];
    else
      HMatrix[i] = 0; // edge case when the simlar str is empty
      i++;
  }
  //for(int i=0; i<pattern.length(); i++){
  //  cout << HMatrix[i] << "  ";
  //}
  //cout << endl;
  return HMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  transform(text.begin(), text.end(), text.begin(), ::toupper);
  transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper);
  int currTextind=0;
  int currPatternind=0;
  while(currTextind < text.length()){
   // cout << currTextind << "  " << currPatternind << " ||| ";

    if(text[currTextind] == pattern[currPatternind]){
      currTextind++;
      currPatternind++;
      //cout<<"1 " << currTextind << "  " << currPatternind << endl;
      if(currPatternind==pattern.length())
        return currTextind-pattern.length();
    }
    else if(currPatternind == 0){
      currTextind++;
      //cout<<"2 " << currTextind << "  " << currPatternind << endl;
    }
    else{
      currPatternind = hMatrix[currPatternind];
      currTextind++;
      //cout<<"3 " << currTextind << "  " << currPatternind << endl;
    }
  }
  //cout << endl;
  return -1;
}

#endif
