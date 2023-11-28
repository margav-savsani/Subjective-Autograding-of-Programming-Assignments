#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int longest(string substring){ //this fucntion gives the length of the longest prefix that is also a proper suffix of the string substring
    int length = substring.length();
    string p = substring.substr(0,length-1); //first proper prefix
    string q = substring.substr(1,length); //longest proper suffix
    while(p.length()!=0){
        if(p==q) return p.length(); //if match, return
        p = p.substr(0,p.length()-1); //if no match, decrease length of prefix and suffix
        q = q.substr(1,q.length());
    }
    return 0;
}

int *Planner::computeHMatrixForKMP(string pattern) { //this function gives the failure matrix of the string pattern
  int l_pattern = pattern.length();
    int *hmatrix;
    hmatrix = new int[l_pattern];
    hmatrix[0]=0;
    for(int i=1; i<l_pattern; i++){
        hmatrix[i] = longest(pattern.substr(0,i+1)); //failure function is basically the length of longest prefix that is also a proper suffix
    }
    return hmatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int l_text = text.length();
    int l_pattern = pattern.length();
    int p=0;
    int q=0;
    while((p-q)<=(l_text-l_pattern)){
        if(p>=l_text || q>= l_pattern) break;
        if(pattern[q]==text[p]){ //if match, go ahead
            p++;
            q++;
        }
        if(q==l_pattern) { //this is the case when the pattern is found in the text
            int i = p-q;
            return i;
        }
        if(pattern[q]!=text[p]){ //this is case when there is a mismatch
            if (q == 0) p++; //if the pattern is at its starting index, then we shift the index of text
            else q = hMatrix[q-1]; //if pattern is not at its starting index, then we shift the index of pattern
        }
    }
    return -1;
}

#endif
