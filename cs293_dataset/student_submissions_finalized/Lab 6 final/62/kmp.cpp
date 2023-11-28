#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
	int pattlen = pattern.length();
	int* hmatrix = new int[pattlen];
	
    hmatrix[0] = 0;

	// len keeps length of the previous longest <pre-suf>ix
	for (int i=1,len=0; i<pattlen; i++){
        if (toupper(pattern[i]) == toupper(pattern[len])) { //for case insensitivity
            hmatrix[i] = ++len;
        }
        else{ // (pattern[i] neq pattern[len])
            if (len != 0) {
                len = hmatrix[len - 1];
				i--;
                // So i isnt incremented
            }
            else // if (len == 0)
                hmatrix[i] = 0;            
        }
    }
    //Convert prefix function to failure function - ref clrs
    for (int i=0;i<pattlen;i++){
        if (hmatrix[i]!=0){
            if (toupper(pattern[hmatrix[i]+1])==toupper(pattern[i+1]))
                hmatrix[i]=hmatrix[hmatrix[i]];
        }
    }
	return hmatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {//made case insensitive
	int pattlen = pattern.length();
	int textlen = text.length();
	// text[i] and pattern[j]
	for (int i=0,j=0; (textlen-i) >= (pattlen-j); ){
        if (toupper(pattern[j]) == toupper(text[i])) { 
            j++;
			i++;
        }
 
        if (j == pattlen) return (i-j);
 
        // mismatch after j matches
        else if (i < textlen && toupper(pattern[j]) != toupper(text[i])) {
            // no need to match hMatrix[0] to hMatrix[j-1]
            if (j != 0)
                j = hMatrix[j - 1];
            else
                i = i + 1;
        }
    }
	return -1;
}

#endif
