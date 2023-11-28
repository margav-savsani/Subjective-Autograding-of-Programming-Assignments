#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

//creates the hmatrix(as described in lectures) for a given pattern
int *Planner::computeHMatrixForKMP(string pattern)
{   //length of the pattern
    int M = pattern.length();
    // length of the previous longest prefix suffix
    int len = 0;
    //creation of the hmatrix
    int *hmatrix = new int[M];

    hmatrix[0] = 0; // hmatrix[0] is always 0

    // the loop calculates hmatrix[i] for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            hmatrix[i] = len;
            i++;
        }
        else // (pattern[i] != pattern[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0)
            {
                len = hmatrix[len - 1];

                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                hmatrix[i] = 0;
                i++;
            }
        }
    }
    return hmatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) //returns the first occurence of a pattern in a text
{
    int M = pattern.length();
    int N = text.length();

    int i = 0; // index for text[]
    int j = 0; // index for pattern[]
    while ((N - i) >= (M - j))
    {
        if (pattern[j] == text[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            int index = i - j;
            return index;
            j = hMatrix[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pattern[j] != text[i])
        {
            // Do not match hMatrix[0..hMatrix[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = hMatrix[j - 1];
            else
                i = i + 1;
        }
    }

    return -1; //return -1 if no match found
}

#endif
