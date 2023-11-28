#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {  // What is HMatrix.
    
    int len = pattern.length();
    
    int *hMatrix;
    hMatrix = new int[len];
    
//    for(int i = 0; i < len; i++){
        int j = 0;
//        if(i == 0){
//            hMatrix[i] == i;
//        }
//        else{
    while(j < len){
        int k = 0;
        while(k < len){
            if(k+j < len){
                if(pattern[k] != pattern[k+j]){  // k is i-j+1
                    if((k == 0) && (j == 0)){
                        hMatrix[0] = 0;
                    }
                    else if(k == 0){
                        hMatrix[j-1] = hMatrix[j];
                    }
                    else if(k+j+1 < len){
                        if(pattern[k-1] == pattern[k+j+1]){
                            hMatrix[k+j-1] = j;
                        }
                    }
                }
                k++;
            }
        }
        j++;
    }
//        }
//    }
    
    for(int i=1; i < len; i++){
        if(hMatrix[i] == 0){
            hMatrix[i] = i;
        }
    }
    
    return hMatrix;

  return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
    
    int l1 = text.length();
    int l2 = pattern.length();
    
    
    int i = 0;
    int j = 0;
    
    while(i < l1){
        if(text[i] == pattern[j]){
            i++;
            j++;
        }
        else{
            if(j != 0){
                j = hMatrix[j-1];
            }
            else{
                i++;
            }
        }
        if(j ==  l2){
            j = hMatrix[j-1];
        }
    }

  return 0;
}

#endif
