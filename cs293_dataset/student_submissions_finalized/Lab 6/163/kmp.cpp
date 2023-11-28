#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
    int len = pattern.length();
    int *hMatrix = new int[len];
    hMatrix[0] = 0;
    for (int i = 1; i < len; i++)
    {
        hMatrix[i] = 0;
        while (hMatrix[i] >= 0)
        {
            while (pattern[i - 1] != pattern[hMatrix[i - 1] - hMatrix[i]])
                hMatrix[i]++;
            for (int j = hMatrix[i - 1]; j >= 0; j--)
            {
                if (pattern[i + j - hMatrix[i - 1] - 1] != pattern[j])
                {
                    hMatrix[i]++;
                    break;
                }
            }
        }
    }

    return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{

    return 0;
}

#endif
