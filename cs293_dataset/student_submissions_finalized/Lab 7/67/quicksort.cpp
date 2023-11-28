#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif

bool operator< (TrainInfoPerStation* s1,TrainInfoPerStation* s2){
	for(int i=0;i<7;i++){
		if(s1.daysOfWeek[i] && s2.daysOfWeek[i])	break;
		if(s1.daysOfWeek[i] && !s2.daysOfWeek[i])	return true;
		if(!s1.daysOfWeek[i] && s2.daysOfWeek[i])	return false;
	}
	return s1.depTime<s2.depTime;
}
bool operator> (TrainInfoPerStation* s1,TrainInfoPerStation* s2){
	for(int i=0;i<7;i++){
		if(s1.daysOfWeek[i] && s2.daysOfWeek[i])	break;
		if(s1.daysOfWeek[i] && !s2.daysOfWeek[i])	return false;
		if(!s1.daysOfWeek[i] && s2.daysOfWeek[i])	return true;
	}
	return s1.depTime>s2.depTime;
}
listOfObjects<TrainInfoPerStation*>* choosePivot(listOfObjects<TrainInfoPerStation*>* stnInfoList){
	return stnInfoList->next;
}
void Quicksort(listOfObjects<TrainInfoPerStation *>*& stnInfoList)
{
	// Put your code here.
	if(stnInfoList->next==nullptr)	return;
	listOfObjects<TrainInfoPerStation*> *pivot=choosePivot(stnInfoList);
	listOfObjects<TrainInfoPerStation *>* i=stnInfoList;
	listOfObjects<TrainInfoPerStation *>* j=pivot->next;
	listOfObjects<TrainInfoPerStation*> * brkPt=pivot;
	listOfObjects<TrainInfoPerStation*>* last=nullptr;
	if(j==nullptr)	last=pivot;
	while(!(i==pivot && j==nullptr)){
		if(i<pivot){
			i=i->next;
			continue;
		}
		if(j && j>pivot){
			if(j->next==nullptr){
				last=j;
			}
			j=j->next;
			continue;
		}
		if(i>pivot && j && j<pivot){ // If the two are to be exchanged
			listOfObjects<TrainInfoPerStation*> tempInfo=*i;
			*i=*j;
			*j=tempInfo;
			continue;
		}
		if(i==pivot){
			listOfObjects<TrainInfoPerStation*>* newJ=j->next;
			j->prev->next=j->next;
			if(j->next)	j->next->prev=j->prev;
			j->next=pivot;
			j->prev=pivot->prev;
			if(pivot->prev)	pivot->prev->next=j;
			pivot->prev=j;
			j=newJ;
			continue;
		}
		if(j==nullptr){
			if(i==stnInfoList){
				stnInfoList=i->next;
			}
			if(i->prev)	i->prev->next=i->next;
			i->next->prev=i->prev;
			listOfObjects<TrainInfoPerStation*>* newI=i->next;
			i->next=NULL;
			i->prev=last;
			last->next=i;
			last=i;
			i=newI;
			continue;
		}
	}
	if(stnInfoList!=pivot){
		pivot->prev->next=nullptr;
		Quicksort(stnInfoList);
		pivot->prev=nullptr;
	}
	Quicksort(pivot->next);
	if(pivot!=stnInfoList){
		listOfObjects<TrainInfoPerStation*>* curr=stnInfoList;
		while(curr->next)
			curr=curr->next;
		pivot->prev=curr;
		curr->next=pivot;
	}
	return;



}
