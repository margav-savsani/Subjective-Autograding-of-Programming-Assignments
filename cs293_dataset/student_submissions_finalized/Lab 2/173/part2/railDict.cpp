#include "railDict.h"
#include "Ins.cpp"
/*
	caveat: There seems to be a problem here. I can actually
	        insert more than one identical keys and I'm lazy
	        in figuring out how to come up with a better 
	        solution to it.  
*/


const double G=0.618033989;

struct Data {
	char KEY[32];
	
	float TI;
	char DEST[32];                         // this is to resolve conflict
	float TF;                              // for put(Entry e); function
};

struct Entry {
	char key[32];                          // is it less better than to define
	                                       // as char* key; ?
	float Ti[50];
	char dest[50][32];                     // these 3 form values
	float Tf[50];                          // setting Ti[0]=-1 means empty and
	                                       // setting Ti[0]=-2 means tombstone.
};

Dictionary::Dictionary() {
	N=64;                                  // 64 is DICT_SIZE
	A = new Entry[N];
	
	for (int i=0; i<N; i++) {
		for (int j=0; j<50; j++)
			A[i].Ti[0]=-1;                     // assuming that value is never -ve
		                                     // and setting it to -1 means empty. 
		                                     // setting it to -2 is just to remind 
		                                     // ourselves that it is a tombstone. 
	}
}

int Dictionary::hashValue(char key[]) {
	int i=0, x=19,                         // wanna change x to 19?
	c=int(key[i]),
	val=c;
	c=key[++i];
	
	while (c != '\0') {
		val=(val*x)%N+int(c);                    // hornor's method for computing polynomial.
		c=key[++i];                          // computing hash value.
	}
	
	return int(64*((val*G)- int(val*G)));  // compression map using fibonacci	
}

int Dictionary::findFreeIndex(char key[]) {
	for (int i=0; i<N; i++) {              // this for loop is just if(table==full)
			if (A[i].Ti[0]==-1) break;         // then return -1; we are doing linear probing.  
			else if (i==N-1) return -1;           
	}

	int probe=hashValue(key);

	while (A[probe].Ti[0] != -1)
		probe=(probe+1)%N;                   // this while loop just checks for empty slots
	                                       // to find the free index, if the index calculated
	                                       // for the hashValue is occupied by shifting the

	return probe;
}

Entry* Dictionary::get(char key[]) {
	for (int i=0; i<N; i++) {              // for loop here used to iterate over all entries
		if (A[i].Ti[0] !=-1)                 // this 'if' condition is to ensure that we are checking
			if (strcmp(A[i].key,key)==0)       // for non empty slots
				return &A[i];
	}
	return NULL;
}

bool Dictionary::put(struct Data e) {
	                                       // I needed to define new struct because
	                                       // in my implementation of struct I gave array
	                                       // of value tuple a size of 32. But I only need to 
	                                       // add one value tuple
	                                         
	if (findFreeIndex(e.KEY)==-1)          // if the table is full return false;
		return false;
	
	strcpy(A[findFreeIndex(e.KEY)].key, e.KEY);
	     
	int f=findFreeIndex(e.KEY);
	
	if (insert(A[f].Ti, A[f].dest, A[f].Tf, e.TI, e.DEST, e.TF));
		return true;                         // return true if the insert is successful
		                                     // it happens when the tuple array is not 
		                                     // full
}

/*
bool Dictionary::remove(char key[]) {
	
	int ind;
	for (int i=0; i<N; i++) {              // check if the key to be deleted is in table
		if (strcmp(A[i].key,key)==0) {ind=i; break;}
		else if (i==N-1) return false;
	}
	
	for (int i=0; i<32; i++) {             // yep, I couldn't find a better way to delete
		A[ind].key[i]='\0';                  // the key.
	}
	                                       // by deleting I implicity mean deleting the
	A[ind].value=-2;                       // entry and setting a tombstone, in this case 
	return true;                           // by setting value=-2(assuming value never takes
	                                       // -ve values and seting key to '\0' (i.e., null
	                                       // character).
}
*/
