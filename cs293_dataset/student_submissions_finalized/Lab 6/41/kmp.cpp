#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
    int* new_var;
    int length = 0, i = 1;
    new_var[0] = 0;
    int length_of_string = pattern.length();
    
    while (i < length_of_string) {
        if (pattern[i] == pattern[length]) {
            len++;
            new_var[i] = length;
            i++;
        }
        else{
            if (length != 0) length = new_var[length - 1];
            else new_var[i++] = 0;
        }
    }
    return new_var[0];
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
    
    return 0;
}
#endif
