#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

int* Planner::computeHMatrixForKMP(std::string pattern)
{
    int* HMatrix = new int[pattern.length()];
    // length of the previous longest prefix suffix
    int len = 0;
 
    HMatrix[0] = 0; // HMatrix[0] is always 0
 
    for (int i = 1; i < pattern.length();) {
        if (pattern[i] == pattern[len]) {
            len++;
            HMatrix[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = HMatrix[len - 1];
            }
            else {
                HMatrix[i] = 0;
                i++;
            }
        }
    }
    return HMatrix;
}

int Planner::KMPMatch(std::string text, int* HMatrix, std::string pattern)
{
    int i = 0; // index for text
    int j = 0; // index for pattern
    
    // int matches = 0;

    while (text.length() + j >= pattern.length() + i) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == pattern.length()) {
            return (i - j);
            // matches++;
            // j = HMatrix[j - 1];
        }

        // mismatch after j matches
        else if (i < text.length() && pattern[j] != text[i]) {
            if (j != 0)
                j = HMatrix[j - 1];
            else
                i++;
        }
    }
    return -1;
}

int* computeHMatrixForInsensitiveKMP(std::string pattern)
{
    for (int i = 0; i < pattern.length(); i++)
        pattern[i] = toupper(pattern[i]);
    int* HMatrix = new int[pattern.length()];
    // length of the previous longest prefix suffix
    int len = 0;

    HMatrix[0] = 0; // HMatrix[0] is always 0

    for (int i = 1; i < pattern.length();) {
        if (pattern[i] == pattern[len]) {
            len++;
            HMatrix[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = HMatrix[len - 1];
            }
            else {
                HMatrix[i] = 0;
                i++;
            }
        }
    }
    return HMatrix;
}

int InsensitiveKMPMatch(std::string text, int* HMatrix, std::string pattern)
{
    for (int i = 0; i < pattern.length(); i++)
        pattern[i] = toupper(pattern[i]);
    for (int i = 0; i < text.length(); i++)
        text[i] = toupper(text[i]);
    int i = 0; // index for text
    int j = 0; // index for pattern

    // int matches = 0;

    while (text.length() + j >= pattern.length() + i) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == pattern.length()) {
            return (i - j);
            // matches++;
            // j = HMatrix[j - 1];
        }

        // mismatch after j matches
        else if (i < text.length() && pattern[j] != text[i]) {
            if (j != 0)
                j = HMatrix[j - 1];
            else
                i++;
        }
    }
    return -1;
}

#endif
