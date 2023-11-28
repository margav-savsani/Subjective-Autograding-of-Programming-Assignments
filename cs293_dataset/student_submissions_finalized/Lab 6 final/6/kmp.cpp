#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  // length of the previous longest prefix suffix
  int pref = 0;
  int l = pattern.length();
  int* table = new int[l];
  for(int i=0; i<l; i++)
    table[i] = 0; // lps[0] is always 0

  // the loop calculates lps[i] for i = 1 to M-1
  int pat_pos1 = 0;
  int pat_pos2 = 1;
  while (pat_pos2 < l)
  {
    if (toupper(pattern[pat_pos1]) == toupper(pattern[pat_pos2]))
    {
      table[pat_pos2] = pat_pos1 + 1;
      pat_pos2++;
      pat_pos1++;
    }
    else if (pat_pos1 == 0 && toupper(pattern[pat_pos1]) != toupper(pattern[pat_pos2]))
    {
      table[pat_pos2] = 0;
      pat_pos2++;
    }
    else 
    {
     pat_pos1 = table[pat_pos1 - 1];
    }
  }
  return table;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  int t_len = text.length();
  int p_len = pattern.length();
  int text_pos = 0; 
  int pat_pos = 0; 
  while(text_pos < t_len)
  {
    if (toupper(pattern[pat_pos]) == toupper(text[text_pos]))
    {
      if( (pat_pos == p_len - 1))
        return text_pos + 1 - p_len;
      else
      {
        pat_pos++; 
        text_pos++;
      }
    }
    else if(pat_pos == 0 && toupper(pattern[pat_pos]) != toupper(text[text_pos]))
    {
      text_pos++;
    }
    else
      pat_pos = hMatrix[pat_pos-1];

    
  }
  return -1;
  
}
#endif
