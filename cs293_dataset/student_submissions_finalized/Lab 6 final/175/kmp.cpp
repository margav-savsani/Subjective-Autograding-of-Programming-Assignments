#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern){ //computes h matrix in linear time
    int *h = new int[pattern.size()];
    bool found = true;
    h[0] = 0; //base case
    for (int i = 1; i < pattern.size(); i++){
        int pos = h[i - 1];
        while (pattern[pos] != pattern[i]){ // check the last char of the longest prefix for the prev index
            if (pos > 0){
                pos = h[pos - 1];
            }
            else{ // this is to check an edge case, if consecutive zeros appear in h matrix
                h[i] = 0;
                found = false;
                break;
            }
        }
        if (found){
            h[i] = pos + 1;
        }
        else{
            found = true;
        }
    }
    return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern){
    for (int i = 0; i < text.size(); i++){
        text[i] = toupper(text[i]);
    }
    for (int i = 0; i < pattern.size(); i++){
        pattern[i] = toupper(pattern[i]);
    }
    hMatrix = computeHMatrixForKMP(pattern);
    int pos = 0, id = 0;
    while (pos < text.size()){
        if (text[pos] == pattern[id]){ // if a char of pattern matches then go to next location
            pos ++;
            id ++;
            if (id == pattern.size()){ // complete match
                return pos - pattern.size();
            }
        }
        else{
            if (id != 0){
                id -= (id - hMatrix[id - 1]); // else the shift the pattern acc to h matrix values
            }
            else{
                pos ++;
            }
        }
    }
    return -1; // if no match found
}

#endif
