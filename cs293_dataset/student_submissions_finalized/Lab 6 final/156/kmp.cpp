#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  
  int *H = new int[pattern.length()];

  //the length of the current matching of the prefix with suffix
  int length = 0;

  //first element of hMatrix is always zero
  H[0] = 0;

  //i is the index in the H Matrix whose value is being calculated
  int i=1;

  while(i < pattern.length()){

    // if this two match then set H[i] to length as now length is the number of characters that match 
    if(pattern[i]==pattern[length]){
      length++;
      H[i]=length;
      i++;
    }

    //if pattern does not match then two cases are possible:
    //(i) if length is zero , implies no match had been found yet and this also does not match so now
    //    set the value to zero
    //(ii) if not then that means that we have to shift the matrix so that the new shorter prefix now 
    //     matches with the suffix and again repeat the procedure for the same i
    else{
      if(length!=0){
        length=H[length-1];
      }
      else{
        H[i]=0;
        i++;
      }
    }
  }

  return H;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  
  int txtlen = text.length();
  int patlen = pattern.length();

  int currtxt = 0;//current index of txt being processed
  int currpat = 0;//current index of pattern being processed

  int returnval = -1;//would be changed to index of first char of first occurence of pattern

  while((txtlen-currtxt) >= (patlen-currpat)){
    
    //match found increase indexes by 1 
    //if complete match found ahead then we would return the index
    //else if mismatch found then we would shift using the hMatrix
    if(pattern[currpat]==text[currtxt]){
      currpat+=1;
      currtxt+=1;
    }
    
    if(currpat==patlen){
      returnval = currtxt-patlen;
      break; 
    }

    else if((currtxt < txtlen) && pattern[currpat]!=text[currtxt]){
      if(currpat!=0){
        //according to our implementation of the hMatrix the values stored in it are the values
        //by which the pattern matches with text after shift 
        currpat = hMatrix[currpat-1];
      }
      else{
        currtxt+=1;
      }
    }

  }

  return returnval;
}

#endif
