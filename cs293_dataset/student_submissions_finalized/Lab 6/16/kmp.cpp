#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  int *lps = new int[pattern.length()];
  // length of the previous longest prefix suffix
  int len = 0;

  lps[0] = 0; // lps[0] is always 0

  // the loop calculates lps[i] for i = 1 to M-1
  int i = 1;
  while (i < pattern.length())
  {
    if (pattern[i] == pattern[len])
    {
      len++;
      lps[i] = len;
      i++;
    }
    else // (pat[i] != pat[len])
    {
      // This is tricky. Consider the example.
      // AAACAAAA and i = 7. The idea is similar
      // to search step.
      if (len != 0)
      {
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
  // return nullptr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  int i = 0; // index for text
  int j = 0; // index for pattern
  while ((text.length() - i) >= (pattern.length() - j))
  {
    if (pattern[j] == text[i])
    {
      j++;
      i++;
    }

    if (j == pattern.length())
    {
      return i - j;
      // printf("Found pattern at index %d ", i - j);
      j = hMatrix[j - 1];
    }

    // mismatch after j matches
    else if (i < text.length() && pattern[j] != text[i])
    {
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
