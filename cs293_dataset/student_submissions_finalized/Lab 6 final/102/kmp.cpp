#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
  const int lop = pattern.length(); // :: length of pattern
  int *h = new int[lop];
  h[0] = 0;
  for (int i = 1; i < lop; i++)
  {
    int lp, ls;  // :: length of prefix and length of suffix
    lp = ls = i; // :: technically to be equal :: length of prefix has to be equal to length of suffix
    while (lp != 0)
    {
      string prefix = pattern.substr(0, lp);
      string suffix = pattern.substr(i - ls + 1, ls);

      if (prefix == suffix)
      { // :: for comparison of prefix and suffix
        h[i] = prefix.length();
        break;
      }
      else if (lp != 0)
      {
        lp--;
        ls--;
        if (lp == 0)
        {
          h[i] = 0;
        }
      }
    }
  }
  return h;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
  int lot=text.length();
  int lop=pattern.length();
  int ip,it;
  ip=it=0;// :: index for pattern and text
  while((lot-it)>=(lop-ip)){
    if(pattern[ip]==text[it]){
      ip++;it++;
    }
    
    if(ip==lop){
      return it-ip;
      ip=hMatrix[ip-1]; 

    }
    else if(it<lot && pattern[ip]!=text[it]){
      if(ip!=0){
        ip=hMatrix[ip-1];
      }
      else{
        it++;
      }
    }
  }
  return -1;
}

#endif
