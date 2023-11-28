#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  int *match = new int[pattern.length()]; // match array initialising
  int len = 0;                            // intial length
  int l = pattern.length();               // total length
  match[0] = 0;                           // first is always 0
  int i = 1;
  while (i < l) // less than total length
  {
    if (pattern[i] == pattern[len]) // pattern match continues
    {
      len++;          // increasing pattern similarity length
      match[i] = len; // updating array
      i++;            // moving to next point
    }
    else
    {
      if (len != 0) // if pattern doesnt continue to match and there is some common pattern before
      {
        len = match[len - 1]; // pattern's common pattern with previous patterns
      }
      else
      {
        match[i] = 0; // if no match for previous elements
        i++;          // moing forward
      }
    }
  }
  return match;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  int T = text.length();    // text length
  int P = pattern.length(); // pattern length
  int i = 0;
  int j = 0;
  while (T - i >= P - j) // text left to search is more than pattern left to be searched
  {
    if (pattern[j] == text[i]||toupper(pattern[j])==toupper(text[i])) // pattern match letter by letter
    {
      i++;
      j++;
    }
    if (j == P) // if complete match
    {
      return i - j; // index of start
    }
    else if (i < T && !(pattern[j] == text[i]||toupper(pattern[j])==toupper(text[i]))) // if patterns arent matching
    {
      if (j != 0) // if already searched in pattern
      {
        j = hMatrix[j - 1]; // updating the pattern using hmatrix
      }
      else
      {
        i = i + 1; // if no match initially just move forward
      }
    }
  }
  return -1;
}

#endif
