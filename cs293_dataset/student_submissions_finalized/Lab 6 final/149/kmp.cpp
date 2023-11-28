#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

/// @brief function for calculating the hMatrix for pattern matching
/// @param pattern pattern whose hmatrix is to be constructed
/// @return the constructed matrix
int *Planner::computeHMatrixForKMP(string pattern)
{
  for (int i = 0; i < pattern.size(); i++)
  {
    pattern[i] = toupper(pattern[i]);
  }
  int n = pattern.length();
  int i = 1, j = 0;
  int h[n];
  h[0] = 0;
  for (i = 1; i < n; i++)
  {
    if (pattern[i] == pattern[j])
      h[i] = j++;
    else
    {
      if (j != 0)
      {
        j = h[j - 1];
        i--;
      }
      else
        h[i] = 0;
    }
  }

  return h;
}

/// @brief find the match for the pattern in the text supplied
/// @param text the text in which the given pattern is to be found
/// @param hMatrix hmatrix of the pattern to be found
/// @param pattern the pattern to be found
/// @return starting index of the pattern in the text
int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  for (int i = 0; i < pattern.size(); i++)
  {
    pattern[i] = toupper(pattern[i]);
  }
  for (int i = 0; i < text.size(); i++)
  {
    text[i] = toupper(text[i]);
  }
  int i = 0, j = 0;
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
    }

    else if (i < text.length() && pattern[j] != text[i])
    {
      if (j != 0)
        j = hMatrix[j - 1];
      else
        i = i + 1;
    }
  }
  return -1;
}

#endif
