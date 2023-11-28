#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H	
#include "planner.h"
#endif

using namespace std;


int *Planner::computeHMatrixForKMP(string pattern) {
   
  int length=pattern.length(); 
  int *harray;
  harray=new int [length];
  int n=0;
  int b=0;
  int i=0;
  int j=0;
  for (int k=0; k<length; k++)
    {
       while(true)
        {
          if(j==k) break;
          
          if(i==0)
           {
             if(pattern[i]==pattern[j])
              { 
               b=j;
               i++;
               j++;
               n++;
               continue;
              }
            }
               
          else
           {
             if(pattern[i]==pattern[j]) 
               {
                 n++;
                 i++;
                 j++;
                } 
             else
              {
                i=0;
                j=b+1;
                n=0;
               }
            }  
         }      
        harray[k]=n;
        n=0;
     }  
     return harray;       
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int t_size=text.length();
  int p_size=pattern.length();
  int *harray;
  harray=computeHMatrixForKMP(pattern);
  int i=0,j=0;
  while((t_size-i) >= (p_size-j)){
     if(text[i] == pattern[j])
      {
        i++;
        j++;
       }
     if(p_size == j)
      {
        j=harray[j-1];
        return i-j;  
       }
     else if (i<t_size && pattern[j]!=text[i])
       {
         if(j!=0) j=harray[j-1];
         else i=i+1;
        }
    }         
  return -1;
}

#endif
