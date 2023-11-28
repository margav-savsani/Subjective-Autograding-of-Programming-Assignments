#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
   
   int k=numStations;
   for(int i=0;i<pattern.length();i++){
       int x=0;
       for(int j=0;j<i-1;j++){ 
           if(pattern.substr(0,j+1)==pattern.substr(i-j,j+1)) x=j+1;
        }
      hMatrix[k][i]=x;  
   }
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

   
}

#endif
