#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int n = pattern.length();
  for (int i = 0; i < n; i++)
  {
    pattern[i] = tolower(pattern[i]);
  }
  
  int *h = new int[n];
  int *h_final = new int[n];

  pattern = pattern.append("$");

  int ptr = 1;
  h[0] = 0;
  int i = ptr - 1;
  while (ptr < n)
  {
    if (i<0)
    {
      h[ptr] = 0;
      ptr++;
      i = ptr -1;
      continue;
    }
    
    else if(pattern[h[i]] == pattern[ptr]){
      h[ptr] = h[i] + 1;
      ptr++;
      i = ptr - 1;
      continue; 
    } 

    else {
      i = h[i] - 1;
    }
  }

  ptr = 1;
  i = ptr;
  h_final[0] = 0;
  
  while (ptr < n)
  {
    if (i < 0)
    {
      h_final[ptr] = 0;
      ptr++;
      i = ptr;
    }

    else if (pattern[h[i]] != pattern[ptr+1]){
      h_final[ptr] = h[i]; 
      ptr++;
      i = ptr;
    }

    else{
      i = h_final[i] -1;
    }

  }
  

  return h_final; 
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
// for matching reviews we will apply kmp algorithm at each node of the JourneyCodeReview to match the given pattern 
// and then print the string of the node which has a match
  int ptr = 0;

  while (ptr < text.length())
  {
    for (int i = 0; i < pattern.length(); i++)
    {
      if (pattern[i] == tolower(text[ptr]))
      {
        ptr++;
        if (i == pattern.length() -1)
        {
          return ptr - pattern.length();
        }
      }

      else{
        if (i == 0)
        {
          ptr += 1; 
          break;
        }
        
        ptr = ptr + i - hMatrix[i-1];
        break;
       
      } 
    }
     
  }
  
  return -1;
}

#endif
