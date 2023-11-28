#include<iostream>
using namespace std;
#include "planner.cpp"
#include<string>
#include<cstring>
int main(){
	
	Planner p;			//p is a Planner type object 
	string input;
	while(input!="EXIT"){
		cout<<">>>";//Just for good design of input taking process 
		getline(cin, input);
		p.take_query(input);	//feeds the user entered command into the take_query of Planner class 
	}
		
}
