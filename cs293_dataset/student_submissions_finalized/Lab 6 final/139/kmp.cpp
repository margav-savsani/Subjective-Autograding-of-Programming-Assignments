#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  int *h = new int[pattern.length()];
  h[0] = 0;
  int i = 1, length = 0;
  while (i < pattern.length())
  {
    if (pattern.at(i) == pattern.at(length))
    {
      length++;
      h[i] = length;
      i++;
    }
    else
    {
      // tricky step, try to understand by taking an example

      if (length != 0)
      {
        length = h[length - 1];

        // Also, note that we do not increment i here
      }
      else // if (length == 0)
      {
        h[i] = 0;
        i++;
      }
    }
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  int count = 0; // count of occurences
  int text_length = text.length(), pattern_length = pattern.length();
  int i = 0; // index for text
  int j = 0; // index for pattern
  while ((text_length - i) >= (pattern_length - j))
  {
    if (pattern.at(j) == text.at(i))
    {
      j++;
      i++;
    }

    if (j == pattern_length)
    {
      //returning first found index if found
      return i - j;
      j = hMatrix[j - 1];
    }

    // mismatching after j matches
    else if (i < text_length && pattern.at(j) != text.at(i))
    {
      // Do not match hMatrix[0..hMatrix[j-1]] characters,
      // they will match anyway
      if (j != 0)
        j = hMatrix[j - 1];
      else
        i = i + 1;
    }
  }
  // returning negative value if not found
  return -1;
}

#endif
