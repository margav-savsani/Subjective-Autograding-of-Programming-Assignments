#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
    int i=1;
    int len = 0;
    int length=pattern.length();
    int* lps=new int[length];
    lps[0] = -1;   
    while (i < length){
        if (pattern[i] == pattern[len]) {
            
            lps[i] = lps[len];
            i++;
            len++;
        }
        else{
            lps[i]=len;
            while (len>=0 && pattern[i]!=pattern[len]){
                len=lps[len];
            }
            i++;
            len++;
        }
    }
    lps[i]=len;
    return lps;
}

int Planner::KMPMatch(string text, int *hMatrix, string patterntern) {
    int tlen=text.length();
    int current =0;
    
    for(int i=0;i<tlen;i++){
        if(patterntern[current]==text[i]){
            if(current==patterntern.length()-1){
                return i-current;
            }
            else{
                current++;
            }
        }
        else{
            
            while(current>=0 && text[current]!=patterntern[i]){
                current=hMatrix[current];
            }
            current++;
        }
    }
    return -1;
}

#endif

