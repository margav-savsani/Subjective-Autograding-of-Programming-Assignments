#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
      int len= pattern.length();
      int *array=new int[len];
      array[0]=0;
      for(int i=1;i<len;i++){
          int j=i;
          while(j!=0){
              if(pattern[i]==pattern[array[j-1]]){
                  array[i]=array[j-1]+1;
                  break;
              }
              else{
                  j=array[j-1];
              }
          }
          if(j==0){
              array[i]=0;
          }
      }
      return array;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
    int lt=text.length();
    int lp=pattern.length();
    int i=0;
    int j=0;
    while(i-j<=lt-lp){
        if(text[i]==pattern[j]){
            i++;
            j++;
            if(j==lp){
                return i-j;
            }
        }
        else{
            if(j==0){
                i++;
                continue;
            }
            else if(hMatrix[j-1]==0){
                j=0;
                continue;
            }
            j=hMatrix[j-1];
        }
    }
    return -1;
}

#endif
