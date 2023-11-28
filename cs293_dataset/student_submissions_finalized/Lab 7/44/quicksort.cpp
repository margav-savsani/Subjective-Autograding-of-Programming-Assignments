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

void swap ( TrainInfoPerStation** a, TrainInfoPerStation** b ){ 
  TrainInfoPerStation* t = *a; *a = *b; *b = t; 
}

listOfObjects<TrainInfoPerStation*> *lastNode(listOfObjects<TrainInfoPerStation*> *root){
	while (root && root->next) root = root->next;
	return root;
}

listOfObjects<TrainInfoPerStation*> * partition(listOfObjects<TrainInfoPerStation*> *l, listOfObjects<TrainInfoPerStation*> *h){
	//pivot as last element :(
	TrainInfoPerStation* x = h->object;

	listOfObjects<TrainInfoPerStation*> *i = l->prev;

	for (listOfObjects<TrainInfoPerStation*> *j = l; j != h; j = j->next){
		if (j->object <= x){
			// Similar to i++ for array
      if(i==nullptr) i==nullptr;
      else i=i->next;
			swap(&(i->object), &(j->object));
		}
	}
  if(i==nullptr) i=l;
  i=i->next;

	swap(&(i->object), &(h->object));
	return i;
}
void quickSort(listOfObjects<TrainInfoPerStation *>* l, listOfObjects<TrainInfoPerStation *> *h){
	if (h != nullptr && l != h && l != h->next){
		listOfObjects<TrainInfoPerStation *> *p = partition(l, h);
		quickSort(l, p->prev);
		quickSort(p->next, h);
	}
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList){
	listOfObjects<TrainInfoPerStation *> *h = lastNode(stnInfoList);
	quickSort(stnInfoList, h);
}
