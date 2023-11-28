#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"

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

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Incorrect number of arguments" << endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]);   // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1 <= pivot_chooser && pivot_chooser <= 3); // Valid choice of pivot chooser function

    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

    int i, j, k, current_entries = 0;
    SorterTree J(pivot_chooser,num_entries);
    string s;
    while (true)
    {
        cout << ">>>";
        getline(cin, s);
        split(s, ' ');
        if (parse[0] == "INS")
        {
            J.ins_journey(stoi(parse[1]), stoi(parse[2]), current_entries);
            current_entries++;
            cout << "SUCCESSFULLY INSERTED!" << endl;
        }
        else if (parse[0] == "PART")
        {  
            if (J.partition(stoi(parse[1]), stoi(parse[2])))
            {
                cout << "DONE!" << endl;
            }
            else
            {
                cout << "FAILED!" << endl;
            }
        }
        else if (parse[0] == "QSORT")
        {  
            if (J.Quicksort(stoi(parse[1]), stoi(parse[2])))
            {
                cout << "QUICK SORTED!" << endl;
                J.compare();
            }
            else
            {
                cout << "QUICK SORT FAILED!" << endl;
            }
        }
        else if (parse[0] == "QINSERT")
        {  
            if (J.QuicksortWithBSTInsert(stoi(parse[1]), stoi(parse[2])))
            {
                cout << "QUICK SORTED!" << endl;
            }
            else
            {
                cout << "QUICK SORT FAILED!" << endl;
            }
        }
        else if (parse[0] == "ARRAYPRINT")
        {  
           J.printArray();
        }
        else if (parse[0] == "PRINTBST")
        {  
           J.print();
        }
        else if (parse[0] == "IMB")
        {  
           cout<<J.Imbalance()<<endl;
        }
        else if (parse[0] == "COMPARE")
        {  
           J.compare();
        }
        else if (parse[0] == "QUIT")
        {
            break;
        }
        else
        {
            cout << "INVALID REQUEST" << endl;
        }
    }
}
