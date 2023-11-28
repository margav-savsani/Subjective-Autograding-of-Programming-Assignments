#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <bits/stdc++.h>
#include <string>
#include <fstream>

using namespace std;
#include "sort.cpp"

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

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Incorrect number of arguments" << endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]);   // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1 <= pivot_chooser && pivot_chooser <= 4); // Valid choice of pivot chooser function

    SorterTree *t = new SorterTree(pivot_chooser, num_entries);
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    BST *b = t->getTree();
    string s;
    while (true)
    {
        cout << ">>>";
        getline(cin, s);
        split(s, ' ');
        if (parse[0] == "ADD")
        {
            if (b->insert(stoi(parse[1]), stoi(parse[2])))
            {
                cout << "SUCCESSFULLY INSERTED!" << endl;
            }
            else
            {
                cout << "INSERTION FAILED!" << endl;
            }
        }
        else if (parse[0] == "DEL")
        {
            if (b->remove(stoi(parse[1]), stoi(parse[2])))
            {
                cout << "SUCCESSFULLY DELETED!" << endl;
            }
            else
            {
                cout << "JOURNEY NOT FOUND!" << endl;
            }
        }
        else if (parse[0] == "FIND")
        {
            if (b->find(stoi(parse[1]), stoi(parse[2])))
            {
                cout << "JOURNEY FOUND!" << endl;
            }
            else
            {
                cout << "JOURNEY NOT FOUND!" << endl;
            }
        }
        else if (parse[0] == "SORT")
        {
            if (t->Quicksort(0,num_entries-1))
            {
                cout << "SORTED!" << endl;
            }
            else
            {
                cout << "Sorting did not take place" << endl;
            }
        }
        else if (parse[0] == "printArray")
        {
            t->printArray();
        }
        else if (parse[0] == "printBST")
        {
            b->printBST("");
        }
        else if (parse[0] == "getImbalance")
        {
            cout<<b->getImbalance()<<endl;
        }
        else if (parse[0] == "SORT-BST")
        {
            if (t->QuicksortWithBSTInsert(0,num_entries-1))
            {
                cout << "SORTED!" << endl;
            }
            else
            {
                cout << "Sorting did not take place" << endl;
            }
        }
    }
    /*if (!(t->Quicksort(0, num_entries-1)))
    {
        cout << "Sorting did not take place" << endl;
    }
    else{cout<<"Sorted"<<endl;}
    t->printArray();
    //cout<<t<<endl;
    if (!(t->QuicksortWithBSTInsert(0, num_entries-1)))
    {
        cout << "Sorting did not take place" << endl;
    }
    else{cout<<"Sorted"<<endl;}

    t->printArray();
    t->getTree()->printBST("");
    cout<< t->getTree()->getImbalance()<<endl;*/
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
}
