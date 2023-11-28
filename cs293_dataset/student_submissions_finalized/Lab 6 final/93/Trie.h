#ifndef TRIE_H
#define TRIE_H

#ifndef DICTONARY_H
#include "dictionary.h"

#endif

using namespace std;

#define NUM_CHARS 26

#include <stack>
#include <fstream>
#include <vector>

class TrieNode {
public:
	bool isWord;
	listOfObjects<int> *indices; // Indices in stnNameToIndex dictionary;
								// non-null only if isWord is true
	int numNonNullBranches; //seems useless
	TrieNode *branch[NUM_CHARS];

	// Constructor
	TrieNode() {
		isWord = false;
		indices = nullptr;
		numNonNullBranches = 0;
		for (int i = 0; i < NUM_CHARS; i++) {
			branch[i] = nullptr;
		}
	}

	// Destructor
	~TrieNode() {
		listOfObjects<int> *currIndex = indices;
		while (currIndex != nullptr) {
			listOfObjects<int> *toDeleteIndex = currIndex;
			currIndex = currIndex->next;
			delete toDeleteIndex;
		}
	}

	//Returns true if the TrieNode is Empty i.e. it has no branches and indices is NULL
	bool isEmpty(){
		if(isWord)
			return false;
		if(numNonNullBranches)
			return false;
		return true;
	}
};

class Trie {
private:
	Dictionary<int> *nameDict;
	TrieNode *root;
	void recursiveDelete(TrieNode *node);
	bool isPresentInCompletions(listOfObjects<string> *completions, string name);
	void freeCompletionList(listOfObjects<string> *completions);
	bool recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions);
	bool addCompletions(TrieNode *node, listOfObjects<string> *currCompletions);
  
public:
	// Constructor
	Trie(Dictionary<int> *nameToIndex);
	// Destructor
	~Trie();

	bool insert(string wordInName, int indexOfName);
	bool del(string wordInName, string name);
	listOfObjects<string> *completions(string prefix);
	bool isPresent(string wordInName);

	void recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight);
	void printTrie();

	void dump_trie(){
		TrieNode* x = root;
		stack<TrieNode*> S;
		S.push(root);
		while(!S.empty()){
			x = S.top();
			S.pop();
			listOfObjects<int>* l = x->indices;
			bool temp = l;
			while(l){
				cout<<nameDict->getKeyAtIndex(l->object)<<" ";
				l = l->next;
			}
			if(temp)
				cout<<endl;
			for(int i{0}; i<26; i++){
				if(x->branch[i])
					S.push(x->branch[i]);
			}
		}
		return;
	}

	void trie_render(string filename = "trie_render.py"){
		ofstream out{filename};
		vector<string> program;
		stack <TrieNode*> S;
		stack <char> chars;
		S.push(root);
		chars.push('#');
		while(!S.empty()){
			TrieNode* temp = S.top();
			char c = chars.top();
			S.pop();
			chars.pop();
			string children = "";
			for(int i{0}; i<26; i++){
				if(temp->branch[i]){
					if(children!="" && i!=25)
						children+=", ";
					children+="a"+to_string((long long int)(temp->branch[i]));
					S.push(temp->branch[i]);
					chars.push(i+'a');
				}
			}
			listOfObjects<int>* l = temp->indices;
			string words;
			while(l){
				words+=nameDict->getKeyAtIndex(l->object);
				words+=" ";
				l = l->next;
			} 
			string line_of_code = "a" + to_string((long long int)(temp)) + " = Node( name = \"" + "a" + to_string((long long int)(temp)) + "\", label = \"" + c;
			if(words != ""){
				line_of_code += ": "+words;
			}
			line_of_code+="\"";
			if(children != ""){
				line_of_code+=", children = ["+children+"]";
			}
			line_of_code+=")";
			program.push_back(line_of_code);
		}
		out<<"from anytree import Node, RenderTree\nfrom anytree.exporter import DotExporter"<<endl;
		for(int i = program.size()-1; i>=0; i--){
			out<<program.at(i)<<endl;
		}
		out<<"DotExporter("<<"a"<<(long long int)(root)<<", nodeattrfunc=lambda node: 'label=\"{}\"'.format(node.label)).to_picture(\"test.png\")"<<endl;
	}
};

template <typename T>
listOfObjects<T>* insert_in_order(listOfObjects<T>* lis, T elem, function<bool(T,T)> less_than = [](T a, T b){return a<b;}, function<bool(T,T)> equal_to = [](T a, T b){return a==b;}){
	if(!lis){
		cout<<elem<<endl;
		cout<<"function call on null object\n";
		// exit(-1);
	}
	if(equal_to(lis->object, elem))
		return NULL;
	if(less_than(lis->object, elem)){
		if(!lis->next){
			lis->next = new listOfObjects<T>(elem);
			return lis;
		}
		lis->next = insert_in_order(lis->next, elem, less_than, equal_to);
		return lis;
	}
	else{
		listOfObjects<T>* temp = new listOfObjects<T>(elem);
		temp->next = lis;
		return temp;
	}
	cout<<"listOfObjects::insert_in_order not working"<<endl;
	exit(-1);
	return NULL;
}

#endif
