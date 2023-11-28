#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
    transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower); // case insensitive
    int *arr = new int[pattern.length()];
    arr[0] = 0;
    int q = 0;
    for (int i = 1; i < pattern.length(); i++) {
            while((pattern[q] != pattern[i] || (q+1 < pattern.length() && pattern[q+1] == pattern[i+1])) && q>0){
                q = arr[q];
            }
            if(pattern[q] == pattern[i] && i>1){
                q = q+1;
            }
            arr[i] = q;
        
    }

  return arr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
    transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower); //Making it case insensitive
    transform(text.begin(),text.end(),text.begin(), ::tolower); 
    int q = 0; // No of chars that match
    for (int i = 0; i<text.length(); i++){
            char c = text[i];
            /* cout << i << " " << q  << endl; */
            while(c != pattern[q] && q > 0){
                    q = hMatrix[q];
            }
            if(c == pattern[q]){
                q+=1;
            }
            if(q == pattern.length()){
    
                return i-pattern.length()+1; 
            }
    }
  return -1;
}

#endif
