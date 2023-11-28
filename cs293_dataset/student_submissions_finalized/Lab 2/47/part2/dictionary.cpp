#include"dictionary.h"
#include<cmath>

using namespace std;


int Dictionary :: hashValue(char key[]){

	
	int x=33;
	int p= 0;
	int i=0;
	while( key[i] != '\0'){
	
		int b = key[i];
		p = (p*x+b)%127;
		i++;
	}
	
	double a = 0.618;
	double b = 1;
	double c = (a*p+b);
	p = c;
	p = p%64;
	return p;
}

int Dictionary :: findFreeIndex(char key[]){

	int index = hashValue(key);
	int indexfinal = -1;
	for( int i = index; i< 64; i++){
	
		if( A[i].filled == false ){
			indexfinal = i;
			break;
		}
	}
	return indexfinal;
}

Dictionary :: Dictionary(){

	N = 64;
	A = new Entry[N];
}	
Entry* Dictionary :: get(char key[]){


	 int p = hashValue(key);
	 Entry* X = NULL;
	 
	 for( int i=p; A[i].t != 'c'; i++){
	 
	 	 if( strcpy(A[i].key,key) && A[i].t != 't'){
	 	 
	 	 	return &A[i];
	 	 }
	 }
	 
	 return  X;
}

bool Dictionary :: put(struct Entry e){

		int index = findFreeIndex(e.key);
		
		if( index != -1){
			
			for( int i=0; e.key[i] != 0; i++){
			
				A[index].key[i] = e.key[i];
				if(  e.key[i+1] == '\0'){
				
					A[index].key[i+1] = '\0';
				}
			}
			A[index].filled = true;
			A[index].t = 'd';
			A[index].value = e.value;
			return true;
		}
	
	return false;
}


bool Dictionary ::remove(char key[]){

	
		Entry* F = get(key);
		
		if( F == NULL ){
		
			return false;
		}
		
		else {
		
			F->filled = false;
			F->t = 't';
			return true;
		}
}


	
	
	
