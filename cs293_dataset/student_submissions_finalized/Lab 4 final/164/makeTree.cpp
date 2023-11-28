#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }
    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot
    SorterTree s(num_entries,pivot_chooser);
    int a; int b;
    for (int i=0;i<num_entries;i++)
    {
        cin >>a;cin>>b;
        s.add(a,b);
    }
    s.Quicksort(0,num_entries-1);
    s.QuicksortWithBSTInsert(0,num_entries- 1);
    s.printArray();
    BST *l=s.getTree();
    l->printBST("");
    cout<<l->getImbalance()<<endl;
}
