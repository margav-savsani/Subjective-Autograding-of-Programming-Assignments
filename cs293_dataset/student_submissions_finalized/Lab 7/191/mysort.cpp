#include<iostream>
using namespace std;

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

const int k=10;
const int n=100;

void make_partition_array(listOfObjects<int> *list, listOfObjects* arr){
	
	int size = k;
	for(int i=0;i<n;i+=k){
		arr[i/k] = list;
		for(int j=0;j<k;j++){
			list = list->next;
		}
	}
	
}

void sort(listOfObjects<int> *list, listOfObjects* arr){
	
}

int main(){
	
	listOfObjects<int> *t = new listOfObjects<int>(0);
	
	for(int i=0;i<n;i++){
		t->next = new listOfObjects<int> (rand()) ;
		cout<<rand()<<endl;
	}
	listOfObjects* p = new listOfObjects*[ceil(n/k)]
	
	make_partition_array(t, p);
	sort(t, p);
	
	
	for(int i=0;i<n+1;i++){
		t->next = new listOfObjects<int> (rand()) ;
		cout<< t <<endl;
		t = t->next;
	}
}
