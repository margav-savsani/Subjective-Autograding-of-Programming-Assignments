#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
    int *hmatrix=new int[pattern.length()+1];
    int l= pattern.length()+1;
    hmatrix[0]=0;
    hmatrix[1]=0;
    int h=0;
    for (int i=2; i<l; i++){
        while(true){
            if(pattern[i-1]==pattern[h]){
                hmatrix[i]=h+1;
                h=hmatrix[i];
                break;
            }
            else{
                h=hmatrix[h];
            }
            if(h==0){
                hmatrix[i]=0;
                break;
            }
        }
    }
    return hmatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
    hMatrix=computeHMatrixForKMP(pattern);
    int index=-1;
    int KMP=0;
    int k=0;
    for(int i=0; i<=text.length(); i++, k++){
        if(k==pattern.length()){
            KMP++;
            index=i-pattern.length();
            k=hMatrix[k];
        }
        else if(i==text.length()){
            break;
        }
        else if(text[i]!=pattern[k]){
            k=hMatrix[k];
        }
    }
    return index;
}

#endif
