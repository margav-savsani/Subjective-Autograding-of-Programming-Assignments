#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif
#include <cstdlib>
#include<cmath>
//#include<array>
//#include<vector>
#include <bits/stdc++.h>

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif
using namespace std;

void interchange(listOfObjects<TrainInfoPerStation *>* Node1,listOfObjects<TrainInfoPerStation *>* Node2)
{
	if(Node1==NULL||Node2==NULL)
	{
		return;
	}
	TrainInfoPerStation* TNode=Node1->object;
	Node1->object=Node2->object;
	Node2->object=TNode;
	return;
}
void QuicksortSimplenew(vector<listOfObjects<TrainInfoPerStation*>*> Array, int start, int end, int n_by_k)
{
	//It takes in the Array and uses that for decreasing the time complexity of this program by using Arrays instead of linked lists
	//order of time complexity is very high compared to Arrays, but finding the rand() is order(k)
	if(start>=end)
	{
		return;
	}
	int n= end-start+1;

	if(n==2)
	{
		listOfObjects<TrainInfoPerStation*>* first_elem=Array[start/n_by_k];
		listOfObjects<TrainInfoPerStation*>* last_elem=Array[end/n_by_k];
		for(int i=0;i<start%n_by_k;i++)
		{
			first_elem=first_elem->next;
		}
		for(int j=0;j<end%n_by_k;j++)
		{
			last_elem=last_elem->next;
		}//loading first and last elements to sort
		int day1;
		for(int kk=0;kk<7;kk++)
		{
			if(first_elem->object->daysOfWeek[kk])
			{
				day1=kk;
				break;
			}
		}
		int day2;
		for(int kk=0;kk<7;kk++)
		{
			if(last_elem->object->daysOfWeek[kk])
			{
				day2=kk;
				break;
			}
		}
		if(day1>day2||(day1==day2)&&(first_elem->object->depTime>last_elem->object->depTime)||(day1==day2)&&(first_elem->object->depTime==last_elem->object->depTime)&&(first_elem->object->arrTime>last_elem->object->arrTime))
		{
			interchange(first_elem,last_elem);	
		}
		return;
	}
	srand(time(0));
	int pivot=start+rand()%n;
	listOfObjects<TrainInfoPerStation*>* pivot_ptr=Array[pivot/n_by_k];
	for(int i=0;i<(pivot%n_by_k);i++)
	{
		pivot_ptr=pivot_ptr->next;
	}//maximum time taken will be around n/n_by_k which is k or k+1, order of k is satisfies 

	listOfObjects<TrainInfoPerStation*>* first_elem=Array[start/n_by_k];
	listOfObjects<TrainInfoPerStation*>* last_elem=Array[end/n_by_k];
	for(int i=0;i<start%n_by_k;i++)
	{
		first_elem=first_elem->next;
	}
	for(int j=0;j<end%n_by_k;j++)
	{
		last_elem=last_elem->next;
	}//loading first and last elements to sort


	interchange(pivot_ptr,last_elem);
	pivot_ptr=last_elem;
	last_elem=last_elem->prev;
	//interchanging pivot with last element

	int i=0;
	int j=n-2;
	int pivot_day;
	for(int kk=0;kk<7;kk++)
	{
		if(pivot_ptr->object->daysOfWeek[kk])
		{
			pivot_day=kk;
			break;
		}
	}

	while(i<j)
	{
		bool start_found=false;
		bool last_found=false;
		while(!start_found&&i<j)//should change to something like i<=j
		{	
			int day1=-1;
			for(int kk=0;kk<7;kk++)
			{
				if(first_elem->object->daysOfWeek[kk])
				{
					day1=kk;
					break;
				}
			}
			if(day1>pivot_day||((day1==pivot_day)&&(first_elem->object->depTime>pivot_ptr->object->depTime))||((day1==pivot_day)&&(first_elem->object->depTime==pivot_ptr->object->depTime)&&(first_elem->object->arrTime>pivot_ptr->object->arrTime)))
			{
				start_found=true;
			}
			if(!start_found&&i<j)
			{
				first_elem=first_elem->next;
				i++;
			}
		}
		while(!last_found&& j>i)
		{
			int day2=-1;
			for(int kk=0;kk<7;kk++)
			{
				if(last_elem->object->daysOfWeek[kk])
				{
					day2=kk;
					break;
				}
			}
			if(day2<pivot_day||((day2==pivot_day)&&(last_elem->object->depTime<pivot_ptr->object->depTime))||((day2==pivot_day)&&(last_elem->object->depTime==pivot_ptr->object->depTime)&&(last_elem->object->arrTime<pivot_ptr->object->arrTime)))
			{
				last_found=true;
			}
			if(!last_found&&j>i)
			{
				last_elem=last_elem->prev;
				j--;
			}
		}
		if(!start_found)
		{
			QuicksortSimplenew(Array,start,start+i,n_by_k);
			QuicksortSimplenew(Array,start+i,end,n_by_k);
			return;
		}
		else if (!last_found)
		{
			interchange(first_elem,pivot_ptr);
			QuicksortSimplenew(Array,start,start+i,n_by_k);
			QuicksortSimplenew(Array,start+i+1,end,n_by_k);
			return;
		}
		else
		{
			interchange(last_elem,first_elem);
			first_elem=first_elem->next;
			last_elem=last_elem->prev;
			i++;
			j--;
			if(i==j)
			{
				QuicksortSimplenew(Array,start+i,end,n_by_k);
		 		QuicksortSimplenew(Array,start,start+i-1,n_by_k);
				return;
			}
			if(i>j)
			{
				QuicksortSimplenew(Array,start,start+j,n_by_k);
		 		QuicksortSimplenew(Array,start+i,end,n_by_k);
				return;
			}
		}
	}
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{// I used this function just for calculating start and end for the linked list to be sorted
	int n=0;
	if(stnInfoList==NULL)
	{
		return;
	}
	listOfObjects<TrainInfoPerStation*>* dum=stnInfoList;
	while(dum!=NULL)
	{
		dum=dum->next;
		n++;
	}
	QuicksortSimple(stnInfoList,0,n-1);
	return;
}
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{//I used this function to get the Array that need to be used throughout the recursion and memory of that is in order of n/k
	int N=end-start+1;
	int K=4; // Parameter to be experimented with
	int n_by_k=ceil(N/float(K));
	vector<listOfObjects<TrainInfoPerStation*>*> Array;
	listOfObjects<TrainInfoPerStation*>* dum=stnInfoList;
	for(int i=0;i<N;i++)
	{
		if(i%n_by_k==0)
		{
			Array.push_back(dum);
        }
        dum=dum->next;
    }
	QuicksortSimplenew(Array,start,end,n_by_k);//I wrote a new function which does the main work that is recursion
	return;
}
#endif