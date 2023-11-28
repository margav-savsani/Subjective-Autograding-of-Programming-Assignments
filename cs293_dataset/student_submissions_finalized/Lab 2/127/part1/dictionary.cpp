#include <iostream>
#include <string>
#include "dictionary.h"

int Dictionary::hashValue(char key[]) {
	int current_pow=0;
	int current_char;
	int current_pow_of_p=1;
	int hash_val=0;
	while(key[current_pow]!='\0') {
		current_char=int(key[current_pow]);
		hash_val=(hash_val+current_char*current_pow_of_p)%N;
		current_pow_of_p=current_pow_of_p*hash_prime%N;
		current_pow+=1;
	}
	return hash_val;
}

int Dictionary::findFreeIndex(char key[]) {
	int start_index=hashValue(key);
	int current_index;
	for(int theta=0; theta<N; theta++) {
		current_index=(start_index+theta)%N;
		if (A[current_index].key[0]=='\0'||A[current_index].key[0]=='\t') {
			return current_index;
		}
	}
	return -1;
}

Dictionary::Dictionary() {
	for(int alpha=0; alpha<N; alpha++) {
		A[alpha].key[0]='\0';
	}
}

struct Entry* Dictionary::get(char key[]) {
	int start_index=hashValue(key);
	int current_index;
	for(int delta=0; delta<N; delta++) {
		current_index=(start_index+delta)%N;
		for(int epsilon=0; epsilon<=32; epsilon++) {
			if(A[current_index].key[epsilon]!=key[epsilon]) break;
			if(key[epsilon]=='\0') return A+current_index;
		}
		if(A[current_index].key[0]=='\0') {
			break;
		}
	}
	return nullptr;
}

bool Dictionary::put(struct Entry e) {
	int start_index=hashValue(e.key);
	int current_index;
	for(int theta=0; theta<N; theta++) {
		current_index=(start_index+theta)%N;
		if(A[current_index].key[0]=='\0'||A[current_index].key[0]=='\t') {
			for(int kappa=0; kappa<=32; kappa++) {
				A[current_index].key[kappa]=e.key[kappa];
				if(e.key[kappa]=='\0') break;
			}
			A[current_index].value=e.value;
			return true;
		}
	}
	return false;
}

bool Dictionary::remove(char key[]) {
	int start_index=hashValue(key);
        int current_index;
        for(int delta=0; delta<N; delta++) {
                current_index=(start_index+delta)%N;
                if(A[current_index].key==key) {
			A[current_index].key[0]='\t';
			return true;
                }
        }
        return false;
}

int Dictionary_float::hashValue(std::string key) {
	int current_pow=0;
	int current_char;
	int current_pow_of_p=1;
	int hash_val=0;
	for(int theta=0; theta<key.length(); theta++) {
		current_char=int(key[current_pow]);
		hash_val=(hash_val+current_char*current_pow_of_p)%N;
		current_pow_of_p=current_pow_of_p*hash_prime%N;
		current_pow+=1;
	}
	return hash_val;
}

int Dictionary_float::findFreeIndex(std::string key) {
	int start_index=hashValue(key);
	int current_index;
	for(int theta=0; theta<N; theta++) {
		current_index=(start_index+theta)%N;
		if (A[current_index].key==""||A[current_index].key=="\t") {
			return current_index;
		}
	}
	return -1;
}




Dictionary_float::Dictionary_float() {
	for(int alpha=0; alpha<N; alpha++) {
		A[alpha].key="";
	}
}

std::vector<float> Dictionary_float::get(std::string key) {
	int start_index=hashValue(key);
	int current_index;
	for(int delta=0; delta<N; delta++) {
		current_index=(start_index+delta)%N;
		if(A[current_index].key==key) {
			return A[current_index].value;
		}
	}
	std::vector<float> temp;
	return temp;
}

bool Dictionary_float::put(std::string key, float values) {
	int start_index=hashValue(key);
	int current_index;
	for(int theta=0; theta<N; theta++) {
		current_index=(start_index+theta)%N;
		if(A[current_index].key==key) {
			A[current_index].value.push_back(values);
		}
		if(A[current_index].key==""||A[current_index].key=="\t") {
			A[current_index].key=key;		
			A[current_index].value.push_back(values);
			return true;
		}
	}
	return false;
}

bool Dictionary_float::remove(std::string key, float value) {
	int start_index=hashValue(key);
    int current_index;
    for(int delta=0; delta<N; delta++) {
        current_index=(start_index+delta)%N;
        if(A[current_index].key==key) {
			
			return true;
        }
    }
    return false;
}

int Dictionary_string::hashValue(std::string key) {
	int current_pow=0;
	int current_char;
	int current_pow_of_p=1;
	int hash_val=0;
	for(int theta=0; theta<key.length(); theta++) {
		current_char=int(key[current_pow]);
		hash_val=(hash_val+current_char*current_pow_of_p)%N;
		current_pow_of_p=current_pow_of_p*hash_prime%N;
		current_pow+=1;
	}
	return hash_val;
}

int Dictionary_string::findFreeIndex(std::string key) {
	int start_index=hashValue(key);
	int current_index;
	for(int theta=0; theta<N; theta++) {
		current_index=(start_index+theta)%N;
		if (A[current_index].key==""||A[current_index].key=="\t") {
			return current_index;
		}
	}
	return -1;
}




Dictionary_string::Dictionary_string() {
	for(int alpha=0; alpha<N; alpha++) {
		A[alpha].key="";
	}
}

std::vector<std::string> Dictionary_string::get(std::string key) {
	int start_index=hashValue(key);
	int current_index;
	for(int delta=0; delta<N; delta++) {
		current_index=(start_index+delta)%N;
		if(A[current_index].key==key) {
			return A[current_index].value;
		}
	}
	std::vector<std::string> temp;
	return temp;
}

bool Dictionary_string::put(std::string key, std::string values) {
	int start_index=hashValue(key);
	int current_index;
	for(int theta=0; theta<N; theta++) {
		current_index=(start_index+theta)%N;
		if(A[current_index].key==key) {
			A[current_index].value.push_back(values);
		}
		if(A[current_index].key==""||A[current_index].key=="\t") {
			A[current_index].key=key;		
			A[current_index].value.push_back(values);
			return true;
		}
	}
	return false;
}

bool Dictionary_string::remove(std::string key, std::string value) {
	int start_index=hashValue(key);
    int current_index;
    for(int delta=0; delta<N; delta++) {
        current_index=(start_index+delta)%N;
        if(A[current_index].key==key) {
			A[current_index].key="\t";
			return true;
        }
    }
    return false;
}
