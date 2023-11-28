#include "dictionary.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
using namespace std;
Dictionary::Dictionary(){
	N=DICT_SIZE;
	A= new Entry[DICT_SIZE];
}
int Dictionary::hashValue(char key[]){
	int i=0;double hash=0;double x=33;
	while(key[i]!='\0'){
		hash = (x*hash + (key[i]-'a'+1));
		i++;
	}
	hash=hash*(sqrt(5)-1)*0.5;
	hash=hash-floor(hash);
	return floor(DICT_SIZE*hash);
}
int Dictionary::findFreeIndex(char key[]){
	int x;
	x=hashValue(key);
	for(int i=x;i<N;i++){
		if(A[i].code==0||A[i].code==-1) return i;
	}
	return -1;
}
Entry* Dictionary::get(char key[]){
	int x;
	x=hashValue(key);
	int c=1;
	while(c!=(N+1)){
		x=x%N;
		string s=A[x].key;
		string r=key;
		if(r==s&A[x].code!=(-1)) return &A[x];
		else{x++;c++;}
	}
	return nullptr;
}
bool Dictionary::put(Entry e){
	int x;
	x=findFreeIndex(e.key);
	if(x==-1) return 0;
	else {
		A[x]=e;A[x].code=1;
		return 1;
	}
}
bool Dictionary::remove(char key[]){
	bool f;
	if(get(key)==nullptr) f=0;
	else {
		int x;
		x=hashValue(key);
		int c=0;
		while(c!=N){
			x=x%N;
			string r;r=A[x].key;string s;s=key;

			if(r==s){
				A[x].code=-1;f=1;break;
			}
			if(f) break;
			x++;c++;
		}
	}
	return f;
}
