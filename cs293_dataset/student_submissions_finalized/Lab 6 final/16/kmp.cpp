#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#include <string>
#include <algorithm>

using namespace std;

// function to find the hMatrix
int *Planner::computeHMatrixForKMP(string pattern)
{
  // Done to make KMP CASE INSENSITIVE, converts string to uppercase
  transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper);

  // initialising the variables
  int pattern_length = pattern.length();
  int *hMatrix = new int[pattern_length];

  // length of the previous longest prefix suffix
  int match = 0;

  // hMatrix[0] is always 0
  hMatrix[0] = 0;

  // the loop calculates hMatrix[i] for i = 1 to pattern_length-1
  int i = 1;
  while (true)
  {
    // For the case when the prefix length is being increased
    if (i < pattern_length && pattern[i] == pattern[match])
    {
      match++;
      hMatrix[i] = match;
      i += 1;
    }
    // either end of pattern or prefix unmatched condition encountered
    else
    {
      // If entire pattern  has been parsed through
      if (i >= pattern_length)
      {
        break;
      }

      // If unmatched condition is to be handled
      if (match != 0)
      {
        match = hMatrix[match - 1];
      }
      else
      {
        hMatrix[i] = 0;
        i += 1;
      }
    }
  }
  // returning the computed final hMatrix
  return hMatrix;
}

// Function to implement the KMP Match algorithm
int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  // Done to make KMP CASE INSENSITIVE by making text and pattern uppercase
  transform(text.begin(), text.end(), text.begin(), ::toupper);
  transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper);

  // initialising the variables
  int pattern_length = pattern.length(), text_length = text.length();

  // index for text and pattern respectively
  int i = 0, j = 0;

  // Loop runs as long as length of remaining characters of text is
  // greater than the pattern's length as in this case, no further match is
  // possible.
  while ((text_length - i) >= (pattern_length - j))
  {
    // Checking for match between characters
    if (pattern[j] == text[i])
    {
      i += 1;
      j += 1;
    }

    // To check if entire pattern has been matched or not
    if (j == pattern_length)
    {
      int k = i - j;
      return k;
    }

    // mismatch after j matches
    else if (i < text_length && pattern[j] != text[i])
    {
      // Do not match hMatrix[0..hMatrix[j-1]] characters, they will match anyway
      // Shifting the hMatrix based on KMP algorithm
      (j != 0) ? j = hMatrix[j - 1] : i += 1;
    }
  }
  // Returns -1 if match is not found, else index of matched location is
  // returned
  return -1;
}

#endif