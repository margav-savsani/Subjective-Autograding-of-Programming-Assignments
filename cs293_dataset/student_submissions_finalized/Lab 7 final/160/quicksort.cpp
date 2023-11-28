#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

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

#include <cstdlib>
#include<ctime>



int day(TrainInfoPerStation* z){
	int d;
	for (int i=0;i<7; i++){
		if (z->daysOfWeek[i] == true){
			d = i;
			break;
		}
	}
	return d;
}

int deptime(TrainInfoPerStation* d){
	return d->depTime;
}

void swap (listOfObjects<TrainInfoPerStation *> * &l, listOfObjects<TrainInfoPerStation *> * &h){
	TrainInfoPerStation * temp1;
	TrainInfoPerStation * temp2;
	temp1 = l->object;
	temp2 = h->object;
	l->object = temp1;
	h->object = temp2;
	
}

listOfObjects<TrainInfoPerStation *>* partition ( listOfObjects<TrainInfoPerStation *>* first, listOfObjects<TrainInfoPerStation *>* last,  listOfObjects<TrainInfoPerStation *>* p ) {// divides the array into two parts.
	if ( first == last ) return p;
	int d = day( p->object );
	int t = deptime(p->object);
	listOfObjects<TrainInfoPerStation *>* l = first;
	listOfObjects<TrainInfoPerStation *>* h = last;
	swap(h,p);
	p = h;
	h=h->prev;
	while (h == l) { // loop until high belows low.
		if((day(h->object)>d||(day(h->object)==d && deptime(h->object)>t))){
			swap(h,p);
			p=h;
			h=h->prev;
		}
		else {
		swap(l,h);
		l=l->next;
		}
	}
	return p;
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
	if ( stnInfoList == NULL) return;
	if (  stnInfoList -> next == NULL ) return;
  	// A few static variable declarations
  	static int k = 4; // Parameter to be experimented with
  	static int recursionLevel = -1; // This can be used to find out at which level of the recursion you are in
  	static listOfObjects<TrainInfoPerStation *>* first;
  	static int firstindex;
  	static listOfObjects<TrainInfoPerStation *>* last;
  	static int lastindex;
  	static listOfObjects<TrainInfoPerStation *>** arr;
  	static listOfObjects<TrainInfoPerStation *>* p;
  	static int pivot;  
  	srand(time(0));
  	// Increment recursion level on entering the function
  	recursionLevel++;
  	if (recursionLevel == 0) {
    	// Find length of the list stnInfoList, if needed.
    		int number=0;
    		listOfObjects<TrainInfoPerStation *>* x = stnInfoList;
    		first = stnInfoList;
    		while (x!=NULL){
    		number++;
    		if ( x->next == NULL )last = x;
    		x = x->next;
    		}
    		pivot = number;
    		firstindex=0;
    		lastindex = number;
    		int qn = number/k;
    		if (number%k!=0) qn++;
    		x = stnInfoList;
    		arr = new listOfObjects<TrainInfoPerStation *>*[qn];
    		for ( int i=0; i< number; i++){
    			if ( i%k == 0 ){
    				arr[i/k] = x;
    			}
    	
    		x = x->next;
    		}
    		pivot = rand()%pivot;
    		int q = pivot/k;
    		int r = pivot%k;
   		x = arr[q];
   		for ( int i=0; i< r; i++){
   			x = x->next;
   		} 
  		p=partition(first,last,x);
   		listOfObjects<TrainInfoPerStation *>* f=first;
   		int i=0;
   		while ( f!= p){
    			i++;
    			f = f->next;
   		}
   		pivot=i;
	}
	else {
 		listOfObjects<TrainInfoPerStation *>* x;
 		if ( stnInfoList->prev == p ){// if the partition is rightone 
			firstindex = pivot + 1;
			if ( firstindex >= lastindex){
          			--recursionLevel;
          			return;
      			}
      			pivot = firstindex + rand()% (lastindex -firstindex);// RANDOM PIVOT GENERATION 
   			int q = pivot/k;
   			int r = pivot%k;
   			x = arr[q];// taking q from array. (static array)
     			for ( int i=0; i< r; i++){
   				x = x->next;
     			}
     			first = stnInfoList;
     			p = partition ( first, last, x);
     			listOfObjects<TrainInfoPerStation *> *f = first;
     			int i=0; 
     			while ( f != p ){
     				i++;
     				f = f->next;
    			}
     			pivot = firstindex+i;
		}
		else {// if the partition is left one
   			lastindex = pivot;
        		if ( firstindex >= lastindex){
          			--recursionLevel;
          			return;
        		}
   			pivot = firstindex + rand() % (lastindex-firstindex);
   			int q = pivot/k;
   			int r = pivot%k;
   			x = arr[q];
  	 		for ( int i=0; i< r; i++){
   				x = x->next;
   			}
       		last = p->prev;
       		p = partition ( first, last, x);
       		listOfObjects<TrainInfoPerStation *> *l = last;
       		int i=0;
       		while ( l != p ){
     				i++;
     				l = l->prev;
       		}
       		pivot = lastindex-i-1;
		}
	}
	
   	listOfObjects<TrainInfoPerStation *> *p2 = p;
   	listOfObjects<TrainInfoPerStation *>* f = first;
  	listOfObjects<TrainInfoPerStation *>* l = last;
   	int lasti = lastindex;
   	int firsti = firstindex;
   	int px = pivot;
   	if ( p != NULL )
   	Quicksort(p->next);
   	p = p2;
   	first = f;
   	last = l;
   	lastindex = lasti;
   	firstindex = firsti;
   	pivot = px;

   	Quicksort(stnInfoList);
    
	recursionLevel--;
	return;
	
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int firstindex, int lastindex)
{
	return;
}

#endif
