#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern)
{
	int m = pattern.length();
	if(m<=0)
	{
		return NULL;
	}
	int* LPS = new int[m];
	LPS[0]=0;
	int len=0;
	int i=1;
	while(i < m)
	{
		if(pattern[i]==pattern[len]) 
		{
			len = len + 1;
			LPS[i]= len;
			i= i + 1;
		}
		else if(len !=0)
		{
			len=LPS[len - 1];
		}
		else if(len==0)
		{
			LPS[i]=0;
			i=i+1;
		}
	}
	return LPS;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
	int index=0;
	int text_len=text.length();
	int pattern_len=pattern.length();
	if(text_len<1 || pattern_len<1 || text_len<pattern_len || hMatrix ==NULL)
	{
		return 0;
	}
	while(index+pattern_len <= text_len)
	{
		bool matched=true;
		for(int i=0;(i<pattern_len && matched);i++)
		{
			if(text[index+i]!=pattern[i])
			{
				matched=false;
				index+=hMatrix[i]+1;
			}
		}
		if(matched)
		{
			return index;
		}
	}
	return -1;
}

#endif