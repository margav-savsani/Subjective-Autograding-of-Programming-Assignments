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
#include<cmath>
void interchange(listOfObjects<TrainInfoPerStation *> * Node1,listOfObjects<TrainInfoPerStation *> * Node2)
{
	listOfObjects<TrainInfoPerStation *> * Node_dummy=new listOfObjects<TrainInfoPerStation *>(NULL);
	if(Node1==NULL||Node2==NULL)
	{
		return;
	}
	Node_dummy->object=Node1->object;
	Node1->object=Node2->object;
	Node2->object=Node_dummy->object;
	return;
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList,int start,int no_of_nodes)
{
	if(no_of_nodes==0||start<0)
	{
		return;
	}
	int n_by_k=ceil(n/float(k));
	int k=4;
}
