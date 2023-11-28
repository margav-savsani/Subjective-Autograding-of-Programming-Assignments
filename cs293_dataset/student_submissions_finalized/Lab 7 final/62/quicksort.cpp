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

#define node listOfObjects<TrainInfoPerStation *> // helpful macro


// just to compare for sorting
bool lessthan(node* LHS, node* RHS){
	TrainInfoPerStation* left = LHS->object, *right = RHS->object;
	for(int day=0;day<7;day++){ //compare days first, only if the same day check time
		if (left->daysOfWeek[day]&&right->daysOfWeek[day]) break;
		if (left->daysOfWeek[day]) return true;
		if (right->daysOfWeek[day]) return false;
	}
	if (left->depTime==-1) return false; // -1 => train never left, it makes sense to show those at the end
	if (right->depTime==-1) return true; // "train leaves at infinity"
	return (left->depTime<right->depTime);
}


//partitioning into left side | pivot element | right side
void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
	if (end<=start) return;//base case
	if (stnInfoList==nullptr) return; // error
	// A few static variable declarations
	static int K = 4; // Parameter to be experimented with
	static int recursionLevel = -1; // This can be used to find out at which
	                                // level of the recursion you are in
	static node ** ptarr = nullptr; // array of each n/kth node

	int size = end+1-start;//size of array/subarray
	// Increment recursion level on entering the function
	recursionLevel++;
	
	if (recursionLevel == 0) { // start 0
		ptarr = new node*[size/K +1]; //for first rec level size is total size
		node * stptr = stnInfoList;
		for(int i = 0; i<=end;i++){ //fill pointers in the array
			if(i%K==0){
				ptarr[i/K] = stptr;
			}
			stptr = stptr->next;
		}
	}
	//generate the pivot randomly
	int randNum = rand()%(size) + start;
	node* op;
	op = ptarr[randNum/K];
	for(int i=0;i<randNum%K;i++){op = op->next;}
	swap(stnInfoList->object,op->object);//move the pivot to the front for ease
	//swapping pointers is fast

	int i = start+1,j=end; 
	node* currleft=stnInfoList->next,* currright=stnInfoList;
	for(int k=start;k<end;k++){currright=currright->next;} //get last pointer
	
	while(i<j){ //partition loop
		while(!lessthan(currright,stnInfoList)&&i<j){ //right side
			currright=currright->prev;
			j--;
		}
		while(!lessthan(stnInfoList,currleft)&&i<j){ //left side
			currleft = currleft->next;
			i++;
		}
		if(i<j){//swap
			swap(currleft->object,currright->object);
		}

	}
	if (!lessthan(currleft,stnInfoList)) { //we have to put the pivot in the middle again
		currleft = currleft->prev;
		i--;
	}
	swap(stnInfoList->object,currleft->object);
	// two parts n pivot	
	QuicksortSimple(stnInfoList, start, i-1); //left side
	QuicksortSimple(currleft->next,i+1,end); //right side
	// Decrement recursion level before leaving the function

	if (recursionLevel == 0) delete[] ptarr; //free the array on the outermost recursion

	recursionLevel--;
	return;
}

//essentially the same as quicksort simple
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
	if (stnInfoList==nullptr) return;
	// A few static variable declarations
	static int K = 4; // Parameter to be experimented with
	static int recursionLevel = -1; // This can be used to find out at which
	                                // level of the recursion you are in
	static node ** ptarr = nullptr;
	static int start=-2,end=-1;//here start and end are static variables instead of parameters
	if (end<=start) return;
	// Increment recursion level on entering the function
	recursionLevel++;
	
	if (recursionLevel == 0) { // start 0
		start=end=0;
		for(node* tail = stnInfoList;tail->next!=nullptr;tail=tail->next){end++;}
		int size = end+1;
		ptarr = new node*[size/K +1]; //for first rec level size is total size
		node * stptr = stnInfoList;
		for(int i = 0; i<=end;i++){
			if(i%K==0){
				ptarr[i/K] = stptr;
			}
			stptr = stptr->next;
		}
	}
	
	int size = end+1-start;
	int randNum = rand()%(size) + start;
	node* op;
	op = ptarr[randNum/K];
	for(int i=0;i<randNum%K;i++){op = op->next;}
	swap(stnInfoList->object,op->object);

	int i = start+1,j=end; 
	node* currleft=stnInfoList->next;
	node* currright=stnInfoList;
	for(int k=start;k<end;k++){currright=currright->next;} //get last pointer
	
	while(i<j){
		while(!lessthan(currright,stnInfoList)&&i<j){
			currright=currright->prev;
			j--;
		}
		while(!lessthan(stnInfoList,currleft)&&i<j){
			currleft = currleft->next;
			i++;
		}
		if(i<j){
			swap(currleft->object,currright->object);
		}

	}
	if (!lessthan(currleft,stnInfoList)) {
		currleft = currleft->prev;
		i--;
	}
	swap(stnInfoList->object,currleft->object);
	// two parts n pivot	
	int tmp1 = end, tmp2=start;
	end = i-1;
	Quicksort(stnInfoList);// start - i-1
	start= end+2; // start- end+1
	end = tmp1;
	Quicksort(currleft->next); // i+1 - end
	start = tmp2;
	// Decrement recursion level before leaving the function

	if (recursionLevel == 0) delete[] ptarr;

	recursionLevel--;
	return;
}


/*
//wanted this to be quicksort.. have to fix some errors
void Planner::Quicksort_(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
	// A few static variable declarations
	static int K = 4; // Parameter to be experimented with
	static int recursionLevel = -1; // This can be used to find out at which
	                                // level of the recursion you are in
	static node** ptarr = nullptr;
	static int offset = 0; //offset of order in list and recursive sublist
	
	
	if (stnInfoList==nullptr) return;//in case of some error

	int size =1;
	node* tail;
	for(tail = stnInfoList;tail->next!=nullptr;tail=tail->next){size++;}
	if (size<=1) return;

	// Increment recursion level on entering the function
	recursionLevel++;
	if (recursionLevel == 0) { // start 0
		ptarr = new node*[size/K +1]; //for first rec level size is total size
		node * stptr = stnInfoList;
		for(int i = 0; i<size;i++){
			if(i%K==0){
				ptarr[i/K] = stptr;
			}
			stptr = stptr->next;
		}
	}
	//* 
	int randNum = rand()%(size) + offset;
	node* op;
	if(size>=K){
		op = ptarr[randNum/K];
		for(int i=0;i<randNum%K;i++) op = op->next;
	}
	else{
		op = stnInfoList;
		for(int i=0;i<randNum-offset;i++) op = op->next;
	}
	
	swap(stnInfoList->object,op->object);

	int i = offset+1,j=offset+size-1; 
	node* currleft=stnInfoList->next,* currright=tail;
	
	while(i<j){
		while(!(lessthan(currright,stnInfoList))&&i<j){
			currright=currright->prev;
			j--;
		}
		while(!lessthan(stnInfoList,currleft)&&i<j){
			currleft = currleft->next;
			i++;
		}
		if(i<j){
			swap(currleft->object,currright->object);
		}

	}

	if (!lessthan(currleft,stnInfoList)) {
		currleft = currleft->prev;
		i--;
	}
	swap(stnInfoList->object,currleft->object); 
	if(currleft->prev!=nullptr) currleft->prev->next=nullptr;
	if (currleft->next!=nullptr) currleft->next->prev = nullptr;
	// two parts n pivot	
	Quicksort_(stnInfoList);
	offset += (i+1);
	Quicksort_(currleft->next);
	offset -= (i+1);
	// Decrement recursion level before leaving the function
	if(currleft->prev!=nullptr) currleft->prev->next=stnInfoList;
	if (currleft->next!=nullptr) currleft->next->prev = currleft;

	if (recursionLevel == 0) delete[] ptarr;

	recursionLevel--;
	return;
}
*/
#endif
