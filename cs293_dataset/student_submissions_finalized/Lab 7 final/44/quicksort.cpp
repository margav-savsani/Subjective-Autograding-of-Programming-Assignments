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


int N = 0;

/**
 * @brief function that swaps the objects of listOfObjects of type TrainInfoPerStation
 * 
 * @param a pointer to object 1
 * @param b pointer to object 2
 */
void swap ( TrainInfoPerStation** a, TrainInfoPerStation** b ){ 
  TrainInfoPerStation* t = *a; *a = *b; *b = t; 
}

/**
 * @brief obtains last node of the stnInfoList
 * 
 * @param root pointer to the first element or head of the stnInfoList
 * @return listOfObjects<TrainInfoPerStation*>* 
 */
listOfObjects<TrainInfoPerStation*> * lastNode(listOfObjects<TrainInfoPerStation*> *root){
	while (root && root->next) {root = root->next ;
	//  N++;
	 }
	return root;
}


/**
 * @brief partitions the listOfObjects, taking pointer to the last element as pivot, though all the elements have equal probabilities of getting chosen and behaving as a pivot, but the pointer would remain at the end
 * 
 * @param l head of the sub-set linked list to be partitioned
 * @param h tail of the sub-set linked list to be partitioned
 * @return listOfObjects<TrainInfoPerStation*>* 
 */
listOfObjects<TrainInfoPerStation*> *partition(listOfObjects<TrainInfoPerStation*> *l, listOfObjects<TrainInfoPerStation*> *h){
	int x = h->object->arrTime;
	int day = -2;
	for(int j = 0; j<7; j++) {
		if(h->object->daysOfWeek[j]){
			day = j;
			break;
		}
	}

	listOfObjects<TrainInfoPerStation*> *i = l->prev;
	for (listOfObjects<TrainInfoPerStation*> *j = l; j != h; j = j->next){
		int day_of_j = -1;
		for(int k = 0; k <7; k++){
			if(j->object->daysOfWeek[k]){
				day_of_j = k;
				break;
			}
		}
		if (day_of_j < day || (day_of_j==day && j->object->arrTime <= x)){
				
				if(i==nullptr) i=l;
				else i=i->next;
				swap(&(i->object), &(j->object));
		}
		
	}
	if(i==nullptr) i=l;
	i=i->next;

	swap(&(i->object), &(h->object));
	return i;
}
/**
 * @brief pivot_chooser for a linked list of length k
 * 
 * @param s starting point from which the pivot selection starts
 * @return listOfObjects<TrainInfoPerStation*>* 
 */
listOfObjects<TrainInfoPerStation*> *pivot_chooser(listOfObjects<TrainInfoPerStation*>*s, int K){
	srand(time(NULL));
	int number_for_selection_of_pivot = abs(rand()) % (K+1);
	listOfObjects<TrainInfoPerStation*> * pivot = s;
	if(pivot!=nullptr){
		for(int i = 0; i < number_for_selection_of_pivot; i++){
			if(pivot!=nullptr && pivot->next!=nullptr) pivot = pivot->next;
		}
	}
	return pivot;
}
/**
 * @brief it chooses a random pivot and calls the partition function
 * 
 * @param l head of the sub-array in which random pivot is to be chosen
 * @param h tail of the sub-array in which random pivot is to be chosen
 * @param K time complexity of choosing the pivot is O(K)
 * @return listOfObjects<TrainInfoPerStation*>* 
 */
listOfObjects<TrainInfoPerStation*> *divider(listOfObjects<TrainInfoPerStation*> *l,listOfObjects<TrainInfoPerStation*> *h,int K){
	srand(time(NULL));
	
	int number_for_equalProbability = abs(rand()) % (N-K+1);
	listOfObjects<TrainInfoPerStation*> * starting_point = l; //it divides the linked list into N/k arrays each containing K elements
	if(starting_point!=nullptr){
		for(int i = 0; i < number_for_equalProbability; i++){
			if(starting_point!=nullptr && starting_point->next!=nullptr) starting_point = starting_point->next;
		}
	}
	/*this is the pivot chooser, It is traversing less than K times through the linked list to get the pivot, which makes the worst case time complexity of choosing pivot = O(K) */
	listOfObjects<TrainInfoPerStation*> * pivot = starting_point; 
	pivot = pivot_chooser(pivot, K);
		
	if(pivot!=nullptr){
		
		if(pivot!=nullptr){
			swap(&(l->object), &(h->object));
			return partition(l,h);
		}
	}
	return partition(l,h);
}
/**
 * @brief helper function for implementing Quicksort in planner with one arguement, it calls itself recursively after partitioning the linked list by calling the pivot chooser function
 * 
 * @param l head of the sub-linked list on which quicksort is to be performed
 * @param h tail of the sub-linked list on which quuicksort is to be performed
 */
void quickSort(listOfObjects<TrainInfoPerStation *>* l, listOfObjects<TrainInfoPerStation *> *h){
	static int K = 10; // Parameter to be experimented with
	//lesser the K more time it is taking to come out of each recursion.  
  	static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in

  // Increment recursion level on entering the function
  	recursionLevel++;
	cout << "RecursionLevel "<<recursionLevel << endl;
	if (h != nullptr && l != h && l != h->next){
		listOfObjects<TrainInfoPerStation*> * p = divider(l,h,K);
		quickSort(l, p->prev);
		quickSort(p->next, h);
	}
}
/**
 * @brief before introducing random pivot my implementation was working perfectly fine, but after introducing the function to choose pivot except first, rest objects were sorted, so this is an extra function to put the first element at its right place.
 * 
 * @param stnInfoList pointer to the head of the list of objects
 * @param h pointer to the tail of the list of objects
 */
void final_call(listOfObjects<TrainInfoPerStation*>* stnInfoList, listOfObjects<TrainInfoPerStation*>*h){
	listOfObjects<TrainInfoPerStation*>* iterator = stnInfoList;
	while(iterator!=h){
		int day_of_iterator = 0;
		int day_of_iterator_next = 0;
		for(int i = 0; i < 7 ; i++){
			if(iterator->object->daysOfWeek[i]) day_of_iterator = i;
			if(iterator->next->object->daysOfWeek[i])day_of_iterator_next = i;
		}
		
		if(day_of_iterator < day_of_iterator_next) break;
		if(day_of_iterator > day_of_iterator_next  || (day_of_iterator==day_of_iterator_next && iterator->object->arrTime >= iterator->next->object->arrTime)) {
			swap(&(iterator->object), &(iterator->next->object));
			iterator=iterator->next;
		}
		else if(day_of_iterator > day_of_iterator_next  || (day_of_iterator==day_of_iterator_next && iterator->object->arrTime < iterator->next->object->arrTime)) {
			break;
		}
		
	}
}
/**
 * @brief main quicksort function which is called in planner.cpp, it calls the helper quicksort function 
 * 
 * @param stnInfoList list of Objects to be sorted on the basis of days of a week and arrival time. 
 */
void Planner :: Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList){
	
	listOfObjects<TrainInfoPerStation*>*h = lastNode(stnInfoList);
	quickSort(stnInfoList, h);
	
	quickSort(stnInfoList, h);
	
	if(stnInfoList->next!=nullptr) final_call(stnInfoList, h);
}
