#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  unsigned int len = pattern.length();
  int *hMatrix = new int[len];
  //hMatrix[0] is defined to be 0
  hMatrix[0] = 0;
  for (int i = 1; i < len; i++)
  {
    int j = hMatrix[i - 1];
    while (j > 0 && pattern[i] != pattern[j])
    {
      j = hMatrix[j - 1];
    }
    if (pattern[i] == pattern[j])
    {
  //If there is a match, then h[i] = h[i-1]+1
      j++;
    }
    hMatrix[i] = j;
    
  }
  
  return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  unsigned int lenp = pattern.length();
  unsigned int lent = text.length();
  int pos = -1;
  int j = 0;//iterates pattern
  int i = 0;//iterates text
  while (i < lent)
  {
    // cout << "while" << endl;
    if (text[i] == pattern[j])// if the chars matches both move forward
    {
      i++;
      j++;
    }

    else
    {
      if (j == 0)// if j = 0, then i must
      {
        i++;
      }
      else
      {
        j = hMatrix[j - 1];// moving backwards for searching
      }
    }
    if (j == lenp)
    {
      pos = i - j;// pos of the match

      break;
    }
  }
  return pos;
}

#endif
