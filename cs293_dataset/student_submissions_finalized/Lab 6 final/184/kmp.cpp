#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  int n=pattern.length();
  int *hmat = new int[n];
  for(int i=0;i<n;i++)
  {
      hmat[i]=0;
  }
  for(int i=1;i<n;i++)
  {
    int j=hmat[i-1];
    while(j>0 and pattern[i]!=pattern[j])
    {
      j=hmat[j-1];
    }
    if(pattern[i]==pattern[j]) j++;
    hmat[i]=j;
  }
  // for(int i=0;i<n;i++)
  // {
  //   cout<<hmat[0]<<endl;
  // }
  return hmat;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  //cout<<"01"<<endl;
  int pattern_length=pattern.length();
  int text_length=text.length();
  int text_ind=0;
  while(text_ind<text_length)
  { 
    //cout<<"02"<<endl;
    int pattern_ind=0;
    // int count;
    //cout<<text[text_ind]<<" "<<pattern[pattern_ind]<<endl;
    while(text[text_ind]==pattern[pattern_ind] && pattern_ind<pattern_length)
    { 
      //cout<<"03"<<endl;
      //cout<<text[text_ind]<<" "<<pattern[pattern_ind]<<endl;
      text_ind++;
      pattern_ind++;
    }
    
    if(text_ind+pattern_length>text_length)
    {
      return -1;
    }
    // if(pattern_ind == 0){
    //   text_ind++;
    // }
    if(pattern_ind==pattern_length)
    { 
      //cout<<"hurray"<<endl;
      return text_ind - pattern_length;
    }
    else if(pattern_ind==0)
    { 
      //cout<<"04"<<endl;
      text_ind++;
    }
    else
    { 
      //cout<<"05"<<endl;
      text_ind=text_ind - hMatrix[pattern_ind-1];
    }
  }
}

#endif
