#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int compare(const char* str1,const char* str2){
  strcmp(str1,str2);
}

int *Planner::computeHMatrixForKMP(string pattern) {
  int* p;
  int length=pattern.length();
  for(int j=0;j<length;j++){
    for(int i=length-1;i>0;i--){
      const char *str1 = pattern.substr(0,i).c_str();
      const char *str2 = pattern.substr(j-i-1,i).c_str();
      if(strcmp(str1,str2)==0){
        p[j]=i;
      }
    }
  }
  return p;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  return 0;
}

#endif
