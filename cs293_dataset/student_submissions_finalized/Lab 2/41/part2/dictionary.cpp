#include <iostream>
#include "dictionary.h"
#include <math.h>
using namespace std;

int total_numbers = 0;

int str_to_int(int x, string s){
	if(s.length()==1) return int(s[0]);
	else{
		s = s.substr(1);
		return int(s[0]+x*str_to_int(x, s));
	}
}

int Dictionary::hashValue(char key[]){
	string s = ""; int j = 0;
	// for (int i = 0; i < sizeof(key)/sizeof(char); i++){
	// 	s = s + key[i];
	// }
	for(int i=0;i<32;i++)
    {
        if (key[i]!='\0') j++;
        else break;
    }
    for(int i=0; i<j; i++) s += key[i];

	double val, a = 0.618034;
	val = str_to_int(5, s);
	val *= a;
	val = (val-floor(val))*N;
	val = floor(val);
	return val;
}

int Dictionary::findFreeIndex(char key[]){
	int position;
	position = hashValue(key);
	while(A[position].is_there==true){
		position = (position+1)%N;
		total_numbers++;
		if(total_numbers>=N){
			total_numbers = -1;
			return -1;
		}
	}
	return position;
}

struct Entry* Dictionary::get(char key[]){
	int i=0;
	while(i<N){
		if(A[i].key==key){
			if(A[i].is_there==true) return &A[i];
		}
		i++;
	}
	return NULL;
}

Dictionary::Dictionary(){
	N = DICT_SIZE;
}

bool Dictionary::put(struct Entry e){
	int s_position;
	s_position = findFreeIndex(e.key);
	if(total_numbers != -1){
		A[s_position] = e;
		A[s_position].is_there = true;
		A[s_position].tombstone = !A[s_position].is_there ;
		return true;
	}
	else return false;
}

bool Dictionary::remove(char key[]){
	if(get(key)==NULL) return false;
	int i=0;
	while(i<N){
		if(strcmp(A[i].key,key)==0){
			if(A[i].is_there==true){
				A[i].tombstone = true;
				A[i].is_there = !A[i].tombstone;
				return true;
			}
		}
		i++;
	}
}