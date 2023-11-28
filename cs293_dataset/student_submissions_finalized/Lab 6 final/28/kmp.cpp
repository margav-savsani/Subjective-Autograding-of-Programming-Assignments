#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#include<vector>
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {

    // length of the previous longest prefix suffix
    int len = 0;

    for(int i=0;i<pattern.size();i++){
        pattern[i]=toupper(pattern[i]);  //For making the KMP searching case insensitive
    }
 
    int *lps=new int[pattern.size()]; // lps[0] is always 0
    lps[0]=0;
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < pattern.size()) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            
            if (len != 0) {
                len = lps[len - 1];
 
              
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }

  return lps;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

    for(int i=0;i<pattern.size();i++){   //For making the KMP searching case insensitive
        pattern[i]=toupper(pattern[i]);
    }
    for(int i=0;i<text.size();i++){  //For making the KMP searching case insensitive
        text[i]=toupper(text[i]);
    }
    int n = text.length();
    int m = pattern.length();
    
    //lps_func(pattern,Lps); // This function constructs the Lps array.
    
    
    int i=0,j=0;
    while(i<n){
        if(pattern[j]==text[i]){i++;j++;} // If there is a match continue.
        if (j == m) { 
            
            return (i-m);                     // and update j as Lps of last matched character.
            j = hMatrix[j - 1]; 
        } 
        else if (i < n && pattern[j] != text[i]) {  // If there is a mismatch
            if (j == 0)          // if j becomes 0 then simply increment the index i
                i++;
            else
                j = hMatrix[j - 1];  //Update j as Lps of last matched character
        }
}return -1;}

#endif
