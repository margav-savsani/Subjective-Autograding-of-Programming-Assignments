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

#include <stack>

listOfObjects<TrainInfoPerStation*>& get_elem(listOfObjects<TrainInfoPerStation*>** arr, int x, int k, listOfObjects<TrainInfoPerStation*> * stnInfoList){
	arr[0] = stnInfoList;
	auto temp = arr[x/k];
	for(int i{0}; i<x%k; i++){
		temp = temp->next;
	}
	return *temp;
}
//generates a pivot and exchanges it with the yth element
listOfObjects<TrainInfoPerStation *>* gen_pivot(listOfObjects<TrainInfoPerStation*>** arr, int x, int y, int k, listOfObjects<TrainInfoPerStation*> * stnInfoList){
	if(x>y)
		throw ("invalid parameters x = "+ to_string(x) + " and y = " + to_string(y));
	if(x==y){
		auto temp = arr[x/k];
		for(int i{0}; i<x%k; i++){
			temp = temp->next;
		}
		return temp;
	}
	int rand_index = rand()%(x-y)+x;
	auto temp = arr[rand_index/k];
	for(int i{0}; i<rand_index%k; i++){
		temp = temp->next;
	}
	// TrainInfoPerStation* temp1 = get_elem(arr, rand_index, k, stnInfoList).object;
	// get_elem(arr, rand_index, k, stnInfoList).object = get_elem(arr, y, k, stnInfoList).object;
	// get_elem(arr, y, k, stnInfoList).object = temp1;

	return temp;
}

//comparison based on departure times and days
bool operator > (const TrainInfoPerStation& a, const TrainInfoPerStation& b){
	for(int i{0}; i<7; i++){
		if(((b.daysOfWeek)[i]) && !((a.daysOfWeek)[i]))
			return true;
		else if(!((b.daysOfWeek)[i]) && (a.daysOfWeek)[i])
			return false;
	}
	if(a.depTime > b.depTime)
		return true;
	else 
		return false;
}

//comparison based on departure times and days
bool operator < (const TrainInfoPerStation& a, const TrainInfoPerStation& b){
	for(int i{0}; i<7; i++){
		if(((a.daysOfWeek)[i]) && !((b.daysOfWeek)[i])){
			return true;
		}
		else if(!((a.daysOfWeek)[i]) && (b.daysOfWeek)[i]){
			return false;
		}
	}
	if(a.depTime < b.depTime)
		return true;
	else 
		return false;
}
//partitions the list using a given pivot
int partition(listOfObjects<TrainInfoPerStation*>** arr, int start, int finish, int k, listOfObjects<TrainInfoPerStation*>* pivot, listOfObjects<TrainInfoPerStation*> * stnInfoList){
	int i = start-1;
    int j = finish+1;
	auto piv = *(pivot->object);

    while(true){
		i++;
        while(*(get_elem(arr, i, k, stnInfoList).object)<piv){
            i++;
        }
		j--;
        while(*(get_elem(arr, j, k, stnInfoList).object)>piv){
            j--;
        }
        if(i<j){
            TrainInfoPerStation* temp = get_elem(arr, i, k, stnInfoList).object;
            get_elem(arr, i, k, stnInfoList).object = get_elem(arr, j, k, stnInfoList).object;
            get_elem(arr, j, k, stnInfoList).object = temp;
        }
        else{
            if(j==start-1)
                return start;
            if(j==finish)
                return finish-1;
            else return j;
        }
    }
}

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList){
	int k = 2;
	int num_trains{0};
	auto last = stnInfoList;
	while(last){
		last = last-> next;
		num_trains++;
	}
	auto arr = new listOfObjects<TrainInfoPerStation*>*[num_trains/k+1]; //not num_trains/k since it will be 0 for k>num_trains 
	auto temp = stnInfoList;
	for(int i{0}; i<num_trains; i++){
		if(!(i%k))
			arr[i/k] = temp;
		temp = temp->next;
	}
	stack<int> start;
	stack<int> end;
	start.push(0);
	end.push(num_trains-1);
	while(!start.empty()){
		auto s = start.top();
		start.pop();
		auto e = end.top();
		end.pop();
		if(s>e-1)
			continue;
		auto pivot = gen_pivot(arr, s, e, k, stnInfoList);
		int boundary = partition(arr, s, e, k, pivot,stnInfoList);
		start.push(s);
		end.push(boundary);
		start.push(boundary+1);
		end.push(e);
	}
}