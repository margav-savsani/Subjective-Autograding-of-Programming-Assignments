#include "dictionary.h"
#include <cmath>
#define A_value 0.618
using namespace std;

Dictionary::Dictionary() {
		N = DICT_SIZE;
		A = new Entry[N];
}

int Dictionary::hashValue(char key[]) {
		long int a=0,x=37; // for decreasing the number of collisions.
		for(int j=strlen(key)-1;j>=0;j--) {
			a = (int(key[j])+x*a); // computing the integer
		}
		double b = a*(A_value);
		double intpart,fracpart;
		fracpart = modf(b,&intpart);
		return int(DICT_SIZE*fracpart);
		
}
int Dictionary::findFreeIndex(char key[]) {
		int h_value = hashValue(key);
		for(int i=h_value; i<N; i++) {
			if(A[i].empty==true) {
				return i;
			}
		}
		return -1;
}
bool Dictionary::put(struct Entry e) {
		int index = findFreeIndex(e.key);
		if(index == -1) {
			return false;
		}
		A[index] = e;
		A[index].empty = false;
		return true;
}
bool Dictionary::remove(char key[]) {
		int h_value = hashValue(key);
		for(int i=h_value; i<DICT_SIZE; i++) {
			string a1 = A[i].key;
			string a2 = key;
			if(a1 == a2) {
				A[i].empty = true;
				A[i].value = -1;
				return true;
			}
		}
		return false;
}
Entry* Dictionary::get(char key[]) {
		int h_value = hashValue(key);
		for(int i=h_value; i<DICT_SIZE; i++) {
			cout << "sh "<< endl;
			cout << key<< endl;
			cout << A[i].key<<endl;
			string a1=A[i].key;
			string a2 = key;
			if(a1==a2) {
				return &A[i];
			}	
		}
		return NULL;	
}
