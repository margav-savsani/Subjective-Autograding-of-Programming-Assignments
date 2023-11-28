#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

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

    assert(1<=pivot_chooser && pivot_chooser<=3); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    SorterTree T(pivot_chooser,num_entries);
		string s;
		int i=0;
		while(true){
			cout<<">>>";
			getline(cin,s);
			split(s,' ');
			if (parse[0] == "ADD"){
				i = T.Journey_ins(stoi(parse[1]), stoi(parse[2]), i);
				cout << "SUCCESSFULLY INSERTED" <<endl;
			}
			else if (parse[0] == "sort"){
				if (T.Quicksort(stoi(parse[1]), stoi(parse[2]))){
					T.printArray();
					cout<< "QUICKSORTED" <<endl;
				}
				else
				cout<< "QUICKSORTFAILED" <<endl;
			}
		}
		
}
