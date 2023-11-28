#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
    int len = pattern.size();
    int* h = new int[len];
    // for(int i=0; i<len; i++){
    //     h[i]=i;
    // }

    h[0] = 0;
    for(int i=1; i<len; i++){
        int k = h[i-1];
        while(k>0){
            if(pattern[i]==pattern[k]){
                h[i]=k+1;
                break;
            }
            else{
                k = h[k-1];
            }
        }
        if(k==0){
            if(pattern[i]==pattern[0]){
                h[i] = 1;
            }
            else{
                h[i] = 0;
            }
        }
        // cout << pattern[i] << " " << i << " " << h[i] << "\n";
    }

    // for(int i=0; i<len; i++){
    //     cout << h[i] << " ";
    // }
    // cout << "\n";
    return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
    int lenpattern = pattern.size();
    int lentext = text.size();
    int i=0;
    while(i<=lentext-lenpattern){
        bool found = 1;
        int jump;
        for(int j=0; j<lenpattern; j++){
            if(pattern[j] != text[i+j]){
                found = 0;
                jump = j-hMatrix[j]+1;
                break;
            }
        }
        if(found) return i;
        i += jump;
    }
    return -1;
}

#endif
