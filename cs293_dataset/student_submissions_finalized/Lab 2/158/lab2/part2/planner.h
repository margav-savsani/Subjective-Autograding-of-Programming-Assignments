#include<iostream>
#include<string.h>
#include<cmath>
#include"dictionary.h"

#include"dictionary.cpp"

#ifndef PLANNER_H
#define PLANNER_H




struct Station {
 	//station consists of name .
 	char name[32]; 
 	
 	
 	Station(){
 		
 		name = '\0'
 	}
};

struct Journey {
	//journey will have two stations and start and end times.
  	struct Station s1, s2;
 	int start_time;
 	int end_time; 	
};

struct Query{

	struct Dictionary D;
	struct Station arr;
	int num_arr;
	
	Query(){
		arr = new struct Station[64];
		num_arr = 0;
	
	}
	
	
	Add(char s1[],char s2[], int t1,int t2){
		strcpy(arr[num_arr++].name,s1);
		strcpy(arr[num_arr++].name,s2);
		
		struct Entry E(s1, s2, t1, t2);
		
		D.put(E);
		
	
	}

}



#endif
