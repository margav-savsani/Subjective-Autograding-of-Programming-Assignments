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

int SorterTree::Partition(int p, int r){
	Journey* x;
	if(choice==1) x=choose_one(array, p, r);
	else if(choice==2) x=choose_two(array, p, r);
		else x=choose_three(array, p, r);
	if(a==1){
		tree->insert(x->getJourneyCode(), x->getPrice());
	}
	int i=p;
	int j=r;
	while(1){
		while(array[j].getJourneyCode() > x->getJourneyCode()){ j=j-1;comparisons++; }
		while(array[i].getJourneyCode() < x->getJourneyCode()){ i=i+1;comparisons++; }
		if(i<j){
			Journey k=array[i];
			array[i]=array[j];
			array[j]=k;
		}
		else if(j==r) return j-1;
		else return j;
	}
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.
  if(start<finish){
		int q=Partition(start,finish);
		Quicksort(start,q);
		Quicksort(q+1,finish);
	}
	return true;
}
