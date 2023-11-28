#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  //the following ine converts text to uppercase.
  transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper);
  int len = pattern.length();
  int *hMatrix = new int[len];
  //the first letter has the hMatrix value 0.
  hMatrix[0] = 0;
  //the length of the matched string
  int match_len = 0;
  int index = 1;
  while (index < pattern.length())
  {
    if (pattern[index] != pattern[match_len])
    {
      if (match_len == 0)
      {
        hMatrix[index] = 0;
        index++;
      }
      else
      {
        match_len = hMatrix[match_len - 1];
      }
    }
    else
    {
      match_len++;
      hMatrix[index] = match_len;
      index++;
    }
  }
  return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  //the below 2 lines converts the text and pattern to uppercase.
  transform(text.begin(), text.end(), text.begin(), ::toupper);
  transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper);
  int patternlen = pattern.length();
  int textlen = text.length();
  //i is the index of the current text index which is going to be matched with pattern
  int i = 0;
  //i is the index of the current pattern index which is going to be matched with text

  int j = 0;
  int index = -1;
  while (textlen - j >= patternlen - i)
  {
    if (text[j] != pattern[i])
    {
      if (i == 0)
      {
        j++;
      }
      else
      {
        i = hMatrix[i - 1];
      }
    }
    else if (text[j] == pattern[i])
    {
      j++;
      i++;
      //the whole pattern matched the text.
      if (i == patternlen)
      {
        if (index == -1)
        {
          //here the whole pattern matches and index is the the the index of the text at which first word of the pattern and text matched.
          index = j - i; 
        }
        i = hMatrix[i - 1];
      }
    }
  }
  return index;
}
#endif