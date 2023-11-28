#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern){
    int* h = new int[pattern.size()];
    // h is the array that stores for every index i in the pattern, the length of the longest proper 
    // suffix of P[1..i] that matches a prefix of P
    // Thus if there is a mismatch at i+1, we can simply move to the beginning of this proper suffix
    // instead of moving only by one element
    // To do this, we run the KMP algorithm on the text which is pattern, but first character is $
    string text;
    copy(pattern.begin(), pattern.end(), text.begin());
    text[0] = '$';
    h[0] = 0;
    int start = 1;
    int index = 0;
    for (int i=0; i<pattern.size()-1; i++) {
        if (pattern[index]==text[i+1]){
            h[i+1] = h[i] + 1;
            index++;
        }
        else {
            if (h[i]==0){
                start++;
                h[i+1] = 0;
                continue;
            }
            // Current match is h(i)
            while (pattern[index]!=text[i+1]){
                start += h[i] - h[h[i]];
                index = h[h[i]];
            }
            h[i+1] = index-start + 1;
        }
    }
    return h;

}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
    int *h = computeHMatrixForKMP(pattern);
    int pattern_index = 0;
    for (int i=0; i<pattern.size(); i++) {
        if (pattern[i-pattern_index]==text[i]){
            continue;
        }
        else {
            pattern_index += h[i-pattern_index];
        }
    }
}

#endif
