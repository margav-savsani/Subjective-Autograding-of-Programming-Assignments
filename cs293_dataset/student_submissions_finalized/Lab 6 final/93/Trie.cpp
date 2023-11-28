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

#include <stack>

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
	for (auto c: wordInName){
		int letter = toupper(c) - 'A';
		if(!(currNode->branch[letter])){
			currNode->branch[letter] = new TrieNode();
			currNode->numNonNullBranches++;
		}
		currNode = currNode->branch[letter];
	}
	currNode->isWord = true;
	listOfObjects<int>* temp = new listOfObjects<int>(indexOfName);
	temp->next = currNode->indices;
	currNode->indices = temp;
	// currNode->numNonNullBranches++;
	return true;
}

bool Trie::del(string wordInName, string name) {
	TrieNode *currNode = root;
	TrieNode *lastBranchNode = nullptr;
	int lastBranchChar = -1;
	int len = wordInName.length();
	// Insert your code here
	stack<TrieNode*> parents; //stores the parents of the node containing the word
	stack<int> letter_stack;
	parents.push(root);
	for(int i{0}; i<len; i++){
		//convert to upper case since search is case insensitive
		int letter = toupper(wordInName.at(i))-'A';
		if(!currNode->branch[letter])
			return false;
		currNode = currNode->branch[letter];
		parents.push(currNode);
		letter_stack.push(letter);
	}
	if(!currNode->indices)
		return false;
	// bool ret_val = false;
	listOfObjects<int>* temp = currNode->indices;
	if(name == nameDict->getKeyAtIndex(temp->object)){
		currNode->indices = temp->next;
		delete temp;
		// currNode->numNonNullBranches--;
		if(!currNode->indices)
			currNode->isWord = false;
		// ret_val = true;
	}
	else{
		while(temp->next){
			if(name == nameDict->getKeyAtIndex(temp->next->object)){
				listOfObjects<int>* temp1 = temp->next;
				temp->next = temp->next->next;
				delete temp1;
				// currNode->numNonNullBranches--;
				if(!currNode->indices)
					currNode->isWord = false;
				// ret_val = true;
				break;
			} 
		}
	}
	// std::cout<<currNode->numNonNullBranches<<currNode->indices<<std::endl;
	if(currNode->isEmpty()){
		delete currNode;
		parents.pop();
	}
	else {return true;}
	while(!parents.empty()){
		TrieNode* temp = parents.top();
		parents.pop();
		int letter = letter_stack.top();
		letter_stack.pop();
		temp->branch[letter] = NULL;
		temp->numNonNullBranches--;
		if(temp->isEmpty() && temp != root)
			delete temp;
		else 
			break;
	}
	return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
	TrieNode *currNode = root;
	int len = prefix.length();
	listOfObjects<string> *currCompletions = nullptr;

	// Insert your code here
	stack<TrieNode*> S;
	for(int i{0}; i<len; i++){
		int letter = toupper(prefix.at(i))-'A';
		currNode = currNode->branch[letter];
		if(!currNode)
			return NULL;
	}
	S.push(currNode);
	while(!S.empty()){
		currNode = S.top();
		S.pop();
		listOfObjects<int>* temp = currNode->indices;
		while(temp){
			//insert the word in currCompletions
			if(!currCompletions){
				currCompletions = new listOfObjects<string>{nameDict->getKeyAtIndex(temp->object)};
				temp = temp->next;
				continue;
			}
			auto a = insert_in_order(currCompletions, nameDict->getKeyAtIndex(temp->object));
			if(a)
				currCompletions = a;
			temp = temp->next;
		}
		for(int i{0}; i<26; i++){
			if(currNode->branch[i])
				S.push(currNode->branch[i]);
		}
	}
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

// Edit version 1: Added printTrie and recursivePrintTrie functions
// to help in debugging

void Trie::printTrie()
{
	trie_render();
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
