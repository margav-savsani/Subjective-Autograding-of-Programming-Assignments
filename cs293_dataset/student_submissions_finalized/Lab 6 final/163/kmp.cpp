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
    hMatrix[0] = 0;               // Matrix value of 0 would always be 0.
    int curr = 0;                 // The current length to check, that could be the length of matching string at current i.
    for (int i = 1; i < len; i++) // each iteration calculations value of ith index in matrix.
    {
        while (curr >= 0)
        {
            if (pattern[i] == pattern[curr])
            {
                hMatrix[i] = ++curr; // pattern matches, so curr is increased and value is stored in hMatrix
                break;               // h value found for this i, so break
            }
            if (curr != 0)
                curr = hMatrix[curr - 1]; // if pattern doesn't match, we check the previous posible substring.
            if (curr == 0)
            {
                hMatrix[i] = 0; // if curr becomes 0, hMatrix at i must have value 0
                break;
            }
        }
    }
    return hMatrix; // hMatrix is returned
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
    int p_len = pattern.length(), p_index = 0; // p_index is the current index of pattern to match
    int t_len = text.length(), t_index = 0;    // t_index is the current index of text to match
    while (t_len - t_index >= p_len - p_index) // matching possiblity only when remaining text length is not less than remaining pattern length
    {
        if (text[t_index] == pattern[p_index]) // current index match
        {
            t_index++;
            p_index++;            // both indices increased
            if (p_index == p_len) // whole pattern has been matched
            {
                // Match found at index t_index-p_index in th text.
                // if we don't return and end function here, all occurences of pattern would be found here.
                return t_index - p_index;
                p_index = hMatrix[p_len - 1]; // p_index set to previous possible substring length
            }
            else if (t_index == t_len)
            {
                break; // Search Complete.
            }
        }
        else
        {
            if (p_index == 0)
                t_index++; // in this case, the 0th index of pattern didn't match, so no match for given t_index, so increase it
            else
                p_index = hMatrix[p_index - 1]; // else set p_index to previous possible value.
        }
    }
    return -1; // if not found, return -1
}

#endif
