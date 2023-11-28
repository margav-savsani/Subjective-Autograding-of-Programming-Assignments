#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
    for (int i = 0; i < pattern.length(); i++)
    {
        pattern[i] = toupper(pattern[i]);
    }
    // cout<<pattern<<endl;
    int *h;
    h = new int[pattern.length()]; // This is the hmatrix
    h[0] = 0;
    for (int i = 1; i < pattern.length(); i++)
    {
        int k = h[i - 1];
        while (true)
        {
            // cout << "in while" << endl;

            if (pattern[i] == pattern[k]) // When the elemtnt we are standing on matches the element at k
            {
                // cout<<"c2"<<endl;
                h[i] = k + 1; // h[i] would be k+1
                break;
            }
            if (k == 0) // now the element doesnt even match the element at start so h[i] would be 0
            {
                // cout<<"c1"<<endl;
                h[i] = 0;
                break;
            }
            k = h[k - 1]; // now we again apply kmp for and try to shift the string of length h[k-1]
        }
        // cout<<i<<" "<<h[i]<<endl;
    }
    // cout<<pattern.length()<<" "<<pattern<<endl;
    return h;
}

// it returns the starting point 0 being the first point
int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
    for (int i = 0; i < pattern.length(); i++)
    {
        pattern[i] = toupper(pattern[i]);
    }
    for (int i = 0; i < text.length(); i++)
    {
        text[i] = toupper(text[i]);
    }
    int i_text = 0;    // This would be the index in the text where we are standing. It never decreases.
    int i_pattern = 0; // This would be the index in the pattern where we are standing . It can decrease.
    while (true)
    {
        if (text[i_text] == pattern[i_pattern]) // If we have a match we move forward in both text and pattern
        {
            if (i_pattern == pattern.length() - 1) // if we checked all
            {
                return i_text - i_pattern; // returns the starting point
            }
            i_text++; // if not completed going forward
            i_pattern++;
        }
        else
        {
            if (i_pattern == 0) // we can move forward in this case as we can no longer find that part in text
            {
                i_text++;
            }
            else
            {
                i_pattern = hMatrix[i_pattern - 1]; // we shift the pattern in case when the words do not match
            }
        }
        if (i_text == text.length()) // it we reach the end and couldn't find
        {
            break;
        }
    }
    return -1;
}

#endif
