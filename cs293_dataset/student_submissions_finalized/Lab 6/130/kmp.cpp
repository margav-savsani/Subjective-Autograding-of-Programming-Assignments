#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
    int* arr = new int[pattern.length()];
    for (int i = 0; i < pattern.length(); ++i)
    {
        /* to be completed */
    }
    return arr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
    /* TBD */
    return 0;
}

#endif
