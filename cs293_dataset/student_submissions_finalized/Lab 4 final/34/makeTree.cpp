#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <vector>
using namespace std;

vector<string> parse;
void split(string str, char seperator)
{
	parse.clear();
	int currIndex = 0, i = 0;
	int startIndex = 0, endIndex = 0;
	while (i <= str.length())
	{
		if (str[i] == seperator || i == str.length())
		{
			endIndex = i;
			parse.push_back(str.substr(startIndex, endIndex - startIndex));
			startIndex = endIndex + 1;
		}
		i++;
	}
}
int main(int argc, char** argv)
{
    // cout << "working1\n";
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }
    // cout << "working2\n";
    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    SorterTree* S_T = new SorterTree(pivot_chooser, num_entries);
    string s;
    bool input = false;
    // cout << "working\n";
	while (getline(cin, s))
	{
        split(s, ' ');
        if(!S_T->insertEle(stoi(parse[0]), stoi(parse[1]))){
            cout << "max capacity reached\n";
            break;
        }
    }
    // S_T->printArray();
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    if(!S_T->QuicksortWithBSTInsert(0, num_entries)){
        cout << "One of the pivot was wrong\n";
        exit(0);
    };
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> time_taken = end - start;
    cout << "Time taken : " << time_taken.count() << "s\n";
    // S_T->printTree();
    cout << "the imbalance is : " << S_T->imbalanceTree() << endl;
    cout << "total comparisons : " << S_T->get_Comparison() << endl;
    // if(!S_T->Quicksort(0, num_entries)){
    //     cout << "One of the pivot was wrong\n";
    //     exit(0);
    // };   
    // S_T->printArray();
}

