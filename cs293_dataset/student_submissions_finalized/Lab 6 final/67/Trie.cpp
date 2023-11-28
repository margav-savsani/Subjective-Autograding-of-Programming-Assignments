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
		int chr_idx=(wordInName[i]|32)-'a'; // get index corr to alphabet
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
	TrieNode *lastBranchNode = root;
	int lastBranchChar = (name[0]|32) - 'a';
	int len = wordInName.length();
	int indexOfName=nameDict->get(name)->value;
	// Insert your code here
	for(int i=0;i<len;i++){
		int chr_idx=(wordInName[i]|32) - 'a';
		if(currNode==NULL)	return false;
		if(currNode->isWord || currNode->numNonNullBranches>1){
			lastBranchNode = currNode;
			lastBranchChar = chr_idx;
		}
		currNode=currNode->branch[chr_idx];
	}
	listOfObjects<int>* curr=currNode->indices;
	if(!curr)	return false; // If the word is not stored there
	if(curr->object==indexOfName){ // If the word is the first word there
		currNode->indices=currNode->indices->next;
		if(!currNode->indices && currNode->numNonNullBranches==0){
			lastBranchNode->numNonNullBranches--;
			recursiveDelete(lastBranchNode->branch[lastBranchChar]);
			lastBranchNode->branch[lastBranchChar]=nullptr;
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

listOfObjects<string> * Trie::completions(string prefix) {
	TrieNode *currNode = root;
	int len = prefix.length();
	listOfObjects<string> *currCompletions = nullptr;

	// Insert your code here
	for(int i=0;i<len;i++){
		int chr_idx = (prefix[i]|32)-'a';
		currNode=currNode->branch[chr_idx];
		if(!currNode)	return nullptr;
	}
	currCompletions=new listOfObjects<string>("\0");
	if(recursiveAddCompletions(currNode,currCompletions))
		return currCompletions->next;
	return nullptr;
	
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
	listOfObjects<int>* wordList=node->indices;
	while(wordList){
		string curr_word=nameDict->getKeyAtIndex(wordList->object);
		if(isPresentInCompletions(currCompletions,curr_word))	continue;
		listOfObjects<string>* to_add = new listOfObjects<string>(curr_word);
		to_add->next=currCompletions->next;
		currCompletions->next=to_add;
		wordList=wordList->next;
	}
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
