#include <iostream>
#include <fstream>
#include"own.cpp"
#include<vector>
// #include <bits/stdc++.h>
#include<sstream>
#include<string>
#include<utility>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

string tostring(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}
int main(int argc, char** argv) {
	Own *o = new Own();

	//string file_name = argv[1];
	
//	ifstream input("graphFile.txt");
	ifstream input(argv[1]);
	vector<pair<int,int> >  e;
	string myText;
	stringstream temp;
	while (getline (input, myText)) {
  		int count = 0;
  		stringstream tempss,tempss2;
  	
  		int num;
  		stringstream ss(myText);
    		string word;
    		while (ss >> word) {
        		
        		count++;
    		}
    		if(count==1) {
    			tempss<<word;
    			tempss>>num;
				o->setNodes(num);
    		}
    		else {
    		stringstream ss1(myText);	
    			int c =0;
    			pair<int, int> temppair;
    			while(ss1 >> word) {
    			
    				if(c==0) {
    					tempss<<word;
    					tempss>>num;
    					if(num==-1)
    						break;
    					
    					temppair.first = num;
    					c++;
    				}
    				else {
    					tempss2<<word;
    					tempss2>>num;
    					
    					temppair.second = num;
    				}
    				
    			}
    			if(c!=0)
	    			e.push_back(temppair);
    		}
  		
	}
	input.close();
	o->setEdges(e);

	o->setsourcesdest();
	o->setsources();
	vector<int> sources = o->displaysources();

	string x = "Source: ";
	for(int i=0;i<sources.size();i++) {
		x = x+tostring (sources[i])+" ";
	}
	//o->displayEdges();
	o->setsimedges();
	vector<pair<int, int> > simedges = o->dispsimedges();
	
	x = x+"\n\nSimilar Node Pair : ";
	for(int i=0;i<simedges.size();i++) {
		x = x+"("+ tostring  (simedges[i].first)+", "+tostring (simedges[i].second)+")";
	
	}
	
	vector<int> cnode = o->getcollapsenode();
	x = x+"\n\nCollapsed graph: \n"+tostring(cnode.size())+": ";
	
	for(int i=0;i<cnode.size();i++) {
		x = x+tostring(cnode[i])+" ";
	}
	//if you want to display output on screen
	cout<<x;
	ofstream output("outgraph.txt");
	output<<x;
	output.close();
	return 0;	
}
