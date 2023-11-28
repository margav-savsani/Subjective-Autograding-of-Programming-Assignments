#ifndef KMP_CPP
#define KMP_CPP

#include <algorithm>

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{   
    // converting whole pattern to upper case
    transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper);

    // prefix function
	int* h = new int[pattern.length()];

    // always equal to 0
    h[0] = 0;

    int prev = h[0];
    
    // creating prefix function
    for(int i=1; i<pattern.length(); ++i){

        prev = h[i-1];

        while(true){

            if(prev == 0){
                if(pattern[prev] == pattern[i]){
                    h[i] = 1;
                    break;
                }
                else{
                    h[i] = 0;
                    break;
                }
            }
            else{
                if(pattern[prev] == pattern[i]){
                    h[i] = prev + 1;
                    break;
                }
                else{
                    prev = h[prev - 1];
                }
            }
        }
    }
    // what we did now is calculate the "prefix function"

    // now we will obtain "failure function" from "prefix function"

    // survival function
	int *h_prime = new int[pattern.length()];

    for(int i=0; i<pattern.length(); ++i){
        if(h[i] == 0){
            h_prime[i] = 0;
        }
        else if(h[i] != 0 && pattern[h[i]+1]==pattern[i+1]){
            h_prime[i] = h_prime[h[i]];
        }
        else if(h[i] != 0 && pattern[h[i]+1]!=pattern[i+1]){
            h_prime[i] = h[i];
        }
    }
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
    // converting whole text and pattern to upper case
    transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper);
    transform(text.begin(), text.end(), text.begin(), ::toupper);

    int M = pattern.length();
    int N = text.length();
 
    // creating an array to hold failure function (H-Matrix)
    int *lps = computeHMatrixForKMP(pattern);
 
     // index for text
    int i = 0;

    // index for patttern
    int j = 0; 

    
    while ((N - i) >= (M - j)) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
 
        if (j == M) {
            return i-j;
            j = lps[j - 1];
        }
 
        // mismatch after j matches
        else if (i < N && pattern[j] != text[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }

    return -1;
}

#endif
