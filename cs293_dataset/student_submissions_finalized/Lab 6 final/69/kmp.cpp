#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner :: computeHMatrixForKMP(string pattern){
    int len = pattern.length();
    if(len == 0){
        return nullptr;
    }
    else{
        int* M = new int(len);
        for(int i=0; i<len; i++){
            M[i] = 0;
        }
        for(int i=1; i<len; i++){
            int j = M[i-1];
            while(j>0 && pattern[i]!=pattern[j]){
                j = M[j-1];
            }
            if(pattern[i]==pattern[j]){
                j++;
            }
            M[i] = M[j];
        }
        return M;
    }
}

int Planner :: KMPMatch(string text, int *hMatrix, string pattern){
    int pos = -1;
    int i, j;
    i = 0;
    j = 0;
    while(i<text.length()){
        if(text[i]==pattern[j]){
            i++;
            j++;
        }
        else{
            if(j!=0){
                j = hMatrix[j-1];
            }
            else{
                i++;
            }
        }
        if(j==pattern.length()){
            pos = i-pattern.length();
            break;
        }
    }
    return pos;
}

#endif
