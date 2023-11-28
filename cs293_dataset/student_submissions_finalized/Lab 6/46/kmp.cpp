#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
	int *arr;
        int sz = pattern.length();
        arr = new int[sz];
        arr[0]=-1;
        cout << arr[0]<<endl;
        arr[1]=0;
        int j=1;
        for(int i=0;i<pattern.length();i++) {
                if(pattern[i]==pattern[i+1]) arr[j] = arr[j-1]+1;
                else arr[j] = arr[arr[j-1]]+1;
                cout <<"h"<< j <<arr[j]<<endl;
                j++;
        }
        return arr;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {

  return 0;
}

#endif
