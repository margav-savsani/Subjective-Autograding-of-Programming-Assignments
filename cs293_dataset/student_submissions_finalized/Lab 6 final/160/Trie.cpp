#ifndef TRIE_CPP
#define TRIE_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef TRIE_H
#include "Trie.h"
#endif

using namespace std;

Trie::Trie(Dictionary<int> *nameToIndex) {
	nameDict = nameToIndex;
	root = new TrieNode();
	if (root == nullptr) {
		cout << "Memory allocation failure." << endl;
		exit(-1);
	}
}

Trie::~Trie() {
	recursiveDelete(root);
}

void Trie::recursiveDelete(TrieNode *node) {
	if (node == nullptr) {
		return;
	}
	else {
		for (int i = 0; i < NUM_CHARS; i++) {
			TrieNode *currNode = node->branch[i];
			recursiveDelete(currNode);
			node->branch[i] = nullptr;
		}
		if (node != root) {
			delete node;
		}
		return;
	}
}

bool Trie::insert(string wordInName, int indexOfName) {
	//cout<<"yes1"<<endl;
	TrieNode *currNode = root;
	int len = wordInName.length();
	//cout<<"yes2"<<endl;
	for (int i = 0; i <len; i++){
		//cout<<"yes3"<<endl;
		int index = wordInName[i] - 'A';
		//cout<<"yes4"<<endl;
		//cout<<&currNode<<endl;
		if(currNode->branch[index]==nullptr) {
			currNode->numNonNullBranches=currNode->numNonNullBranches+1;
			//cout<<currNode->numNonNullBranches<<endl;
			currNode->branch[index]=new TrieNode();
		}
		currNode = currNode->branch[index];
		//ins(currNode->indices,indexOfName);
	}

	// mark last node as leaf
	listOfObjects<int> *c=new listOfObjects<int>(indexOfName);
	c->next=currNode->indices;
	currNode->indices=c;
	currNode->isWord = true;

	// Insert your code here

	return true;
}

bool Trie::del(string wordInName, string name) {
	TrieNode *currNode = root;
	//TrieNode *lastBranchNode = nullptr;
	//int lastBranchChar = -1;
	int len = wordInName.length();
	for(int i=0;i<len;i++){
		int index=wordInName[i]-'A';
		if(currNode->branch[index]==nullptr){
			return false;
		}
		currNode=currNode->branch[index];
	}

	Entry<int> *outp=nameDict->get(name);
	int r=outp->value;
	listOfObjects<int> *c=currNode->indices;
	//listOfObjects<int> *n=nullptr;
	while(c!=nullptr){
		if(r==(c->object)) {c=c->next;break;}
		c=c->next;
	}

	return true;

}

listOfObjects<string> * Trie::completions(string prefix) {
//cout<<"yes1"<<endl;
	TrieNode *currNode = root;
	int len = prefix.length();
	//cout<<"yes2"<<endl;
	listOfObjects<string> *currCompletions = nullptr;
	for(int i=0;i<len;i++){
		int index=prefix[i]-'A';
		if(currNode->branch[index]==nullptr){
			return nullptr;
		}
		cout<<"yes3"<<endl;
		currNode=currNode->branch[index];
	}
	/*listOfObjects<int> *x=currNode->indices;
	while(x != nullptr){
		int i=x->object;
		listOfObjects<string> *c=new listOfObjects<string>(nameDict->getKeyAtIndex(i));
		c->next=currCompletions;
		currCompletions=c;
		x=x->next;
	}*/
	// Insert your code here
	//cout<<"yes4"<<endl;
	recursiveAddCompletions(currNode,&currCompletions);
cout<<currCompletions<<endl;
	return currCompletions;

}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> **currCompletions) {
	if (node->isWord) {
	//cout<<"yes1"<<endl;
		if (!addCompletions(node, currCompletions)) {
			return false;
		}
	}

	TrieNode *currNode = node;
	for (int i = 0; i < NUM_CHARS; i++) {
		if (currNode->branch[i] != nullptr) {
		//cout<<"yes2"<<endl;
			if (!recursiveAddCompletions(currNode->branch[i], currCompletions)) {
				return false;
			}
		}
	}

	return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> **currCompletions) {
	listOfObjects<int> *x=node->indices;
	cout<<&currCompletions<<endl;
	while(x != nullptr){
	//cout<<&(currCompletions)<<endl;
		int i=x->object;
		
		listOfObjects<string> *c=new listOfObjects<string>(nameDict->getKeyAtIndex(i));
		
		c->next=*currCompletions;
		
		*currCompletions=c;
		x=x->next;
	}
	// Insert your code here
	//cout<<currCompletions->next->object<<endl;
	return true;
}

bool Trie::isPresentInCompletions(listOfObjects<string> *completions, string name) {
	listOfObjects<string> *currCompletion = completions;
	bool isPresent = false;
	while (currCompletion != nullptr) {
		if (currCompletion->object == name) {
			isPresent = true;
			break;
		}
		currCompletion = currCompletion->next;
	}
	return isPresent;
}

void Trie::freeCompletionList(listOfObjects<string> *completions) {
	listOfObjects<string> *currCompl = completions;
	while (currCompl != nullptr) {
		listOfObjects<string> *toDeleteCompl = currCompl;
		currCompl = currCompl->next;
		delete toDeleteCompl;
	}
	return;
}

bool Trie::isPresent(string wordInName) {
	TrieNode *currNode = root;
	int len = wordInName.length();

	for (int i = 0; i < len; i++) {
		int letter = toupper(wordInName.at(i)) - 'A';

		if (currNode->branch[letter] == nullptr) {
			return false;
		}
		currNode = currNode->branch[letter];
	}

	return currNode->isWord;

}

// Edit version 1: Added printTrie and recursivePrintTrie functions
// to help in debugging

void Trie::printTrie()
{
	recursivePrintTrie(root, "", -1, false);
}

// Adapted from Adrian Schneider's code on StackOverflow
// Basically a variation of the function we've been using
// print binary search trees in previous labs

void Trie::recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight)
{
	if (node != nullptr) {
		cout << prefix;

		cout << ((branchId == 0) ? "|-" : (branchId == -1)? " *":"|_" ) << (char) ((branchId != -1) ? 'A'+branchId: '*');
		cout << ((branchId == 0) ? '-' : (branchId == -1) ? '*':'_');

		// If this trie node has isWord set to true, print "(isWord)" and
		// also the list of complete station names (accessed through indices
		// in nameDict) associated with this trie node.
		if (node->isWord) {
			cout << "(isWord)";
			listOfObjects<int> *currIndices = node->indices;
			while (currIndices != nullptr) {
				cout << endl << prefix << "     " << nameDict->getKeyAtIndex(currIndices->object);
				currIndices = currIndices->next;
			}
		}
		else {
			cout << "()";
		}
		cout << endl;
		for (int i = 0; i < NUM_CHARS; i++) {
			TrieNode *currNode = node->branch[i];
			bool childrenToRight = false;
			for (int j = i+1; j < NUM_CHARS; j++) {
				if (node->branch[j] != nullptr) {
					childrenToRight = true;
					break;
				}
			}
			if (currNode != nullptr) {
				recursivePrintTrie(currNode, prefix + ((siblingsToRight) ? "│   " : "    "), i, childrenToRight);
			}
		}
	}
}
// End edit version 1

#endif

