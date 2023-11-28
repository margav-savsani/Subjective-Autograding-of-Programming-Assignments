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
	if (root==nullptr) return false;
	TrieNode *currNode = root;
	int len = wordInName.length();
	
	for (int i =0;i<len;i++){
		int charindex = (toupper(wordInName.at(i)) - 'A');
		if (currNode->branch[charindex] == nullptr) {//create necessary nodes 
			currNode->branch[charindex] = new TrieNode();
			currNode->numNonNullBranches++;
		}
		currNode = currNode->branch[charindex]; 
	}
	if (!(currNode->isWord)){ // wasnt a word node yet
		currNode->indices= new listOfObjects<int>(indexOfName);
		currNode->isWord = true; 
		return true;
	} 
	//is a word node already
	listOfObjects<int> * currlist;
	for (currlist = currNode->indices;currlist->next!=nullptr;currlist = currlist->next)
		if(currlist->object==indexOfName) return false; //already present	
	
	currlist->next = new listOfObjects<int>(indexOfName);
	return true;
}

bool Trie::del(string wordInName, string name) {
	//getting index from name
	Entry<int>* entry = nameDict->get(name);
	if (entry==nullptr) return false;
	int indexval = entry->value;


	TrieNode *currNode = root;
	TrieNode *LastBranchPoint=root; // last point where branching happened or another word present
	int ChildAtLastBranch; // our string is in which branch of the lastbranchpoint? - as int
	int len = wordInName.length();
	
	for (int i =0;i<len;i++){//trie traversal
		int charindex = (toupper(wordInName.at(i)) - 'A');
		if (currNode->branch[charindex] == nullptr) return false;
		if (currNode->numNonNullBranches>1||(currNode->isWord&&i!=len-1)){// conditions for updating branch points
			LastBranchPoint = currNode;
			ChildAtLastBranch = charindex;
		}
		currNode = currNode->branch[charindex]; 
	}
	if (!(currNode->isWord)||(currNode->indices==nullptr)) return false;
//going over linked list
	listOfObjects<int> * currlist,*prevlist=nullptr;
	for (currlist = currNode->indices;currlist->object!=indexval&&currlist->next!=nullptr;currlist = currlist->next){prevlist=currlist;}
	if (currlist->object!=indexval) return false;

	if (prevlist==nullptr){ // in case first element in LL
		currNode->indices = currlist->next;
		if (currNode->indices==nullptr){
			currNode->isWord = false; //not a word anymore
			if (currNode->numNonNullBranches==0&&LastBranchPoint!=currNode){
				LastBranchPoint->numNonNullBranches--;
				// remove the "linear" branch
				recursiveDelete(LastBranchPoint->branch[ChildAtLastBranch]);
				LastBranchPoint->branch[ChildAtLastBranch] = nullptr;
			}
		}
	}
	else{ // when not first element of list just regular LL deletion
		prevlist->next = currlist->next;
	}		
	delete currlist; // free that removed node
	return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
	TrieNode *currNode = root;
	int len = prefix.length();
	//traverse down trie
	for (int i =0;i<len;i++){
		int charindex = (toupper(prefix.at(i)) - 'A');
		if (currNode->branch[charindex] == nullptr) return nullptr;
		currNode = currNode->branch[charindex]; 
	}

	listOfObjects<string> currCompletions = listOfObjects<string>(""); // makes life easy, we ignore it later
	recursiveAddCompletions(currNode,&currCompletions);
	return currCompletions.next;
	
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
	if (node==nullptr||currCompletions==nullptr) return false;

	for(listOfObjects<int>*ind = node->indices; ind!=nullptr; ind=ind->next){//read over indices list
		listOfObjects<string>* newstr = new listOfObjects<string>(nameDict->getKeyAtIndex(ind->object));//get corresponding stname from int
		newstr->next=currCompletions->next; // add to completions
		currCompletions->next = newstr;
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

#endif

