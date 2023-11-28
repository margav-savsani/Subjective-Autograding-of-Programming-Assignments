#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
    int *H;
    H= new int[pattern.length()];
    H[0]=0;
    int len = 0;
    int i = 1;
    while (i < pattern.length()) {
        if (pattern[i] == pattern[len]) {
            len++;
            H[i] = len;
            i++;
        }
        else 
        {
            if (len != 0) {
                len = H[len-1];
            }
            else 
            {H[i] = 0;
                  i++;
              }
          }
      }
    return H;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
    int *c=hMatrix;
    int m=pattern.length();
    int n=text.length();
    int i=0;
    int j=0;
    int d;
    while((n-i) >= (m-j)) {
        if(pattern[j]==text[i]) {
          j++;
          i++;
        }
        if(j==m) {
           d=i-j;
           j=c[j-1];
        }
        else if (i<n && pattern[j] != text[i]) {
            if (j!=0)
                j = c[j-1];
            else 
                i++;
        }
    }
    return d;
}

int main()
{
    string a = "ABABDABACDABABCABAB";
    string b = "ABABCABAB";
    return 0;
}
#endif
