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
	// root null - empty trie -- ??
	TrieNode *currNode = root;
	int len = wordInName.length();
	// Insert your code here
	for (int i =0;i<len;i++){
		int charindex = (wordInName[i]>='a'? wordInName[i]-'a' : wordInName[i]-'A');
		if (currNode->branch[charindex] == nullptr) currNode->branch[charindex] = new TrieNode();
		currNode = currNode->branch[charindex]; 
	} //all except terminal 
	// set for terminal character
	if (currNode->indices == nullptr){ // wasnt a word node yet
		currNode->indices= new listOfObjects<int>(indexOfName);
		currNode->numNonNullBranches = currNode->isWord = true; 
		return true;
	} 
	//is a word already
	for (listOfObjects<int> * currlist = currNode->indices;currlist->object!=indexOfName;currlist = currlist->next){
		if (currlist->next==nullptr){
			currlist->next = new listOfObjects<int>(indexOfName);
			currNode->numNonNullBranches++;
			return true;
		}
	}	
	return false;
}

bool Trie::del(string wordInName, string name) {
	TrieNode *currNode = root;
	TrieNode *lastBranchNode = nullptr;
	int lastBranchChar = -1;
	int len = wordInName.length();

	// Insert your code here
	return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
	TrieNode *currNode = root;
	int len = prefix.length();
	for(int i=0;i<len&&currNode!=nullptr;i++,currNode = currNode->branch[(prefix[i]>='a'? prefix[i]-'a' :prefix[i]-'A')]){}
	if (!(currNode->isWord)) return nullptr;	
	listOfObjects<string> *currCompletions = new listOfObjects<string>();
	recursiveAddCompletions(currNode->indices,currCompletions);
	// Insert your code here
	return currCompletions;
	
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
	if (node->isWord) {
	if (!addCompletions(node, currCompletions)) {
		return false;
	}
	}

	TrieNode *currNode = node;
	for (int i = 0; i < NUM_CHARS; i++) {
	if (currNode->branch[i] != nullptr) {
		if (!recursiveAddCompletions(currNode->branch[i], currCompletions)) {
	return false;
		}
	}
	}

	return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

	// Insert your code here
	return false;
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


#endif
