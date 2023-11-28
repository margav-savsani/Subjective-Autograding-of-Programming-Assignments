#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

  int l=0;
  int *hMatrix;
  int n=pattern.length();
  hMatrix=new int[n];
  hMatrix[0]=0;
  int i=1;
    while (i<n) {
        if (pattern[i] == pattern[l]) {
            l++;
            hMatrix[i] = l;
            i++;
        }
        else 
        {
            if (l!= 0) {
                l = hMatrix[l-1];
                }
            else
            {
                hMatrix[i] = 0;
                i++;
            }
        }
    }
  return hMatrix;
}
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

   int pat = pattern.length();
   int size= text.length();
  
   int i = 0; 
   int j = 0; 
   while (i<size) {
     if (pattern[j] == text[i]) {
         j++;
         i++;
         }
       
      else {
                if (j!=0){
                j=hMatrix[j-1];
                }
             else{
                i=i+1;
                }
         }

         if (j == pat) {
             return i-j;
         }
     }
return -1;
 }

#endif
