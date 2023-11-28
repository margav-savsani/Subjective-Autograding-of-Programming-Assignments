#include <cctype>
#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
    int n = pattern.length();
    int * h = new int[n];
    h[0] = 0;
    int length = 0;
    int i = 1;
    while (i < n)
    {
        if (toupper(pattern[i]) == toupper(pattern[length]))
        {
            length++;
            h[i] = length;
            i++;
            continue;
        }
        if (length == 0)
        {
            h[i] = 0;
            i++;
        }
        if (length != 0) length = h[length - 1];
    }
    return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
    int i = 0, j = 0;
    int m = pattern.length();
    int n = text.length();
    while (n - j >= m - i)
    {
        if (toupper(pattern[i]) == toupper(text[j]))
        {
            i++;
            j++;
        }
        if (i == m)
        {
            return (j - m);
        }
        else if (j < n && toupper(pattern[i]) != toupper(text[j]))
        {
            if (i == 0) j++;
            else i = hMatrix[i - 1];
        } 
    }
    return -1;
}

#endif
