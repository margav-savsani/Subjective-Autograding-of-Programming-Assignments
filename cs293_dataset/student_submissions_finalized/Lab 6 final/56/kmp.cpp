#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int* Planner::computeHMatrixForKMP(string pattern) {  //computes the h matrix, (inclusive of the curent index while calculating suffixes)

    int len = pattern.size();
    int* h = new int[len];
    if(len == 0){
        return nullptr;
    }
    h[0] = 0;   //trivial case, no proper suffix
    int k = 0;
    for(int i = 1; i < len; i++){  //calculating h values for indices > 0
        while(k > 0 && tolower(pattern[k]) != tolower(pattern[i])){  //characters don't match, reverst to a previous h value
            k = h[k-1];
        }
        if(tolower(pattern[k]) == tolower(pattern[i])){   //check if the characters match, if yes, check for the next character
            k += 1;
        }
        h[i] = k;
    }
    return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {  //matches pattern and text using kmp

    int patlen = pattern.size();
    int textlen = text.size();
    int q = 0;
    for(int i = 0; i < textlen; i++){  //algorithm similar to kmp, just that this returns index if matched
        while(q > 0 && tolower(pattern[q]) != tolower(text[i])){    
            q = hMatrix[q-1];
        }
        if(tolower(pattern[q]) == tolower(text[i])){
            q += 1;
        }
        if(q == patlen){
            return (i+1 - patlen);
        }
    }
    return -1;
}

#endif
