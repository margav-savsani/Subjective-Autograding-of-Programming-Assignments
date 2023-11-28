#include <stdlib.h>
#include <iostream>
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
    
    {
        SorterTree *b=new SorterTree(pivot_chooser,num_entries);
		string s;
		for (int i=0;i<num_entries;i++) {
			int code,price;
			cin >> code;
			cin >> price;
			b->insertjourney(code,price);
		}
		cout<<">>> Array before sorting\n";
		b->printArray();
		//sorting 
		b->Quicksort(0,num_entries);
		cout<<"<<< Array after sorting\n";
		b->printArray();
		cout<<"comparision = "<<b->get_comparisions()<<endl;
		b->QuicksortWithBSTInsert(0,num_entries);
		BST * bst=b->getTree();
		cout<<"TREE\n";
		bst->printBST("");
		// while(true){
		// 	cout<<">>>";
		// 	getline(cin,s);
		// 	split(s,' ');
		// 	if(parse[0]=="ADD"){
		// 		if(b->insert(stoi(parse[1]),stoi(parse[2]))){
		// 			cout<<"SUCCESSFULLY INSERTED!"<<endl;
		// 		}else{
		// 			cout<<"INSERTION FAILED!"<<endl;
		// 		}
		// 	}else if(parse[0]=="DEL"){
		// 		if(b->remove(stoi(parse[1]),stoi(parse[2]))){
		// 			cout<<"SUCCESSFULLY DELETED!"<<endl;
		// 		}else{
		// 			cout<<"JOURNEY NOT FOUND!"<<endl;
		// 		}
		// 	}else if(parse[0]=="FIND"){
		// 		if(b->find(stoi(parse[1]),stoi(parse[2]))){
		// 			cout<<"JOURNEY FOUND!"<<endl;
		// 		}else{
		// 			cout<<"JOURNEY NOT FOUND!"<<endl;
		// 		}
		// 	}else if(parse[0]=="TRAVERSE"){
		// 		if(parse[1]!="PRE" && parse[1]!="POST" && parse[1]!="IN"){
		// 			cout<<"INVALID REQUEST!"<<endl;
		// 		}
		// 		int x = (parse[1]=="PRE")?0 : ((parse[1]=="POST")?1:2);
		// 		b->traverse(x);
		// 	}else if(parse[0]=="PRINT"){
		// 		b->printBST("");
		// 	}else if (parse[0]=="QUIT"){
        //         break;
        //     }else{
		// 		cout<<"INVALID REQUEST"<<endl;
		// 	}

		// }
	}
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)

}
