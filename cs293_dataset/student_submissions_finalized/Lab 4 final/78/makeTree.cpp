#include <stdlib.h>
#include <iostream>
#include <bits/stdc++.h>
#include <cassert>
#include "sort.cpp"

using namespace std;

vector<string> parse;
void split (string str, char seperator)  
{  
    parse.clear();
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= str.length())  
    {  
        if (str[i] == seperator || i == str.length())  
        {  
            endIndex = i;
            parse.push_back(str.substr(startIndex,endIndex-startIndex));
            startIndex = endIndex + 1;  
        }  
        i++;  
        }     
}  


int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot
    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

    SorterTree *sorttree;
    sorttree = new SorterTree(pivot_chooser,num_entries);
    string s;
    while(true){
        cout<<">>>";
        getline(cin,s);
		split(s,' ');
        if(parse[0]=="PRINTARRAY"){
			if(sorttree->printArray()){
                cout<<"SUCCESSFULLY PRINTED"<<endl;
            }
            else 
                cout<<"UNSUCCESSFULL PRINT"<<endl;
        }
        else if(parse[0]=="SORTARRAY"){
            if(sorttree->Quicksort(stoi(parse[1]),stoi(parse[2]))){
					cout<<"SUCCESSFULLY SORTED"<<endl;
				}else{
					cout<<"SORT FAILED!"<<endl;
                }
        }
        else if(parse[0]=="SORTBST"){
            if(sorttree->QuicksortWithBSTInsert(stoi(parse[1]),stoi(parse[2]))){
					cout<<"SUCCESSFULLY SORTED"<<endl;
				}else{
					cout<<"SORT FAILED!"<<endl;
                }
        }
        else if(parse[0]=="ADD"){
				if(sorttree->addtoarr(stoi(parse[1]),stoi(parse[2]))){
					cout<<"SUCCESSFULLY INSERTED!"<<endl;
				}else{
					cout<<"INSERTION FAILED!"<<endl;
				}
		}
        else if(parse[0]=="COMPARE"){
                cout<<sorttree->numcompare()<<endl;
        }
        else {
            cout<<"INVALID REQUEST"<<endl;
        }
    }
}
