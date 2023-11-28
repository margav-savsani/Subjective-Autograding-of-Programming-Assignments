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

listOfObjects<TrainInfoPerStation *> gen_pivot(int x, int y){
	
}

void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList){
	int k = 4;
	int num_trains;
	auto temp = stnInfoList;
	while(temp){
		temp = temp -> next;
		num_trains++;
	}
	auto arr = new listOfObjects<TrainInfoPerStation*>*[num_trains/k+1];
	temp = stnInfoList;
	for(int i{0}; i<num_trains; i++){
		if(! i%k)
			arr[i/k] = temp;
	}
	arr[num_trains/k] = temp;

}
