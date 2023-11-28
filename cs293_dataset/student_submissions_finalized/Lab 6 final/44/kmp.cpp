#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
	int pattern_length = pattern.length(); //measuring pattern length
	
	int * lps = new int[pattern_length]; //allocating memory for lps matrix
	
	int matched_pattern=0; //setting matched pattern iterator to 0
	
	lps[0]=0; //lps[0] is always 0
	
	int i= 1; //setting index to 1
	//two iterators are mathced_pattern and i
	while(i<pattern_length){
		//if the character at index i matches the prefix, lps[i] becomes index of matched prefix + 1
		if(pattern[i]==pattern[matched_pattern]){
			matched_pattern++;
			lps[i]=matched_pattern;
			i++; 
		}
		//if the character does not match the character at index matched_pattern
		else{
		/*
		keep decrementing the matched_pattern index till :
		1) the character at index i matched the character at index matched pattern
		2) matched pattern index is non zero
		*/
			while(matched_pattern > 0 and pattern[i]!= pattern[matched_pattern]){
			matched_pattern=lps[matched_pattern-1];
			}
			if(matched_pattern==0){
			lps[i]=0;
			i++;
			}
    	}
  	}
  	return lps;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {	
	/*from planner.cpp 
	1) matchStartIndex = KMPMatch(currReview->object, hMatrix, keywordString);
	2) int *hMatrix;
	3) hMatrix = computeHMatrixForKMP(keywordString);
	4) return -1 if keyword not found, else return the index of the found pattern in the text.
	*/
	
	int len_text=text.length();//length of text
	int len_pattern=pattern.length(); //length of pattern

	int i = 0; //iterator for text
	int j = 0; //iterator for pattern
	
	/**-------pattern matching from text begins---------**/
	while ((len_text - i) >= (len_pattern - j)) { //indices left in the text that are yet to be matched with the indices in the pattern must be greater than the indices left in pattern to be matced.
        //if a match occurs
		if (pattern[j] == text[i]) {
            j++;
            i++;
        }
		//if the whole pattern is matched
        if (j == len_pattern) {
            return i - j ;
        }
 
        // a mismatch occurs after j matches
        else if (i < len_text && pattern[j] != text[i]) { //must check the i < len_text condition first because if i becomes greater than len_text and it tries to call text[i] which would not exist in that case, as only memory equivalent to the len_text was alloted, hence a segfault might occur. and we don't need to check the same condition for j, because if j becomes equal to len_pattern the program will return a value due to the if statement used before this condition.
			//if a mismatch occurs at a non zero j, use the lsp table to move the j
		    if (j != 0)
                j = hMatrix[j - 1];
            else
                i = i + 1;
        }
    }
    return -1;
	/**----------ends----------**/
}

#endif
