#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;
/*
WE CREATE AN EMPTY ARRAY AND THEN WE MATCH THE PATTERN FROM STARTING OF THE PREFIX IF IT MATCHES WE SHIFT TO THE NEXT ELEMENT AND ASSIGN THAT VALUE TO THE NODE. IF NOT AND SOME ELEMENTS HAVE MATCHED, WE RESTART WITH THE VALUE ASSIGNED TO THE PREVIOUS NODE
IF NO MATCHING AS HAPPENED WE ASSIGN 0 AND MOVE TO NEXT ELEMENT WHICH STARTS MATCHING FROM 1ST ELEMENT
*/
int *Planner::computeHMatrixForKMP(string pattern) {
  int len = 0;
  int pleng=pattern.length();
  int *lps;
  lps= new int[pleng];
    lps[0] = 0; // lps[0] is always 0
 
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < pleng) {
        if (toupper(pattern[i]) == toupper(pattern[len])) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0) {
                len = lps[len - 1];
 
                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }

  return lps;
}
/*
WE MATCH THE PATTERN AND TEXT, IF THEY DONT MATCH WE USE THE HMATRIX TO FIND THE NEXT LOCATION OF THE ARRAY. IF WE ARE MATCHING THE FIRST ELEMENT OF THE ARRAY WE JUST SHIFT TO NEXT ELEMENT OF THE TEXT AND KEEP MATCHING.
*/
int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
 int M = pattern.length();
  int N = text.length();
 
    // create lps[] that will hold the longest prefix suffix
    // values for pattern
 
    // Preprocess the pattern (calculate lps[] array)
 
    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while ((N - i) >= (M - j)) {
        if (toupper(pattern[j]) == toupper(text[i])) {
            j++;
            i++;
        }
 
        if (j == M) {
            return (i - j);
        }
 
        // mismatch after j matches
        else if (i < N && toupper(pattern[j]) != toupper(text[i])) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = hMatrix[j - 1];
            else
                i = i + 1;
        }
    }
  return -1;
}

#endif
