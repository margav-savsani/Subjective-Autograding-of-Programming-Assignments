#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#include <string>
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
    int index = 0;
    int z=pattern.length();
    int *H_matrix=new int(z);
    H_matrix[0] = 0; 
    int i = 1;
    while (i < z) {
        if (pattern[i] == pattern[index]) {
            index++;
            H_matrix[i] = index;
            i++;
        }
        else {
            if (index != 0) {
                index = H_matrix[index - 1];
            }
            else{
                H_matrix[i] = 0;
                i++;
            }
        }
    }
  return H_matrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
    int len_1 = pattern.length();
    int len_2 = text.length();
    int* a=hMatrix;
    int i = 0;
    int j = 0;
    while ((len_2 - i) >= (len_1 - j)) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
        if (j == len_1) {
            return i-j;
            j = a[j - 1];
        }
        else if (i < len_2 && pattern[j] != text[i]) {
            if (j != 0)
                j = a[j - 1];
            else
                i = i + 1;
        }
    }
  return -1;
}

#endif
