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

TrainInfoPerStation *genRandomPivot(int n, int k, listOfObjects<TrainInfoPerStation*> *stnInfoList)
{
	int randNum1 = rand() % n;
	// int randNum2 = rand() % (n/k);

	// TrainInfoPerStation* currStation =  partitionedStation[randNum2];
	// while(currStation

	listOfObjects<TrainInfoPerStation*> *currStn = stnInfoList;

	for(int i=0; i<randNum1; i++){
		currStn = currStn->next;
	}
	return currStn->object;
}

void swap(listOfObjects<TrainInfoPerStation*> *stn1, listOfObjects<TrainInfoPerStation*> *stn2){
	TrainInfoPerStation* temp = stn1->object;
	stn1->object = stn2->object;
	stn2->object = temp;
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
	

	const int n = 10;
	listOfObjects<TrainInfoPerStation*> partitionedStation[n];
	
	int K = 4, i=0, j=0;
	listOfObjects<TrainInfoPerStation*> *currStation = stnInfoList;
	while(currStation != nullptr){
		partitionedStation[j] = currStation;
		j++;
		while(i<K && currStation != nullptr){
			currStation = currStation->next;
			i++;
		}
		i=0;
	}

	TrainInfoPerStation* pivot = genRandomPivot(K, );
	
	Put your code here.



	if(stnInfoList != nullptr){
		listOfObjects<TrainInfoPerStation*> *pivot = partition();
		Quicksort(stnInfoList, pivot);
		listOfObjects<TrainInfoPerStation*> *currStn = pivot;
		while(currStn->next == nullptr){
			currStn = currrStn->next;
		}
		Quicksort(pivot, currStn);
	}




}
