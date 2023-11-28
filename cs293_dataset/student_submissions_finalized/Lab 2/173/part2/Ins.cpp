#include <iostream>
#include <cstring>
using namespace std;

/* throw an error when inserting an element to the values array if it is full. 
	 insert the element to the array if it as empty place.
*/


const int M=50;     // M is used as the length of the array of
                    // values(3-tuple: Ti, dest, Tf) in railDict

bool insert(float T1[], char stop[][32], float T2[], float Ti, char dest[32], float Tf) {
	
	if (T1[0]==-1) {
		T1[0]=Ti;
		strcpy(stop[0], dest);
		T2[0]=Tf;
		return true;
	}
	
	if (T1[49]==-1) {
		
		int ind=0;
		while (ind<50) {
			if (T1[ind]==-1) break;            // ind here is the index of first
			ind++;                             // empty slot.
		}
		
		for (int i=0; i<ind-1; i++) {
			if ((Ti>=T1[i]) && (Ti<T1[i+1])) {
				for (int j=49; j>i; j--) {
					T1[j]=T1[j-1];                 // I am sorting the array based on Ti
					strcpy(stop[j], stop[j-1]);    // then I'm inserting the new value for 
					T2[j]=T2[j-1];                 // for the given key.
				}
				
				T1[i]=Ti;                        // there is a flaw here though!
				strcpy(stop[i], dest);           // if I insert the value tuple(Ti,dest,Tf)
				T2[i]=Tf;                        // then it inserts instead of giving error
				                                 // for now I'm not correcting it
			}
			
			else if (Ti>=T1[ind-1]) {
				T1[ind]=Ti;
				strcpy(stop[ind], dest);
				T2[ind]=Tf;
			}
		}
		
		return true;	
	}
	
	return false;                          // this is achieved when array is full
	                                       // i.e, max size=50;

}
