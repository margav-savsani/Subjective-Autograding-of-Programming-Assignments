#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
    int Len = pattern.length();

    if (Len == 0)
    {
        return nullptr;
    }
    else 
    {
        int *H;
        H = new int[Len];
        return H;
    }
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{

    return 0;
}

#endif
