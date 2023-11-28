#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern){
    int *h = new int[pattern.size()];
    h[0] = 0;
    for (int i = 1; i < pattern.size(); i++){
        int pos = h[i - 1];
        if (pos == 0 && pattern[pos] != pattern[i]){
            h[i] = 0;
            continue;
        }
        while (pattern[pos] != pattern[i]){
            pos = h[pos - 1];
        }
        h[i] = pos + 1;
    }
    return h;
}

int Planner::KMPMatch(string text, int *h, string pattern){
    h = computeHMatrixForKMP(pattern);
    int pos = 0, id = 0;
    while (pos < text.size()){
        if (text[pos] == pattern[id]){
            pos ++;
            id ++;
            if (id == pattern.size()){
                return pos - pattern.size();
            }
        }
        else{
            if (id != 0){
                id -= (id - h[id - 1]);
            }
            else{
                pos ++;
            }
        }
    }
    return -1;
}

#endif
