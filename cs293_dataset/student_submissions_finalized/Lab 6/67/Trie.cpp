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
	TrieNode *currNode = root;
	int len = wordInName.length();

	// Insert your code here

	for(int i=0;i<len;i++){
		int chr_idx=wordInName[i]|32-'a'; // get index corr to alphabet
		if(!currNode->branch[chr_idx]){// make new node if not created yet
			currNode->numNonNullBranches++;
			currNode->branch[chr_idx]=new TrieNode();
		}
		currNode=currNode->branch[chr_idx];
	}
	currNode->isWord=true;
	listOfObjects<int>* to_add=new listOfObjects<int>(indexOfName);
	to_add->next=currNode->indices;
	currNode->indices=to_add;
	return true;
}

bool Trie::del(string wordInName, string name) {
	TrieNode *currNode = root;
	TrieNode *lastBranchNode = nullptr;
	int lastBranchChar = -1;
	int len = wordInName.length();
	int indexOfName=nameDict->get(wordInName)->value;
	// Insert your code here
	for(int i=0;i<len;i++){
		int chr_idx=wordInName[i]|32 - 97;
		currNode=currNode->branch[chr_idx];
		if(currNode==NULL)	return false;
		if(currNode->isWord || currNode->numNonNullBranches){
			lastBranchNode = currNode;
			lastBranchChar = chr_idx;
		}
	}
	listOfObjects<int>* curr=currNode->indices;
	if(!curr)	return false; // If the word is not stored there
	if(curr->object=indexOfName){ // If the word is the first word there
		currNode->indices=currNode->indices->next;
		if(!currNode->indices && currNode->numNonNullBranches && lastBranchNode){
			recursiveDelete(lastBranchNode->branch[lastBranchChar]);
		}
		return true;
	}
	while(curr->next){
		if(curr->next->object==indexOfName){
			listOfObjects<int>* to_remove=curr->next;
			curr->next==curr->next->next;
			delete to_remove;
			return true;
		}
	}
	return false;
}

listOfObjects<string>* Trie::addWords(listOfObjects<string>* currCompletions,TrieNode* currNode){
	if(!currNode)	return currCompletions;
	for(int i=0;i<NUM_CHARS;i++){
		currCompletions=addWords(currCompletions,currNode->branch[i]);
	}
	if(currNode->isWord){
		listOfObjects<string>* to_add = currNode->indices;
		while(to_add){
			listOfObjects<string>* add=new listOfObjects<string>(getKeyAtIndex(to_add->object));
			to_add=to_add->next;
			add->next=currCompletions;
			currCompletions=add;
		}
	}
	return currCompletions;
}

listOfObjects<string> * Trie::completions(string prefix) {
	TrieNode *currNode = root;
	int len = prefix.length();
	listOfObjects<string> *currCompletions = nullptr;

	// Insert your code here
	for(int i=0;i<len;i++){
		chr_idx = prefix[i]|32-'a';
		currNode=currNode->branch[chr_idx];
	}
	addWords(currCompletions,currNode);
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

/* To Implement */bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

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
