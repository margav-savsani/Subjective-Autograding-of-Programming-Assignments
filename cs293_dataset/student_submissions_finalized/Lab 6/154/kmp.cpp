#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;


int *Planner::computeHMatrixForKMP(string pattern) {
	// computing the hmatrix

	transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper); // change it to upper
	const int max_idx = pattern.length();
	int* hmatrix = new int[max_idx];
	hmatrix[0]=0; // base case
	// i is current index in pattern
	// k is length of prefix matched
	for(int i=1, k=0; i<max_idx; i++){
		while(k>0 && pattern[k] != pattern[i]) // move the pattern till you find a match
			k = hmatrix[k-1]; 
		if(pattern[k]==pattern[i])
			k++; // adding if last matched
		hmatrix[i]=k;
	}
 	return hmatrix;
}


int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
	// kmpmatch algorithm
	int idx = 0; // curr index in text at start of pattern
	int k = 0; // length of pattern matched
	transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper); // change it to upper
	transform(text.begin(), text.end(), text.begin(), ::toupper); // change it to upper

	const int max_idx = text.length()-pattern.length();
	while(idx <= max_idx){
		while(text[idx + k] == pattern[k]){ // matching and increasing k
			k++;
			if(k==pattern.length()){ // found
				return idx;
			}
		}
		if(k==0){ // moving idx by 1 since no match
			idx++;
		}
		else{ // changing idx and k accordingly with hMatrix since a mismatch
			idx += k-hMatrix[k-1]; 
			k = hMatrix[k-1];
		}
	}
  	return -1; // if not found
}
#endif

// int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
// 	int k = 0;
// 	for(int i=0; i<text.length(); i++){
// 		while(k>0 && pattern[k]!=text[i]){
// 			k = hMatrix[k-1];
// 		}
// 		if (pattern[k]==text[i]){
// 			k++;
// 			if(k==pattern.length()){
// 				return i-k+1;
// 			}
// 		}
// 	}
// 	return -1;
// }

// int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
// 	int idx = 0;
// 	int i =0;
// 	const int max_idx = text.length()-pattern.length();
// 	while(idx <= max_idx){
// 		while(text[i] == pattern[i-idx]){
// 			i++;
// 			if(i-idx==pattern.length()){
// 				return idx;
// 			}
// 		}
// 		if(i-idx==0){
// 			idx++;
// 			i++;
// 		}
// 		else{
// 			idx += i -idx - hMatrix[i-idx-1]; // >=1
// 		}
// 	}
//   	return -1;
// }

// int *Planner::computeHMatrixForKMP(string pattern) {
// 	const int max_idx = pattern.length();
// 	int* hmatrix = new int[max_idx];
// 	hmatrix[0]=0;
// 	for(int i=1, k=0; i<max_idx; i++){
// 		while(k>0 && pattern[k] != pattern[i])
// 			k = hmatrix[k-1];
// 		if(pattern[k]==pattern[i])
// 			k++;
// 		hmatrix[i]=k;
// 	}
// 	for(int i=1, k=0; i<max_idx-1; i++){
// 		while(k>0 && pattern[k] != pattern[i] && pattern[k+1]==pattern[hmatrix[k]+1])
// 			k = hmatrix[k-1];
// 		if(pattern[k]==pattern[i])
// 			k++;
// 		hmatrix[i]=k;
// 	}
//  	return hmatrix;
// }

