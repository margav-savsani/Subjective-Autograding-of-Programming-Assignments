#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
    int patlen = pattern.length();
    //length
    int *H = new int [patlen];
    //creating array we are supposed to return
    H[0] = -1;
    //Default value of H[0]
    

    for (int i = 1; i < patlen; i++)
    //loop where each iteration is for each element of H
    {
        if (i == 1) H[i] = 0;
        else
        {
            int a = i-1;
            while ((pattern[i] != pattern[H[a]]) && (a > 0)) a = H[a];
            H[i] = H[a] + 1;
        }
    }

    return H;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
    int M = pattern.length();
    int N = text.length();
    int shift;//defining shift

    for (int j = 0; j <= N-M; j = j + shift)
    //going throuh text
    {
        int a = j;
        for (int i = 0; i < M; i++)
        //going through pattern
        {
            if (text[a] == pattern[i]) 
            {
                if (i == M-1) return j;
                a++;
            }
            else 
            {
                shift = i - hMatrix[i];
                //giving value to shift
                break;
            }
        }
    }
    return -1;
}

#endif
