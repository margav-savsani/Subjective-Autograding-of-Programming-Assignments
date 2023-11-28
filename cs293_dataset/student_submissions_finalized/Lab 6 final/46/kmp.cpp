#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif
#include <vector>
using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
 
    int* h = new int[pattern.length()]; 
	int len = 0; // initial match length is 0
	h[0] = 0;  // base case
	int i = 1;
	while (i < pattern.length()) {
		if (pattern[i] == pattern[len]) { // if the next character in pattern matches 
			len++;
			h[i] = len;
			i++;
		}
		else {
			if (len != 0) {
				len = h[len - 1];	
			}
			else { // no matching pattern found
				h[i] = 0;
				i++;
			}
		}
	}
    return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
    int t_len = text.length();
    int p_len = pattern.length();
    int i=0,j=0;
    // i for the pattern
    // j for the text
    while(text[j]!=pattern[0]) { // finding the first match
            j++;
        }
    while(j<t_len) {
        while(text[j] == pattern[i]) {
            i++;
            j++; // maximum match
			if(j==t_len || i==p_len) break; // reaches the end of text or pattern
        }
        if(j==t_len) break;
        if(i==p_len) {
            return j-i; //find the match
        }
        i = i-hMatrix[i]; // kmp shift
        if(pattern[i]!=text[j]) {
            i=0;
			j++;
        }
    }
  return -1; // not found
}

#endif
