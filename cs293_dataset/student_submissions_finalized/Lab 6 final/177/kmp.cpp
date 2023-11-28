#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int* Planner::computeHMatrixForKMP(string pattern) {

    int length_of_string = pattern.length();

    int* failure_array = new int[length_of_string];
    failure_array[0] = 0;

    int length = 0;
    int current_index = 1;

    while (current_index < length_of_string){
      if (pattern[current_index] == pattern[length]) failure_array[current_index++] = ++length;
      else{
        if (length != 0) length = failure_array[length - 1];
        else failure_array[current_index++] = 0;
      }
    }
  return failure_array;
}

int Planner::KMPMatch(string text, int* hMatrix, string pattern) {

    int pattern_length = pattern.length();
    int text_length = text.length();
    
    int text_index = 0;
    int pattern_index = 0;

    while ((text_length - text_index) >= (pattern_length - pattern_index)) {
        if (toupper(pattern[pattern_index]) == toupper(text[text_index])) {pattern_index++; text_index++;}
 
        if (pattern_index == pattern_length) {
            return text_index - pattern_index;
        }
 
        else if (text_index < text_length && pattern[pattern_index] != text[text_index]) {
            if (pattern_index != 0) pattern_index = hMatrix[pattern_index - 1];
            else text_index++;
        }
    }
    return -1;
}

#endif
