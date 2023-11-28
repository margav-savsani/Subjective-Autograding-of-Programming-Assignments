#include <iostream>
#include "dictionary.h"

int Dictionary::hashValue(char key[]){
	compression_map(key[]);
}

int Dictionary::findFreeIndex(char key[]){
	LinearProb(key);
}

Dictionary::Dictionary(){
	N = DICT_SIZE;
}

bool Dictionary::put(struct Entry e){

}

bool Dictionary::remove(char key[]){

}

int str_to_int(int x, string s){
	if(s.length()==1) return int(s[0]);
	else{
		s.erase(0,1);
		return int(s[0]+x*str_to_int(x, s));
	}
}

int compression_map(char key[]){
	string s = "";
	for (i = 0; i < sizeof(key); i++) s = s + key[i];
	double val, a = 0.618034;
	val = str_to_int(15, s);
	val *= a;
	val = (val%1)*N;
	val = floor(val);
	return val;
}



int LinearProb(char key[]){
	if(N==DICT_SIZE) return -1;
	int position;
	position = compression_map(key);
	while(A[position]!=){
		position = (position+1)%N;
	}
	return position;
}