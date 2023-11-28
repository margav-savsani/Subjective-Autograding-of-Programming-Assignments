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

// If you are using the updated planner.cpp, then you simply need to
// sort the list of TrainInfoPerStation objects in stnInfoList.  The
// function that calls Quicksort in planner.cpp (i.e. printStationInfo)
// will then automatically pretty-print the sorted list.
//
// USING THE UPDATED planner.cpp FILE IS STRONGLY RECOMMENDED
//
// Notice that there is a variable K in Quicksort that is to be used as
// described in the problem statement in problems_statement.pdf
// Specifically, if the first call to Quicksort has an argument list of
// n TrainInfoPerStation objects, you can't use additional storage space
// for more than n/K TrainInfoPerStation objects overall (across all
// recursive calls), you must implement random choice for pivot (i.e.
// each element in the list being sorted should be equally likely to
// be chosen as pivot), and each call to finding a random pivot
// within the list being sorted must take time within O(K), regardless
// of how long the list to be sorted is.
//
// In the function signature of Quicksort, stnInfoList is a list of
// TrainInfoPerStation objects that is to be sorted. In the updated
// planner.cpp file, this list (unsorted) is already prepared for you,
// and you need to simply ensure that the list is sorted (see note
// below about sorting order) when Quicksort returns.
//
// A note about the sorting order:
//
// The final list should be sorted with respect to day of week (first)
// and departure time within the day (next).  Thus Sun 900 < Sun 1100
// < Mon 800 < Thu 700 < Fri 1200
//
//
// Based on how we saw some of you were trying to approach the problem
// in the lab of Sep 23, we are providing another function QuicksortSimple
// with a slightly extended signature. In addition to the list stnInfoList,
// which is passed as the first argument to QuicksortSimple, there are two
// integer parameters "start" and "end", just like in the usual Quicksort
// of an array (as in Prof. Naveen Garg's lectures, for example).
// How do we interpret these "start" and "end" variables in this case,
// when we are trying to sort a list?
// Well, here is one way of thinking about this: If we start
// counting elements of the list starting from stnInfoList and
// chasing "next" pointers until nullptr is reached, the corresponding
// elements can be thought of as elements of a (virtual) array indexed
// from 0 onwards.
// Then, the call to Quicksort must sort the part of the list
// consisting of elements at indices start, start+1, ... until end
// of the above virtual array.
// The whole point of this assignment is to have you do this without
// converting the whole list to an array.
//
// Remember it is indeed possible to solve this problem using the
// function Quicksort with only stnInfoList as its argument.  However,
// if you are finding it difficult to implement Quicksort, you can
// implement QuicksortSimple instead.  Those who implement both
// Quicksort and QuicksortSimple potentially stand to gain some bonus
// points.

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  int n{0}; // number of objects
  static int start,stop;
  int a,b; //stores values of start, stop as a memory because start and stop changes many a times
  static listOfObjects<TrainInfoPerStation *> **arr; //array storing O(n/K) pointers for helping in finding the pivot in O(K) time complexity.
  
  recursionLevel++; // incrementing the recursionLevel
  if(stnInfoList == nullptr || stnInfoList->object == nullptr){ //checking for the case of nullptr
  	recursionLevel--;
  	return;
  }
  
  //Process for creating an array for helping to choose pivot given the constraints is started here
  if (recursionLevel == 0) { //initialising the arr that is created above on the first call to QuickSort function
  	start = 0;
  	auto c = stnInfoList;
    while(stnInfoList != nullptr){
    	n++;
    	stnInfoList = stnInfoList->next;
    }
    stnInfoList = c;
    int a = n/K + 1;
    arr = new listOfObjects<TrainInfoPerStation*>*[a];
    int i=0;
    int j=0;
    while(stnInfoList != nullptr){
    	arr[i] = stnInfoList;
    	i++;
    	while(stnInfoList != nullptr){
    		j++;
    		stnInfoList = stnInfoList->next;
    		if(j%K == 0)break;
    	}
    }
    stop = n-1;
    stnInfoList = c;
    c = nullptr;
  }
  //Making of array of required pointers is completed till above
  a = start;
  b = stop;
  // base condition 
  if(stop <= start){
  	recursionLevel--;
  	return;
  }
  //base condition ends
  
  // Process of choosing pivot
  srand(time(NULL)); 
  int pivot_n = rand() % (b-a+1) + a; //randomising for choosing any object in the list with equal probabiltiy 
  int pivot_q = pivot_n / K;
  int pivot_r = pivot_n % K;
  TrainInfoPerStation* pivot;
  auto c = arr[pivot_q];
  for(int i=0;i<pivot_r;i++){
  	c = c->next;
  }  
  pivot = c->object;
  c = nullptr;
  // Process of choosing pivot ends
  
  //getting all the required information for quicksort starts
  int arrTime = pivot->arrTime;//stores the arrTime of the pivot Train
  int depTime = pivot->depTime;//stores the depTime of the pivot Train
  int day; // stores the day of travelling of the pivot Train
  for(int i=0;i<7;i++){
  	if(pivot->daysOfWeek[i]){
  		day = i;
  		break;
  	}
  }
  if(depTime == -1)depTime = 100000;
  c = stnInfoList;
  for(int i=0;i< stop - start;i++){
  	c = c->next;
  }
  auto finish_p = c; //pointer to the last element in the QuickSort implementation
  auto start_p = stnInfoList;
  c = nullptr;
  
  //getting all the required information for quicksort ends
  
  //Main quicksort starts here
  int dec{stop};
  while(true){
  	while(start<=stop){ // moving from starting to ending 
  		//storing the arrtime, depTime, day of the objects in the List as we iterate thorugh the list
  		int c_arrTime = start_p->object->arrTime;
  		int c_depTime = start_p->object->depTime;
  		int c_day;
  		if(c_depTime == -1) c_depTime = 100000;
  		for(int i=0;i<7;i++){
  			if(start_p->object->daysOfWeek[i]){
  				c_day = i;
  				break;
  			}
  		}
  		//below are the comparison statements for QuickSort implementation
  		if(c_day < day){
  			start++;
  			start_p = start_p->next;
  		}
  		else if(c_day == day){
  			if(c_depTime < depTime){
  				start++;
  				start_p = start_p->next;
  			}
  			else if(c_depTime == depTime){
  				if(c_arrTime < arrTime){
  					start++;
  					start_p = start_p->next;
  				}
  				else{
  					break;
  				}
  			}
  			else{
  				break;
  			}
  		}
  		else{
  			break;
  		}
  	}
	
  	while(start<=stop){ //moving from ending to starting
  	//storing the arrtime, depTime, day of the objects in the List as we iterate thorugh the list
  		int c_arrTime = finish_p->object->arrTime;
  		int c_depTime = finish_p->object->depTime;
  		int c_day;
  		if(c_depTime==-1)c_depTime= 100000;
  		for(int i=0;i<7;i++){
  			if(finish_p->object->daysOfWeek[i]){
  				c_day = i;
  				break;
  			}
  		}
  		
  		//below are the comparison statements for QuickSort implementation
  		if(day < c_day){
  			stop--;
  			finish_p = finish_p->prev;
  			dec--;
  		}
  		else if(c_day == day){
  			if(depTime < c_depTime){
  				stop--;
  				finish_p = finish_p->prev;
  				dec--;
  			}
  			else if(depTime == c_depTime){
  				if(arrTime < c_arrTime){
  					stop--;
  					finish_p = finish_p->prev;
  					dec--;
  				}
  				else{
  					break;
  				}
  			}
  			else{
  				break;
  			}
  		}
  		else{
  			break;
  		}
  	}
  	
  	if(stop>start){ // swapping the objects
  		
  		auto temp_object = start_p->object;
  		start_p->object = finish_p->object;
  		finish_p->object = temp_object;
  		
  	}else{
  		break;
  	}
  }
  //Main quicksort ends here

  //Recursive calling starts
  if(stop == b){
    start = a;
  	stop--;
  	this->Quicksort(stnInfoList); //recursive calling
  }
  else{
  	if(start == stop){
  		start_p = start_p->next;
  	}
    start = a;
  	stop = dec;
  	
  	this->Quicksort(stnInfoList); //recursive calling
  	start = dec+1;
  	stop = b;
  	this->Quicksort(start_p);//recursive calling
  }
  //Recursive calling ends
  recursionLevel--; //recursionLevel decrements to indicate removal of current function call from the stack
  return;
}





void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int stop)
{
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  int n{0};// number of objects
  int a,b;//stores values of start, stop as a memory because start and stop changes many a times
  static listOfObjects<TrainInfoPerStation *> **arr; //array storing O(n/K) pointers for helping in finding the pivot in O(K) time complexity.
  
  recursionLevel++;// incrementing the recursionLevel
  if(stnInfoList == nullptr || stnInfoList->object == nullptr){//checking for the case of nullptr
  	recursionLevel--;
  	return;
  }
  
  //Process for creating an array for helping to choose pivot given the constraints is started here
  if (recursionLevel == 0) {//initialising the arr that is created above on the first call to QuickSort function
  	start = 0;
  	auto c = stnInfoList;
    while(stnInfoList != nullptr){
    	n++;
    	stnInfoList = stnInfoList->next;
    }
    stnInfoList = c;
    int a = n/K + 1;
    arr = new listOfObjects<TrainInfoPerStation*>*[a];
    int i=0;
    int j=0;
    while(stnInfoList != nullptr){
    	arr[i] = stnInfoList;
    	i++;
    	while(stnInfoList != nullptr){
    		j++;
    		stnInfoList = stnInfoList->next;
    		if(j%K == 0)break;
    	}
    }
    stop = n-1;
    stnInfoList = c;
    c = nullptr;
  }
  //Making of array of required pointers is completed till above
  a = start;
  b = stop;
  // base condition 
  if(stop <= start){
  	recursionLevel--;
  	return;
  }
  //base condition ends
  
  // Process of choosing pivot
  srand(time(NULL));
  int pivot_n = rand() % (b-a+1) + a;//randomising for choosing any object in the list with equal probabiltiy 
  int pivot_q = pivot_n / K;
  int pivot_r = pivot_n % K;
  TrainInfoPerStation* pivot;
  auto c = arr[pivot_q];
  for(int i=0;i<pivot_r;i++){
  	c = c->next;
  }  
  pivot = c->object;
  c = nullptr;
  // Process of choosing pivot ends
  
  //getting all the required information for quicksort starts
  int arrTime = pivot->arrTime;//stores the arrTime of the pivot Train
  int depTime = pivot->depTime;//stores the depTime of the pivot Train
  int day;// stores the day of travelling of the pivot Train
  for(int i=0;i<7;i++){
  	if(pivot->daysOfWeek[i]){
  		day = i;
  		break;
  	}
  }
  
  c = stnInfoList;
  for(int i=0;i< stop - start;i++){
  	c = c->next;
  }
  auto finish_p = c;//pointer to the last element in the QuickSort implementation
  auto start_p = stnInfoList;
  c = nullptr;
  if(depTime == -1)depTime = 100000;
  //getting all the required information for quicksort ends
  
  //Main quicksort starts here
  while(true){
  	while(start<=stop){// moving from starting to ending 
  		//storing the arrtime, depTime, day of the objects in the List as we iterate thorugh the list
  		int c_arrTime = start_p->object->arrTime;
  		int c_depTime = start_p->object->depTime;
  		int c_day;
  		if(c_depTime == -1)c_depTime = 100000;
  		for(int i=0;i<7;i++){
  			if(start_p->object->daysOfWeek[i]){
  				c_day = i;
  				break;
  			}
  		}
  		//below are the comparison statements for QuickSort implementation
  		if(c_day < day){
  			start++;
  			start_p = start_p->next;
  		}
  		else if(c_day == day){
  			if(c_depTime < depTime){
  				start++;
  				start_p = start_p->next;
  			}
  			else if(c_depTime == depTime){
  				if(c_arrTime < arrTime){
  					start++;
  					start_p = start_p->next;
  				}
  				else{
  					break;
  				}
  			}
  			else{
  				break;
  			}
  		}
  		else{
  			break;
  		}
  	}
	
  	while(start<=stop){//moving from ending to starting
  	//storing the arrtime, depTime, day of the objects in the List as we iterate thorugh the list
  		int c_arrTime = finish_p->object->arrTime;
  		int c_depTime = finish_p->object->depTime;
  		int c_day;
  		if(c_depTime == -1)c_depTime = 100000;
  		for(int i=0;i<7;i++){
  			if(finish_p->object->daysOfWeek[i]){
  				c_day = i;
  				break;
  			}
  		}
  		//below are the comparison statements for QuickSort implementation
  		if(day < c_day){
  			stop--;
  			finish_p = finish_p->prev;
  		}
  		else if(c_day == day){
  			if(depTime < c_depTime){
  				stop--;
  				finish_p = finish_p->prev;
  			}
  			else if(depTime == c_depTime){
  				if(arrTime < c_arrTime){
  					stop--;
  					finish_p = finish_p->prev;
  				}
  				else{
  					break;
  				}
  			}
  			else{
  				break;
  			}
  		}
  		else{
  			break;
  		}
  	}
  	
  	if(stop>start){
  		// swapping the objects
  		auto temp_object = start_p->object;
  		start_p->object = finish_p->object;
  		finish_p->object = temp_object;
  		
  	}else{
  		break;
  	}
  }
  //Main quicksort ends here

  //Recursive calling starts
  if(stop == b){
  	this->QuicksortSimple(stnInfoList, a, b-1);//recursive calling
  }
  else{
  
  	if(start == stop){
  		start_p = start_p->next;
  	}
  	this->QuicksortSimple(stnInfoList, a, stop);//recursive calling
  	this->QuicksortSimple(start_p, stop+1, b);//recursive calling
  }
  //Recursive calling ends
  recursionLevel--;
  return;
}

#endif
