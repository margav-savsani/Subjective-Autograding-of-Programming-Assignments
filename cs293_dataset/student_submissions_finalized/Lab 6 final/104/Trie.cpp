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

Trie::Trie(Dictionary<int> *nameToIndex)
{
	nameDict = nameToIndex;
	root = new TrieNode();
	if (root == nullptr)
	{
		cout << "Memory allocation failure." << endl;
		exit(-1);
	}
}

Trie::~Trie()
{
	recursiveDelete(root);
}

void Trie::recursiveDelete(TrieNode *node)
{
	if (node == nullptr)
	{
		return;
	}
	else
	{
		for (int i = 0; i < NUM_CHARS; i++)
		{
			TrieNode *currNode = node->branch[i];
			recursiveDelete(currNode);
			node->branch[i] = nullptr;
		}
		if (node != root)
		{
			delete node;
		}
		return;
	}
}

// inserting a particular word in trie and pointing it to it's index in dictionary
bool Trie::insert(string wordInName, int indexOfName)
{
	TrieNode *currNode = root;
	int len = wordInName.length();

	// traversing the trie until we reach the required word
	for(int i=0; i<len; ++i){
		int indx = (int)(tolower(wordInName[i])) - 97;

		// if the letter is already present
		if( currNode->branch[indx] != nullptr){
			currNode = currNode->branch[indx];
		}
		// if letter isn't present then we will create a new node for that letter
		else{
			currNode->branch[indx] = new TrieNode();

			// updating number of non-null branches
			currNode->numNonNullBranches = currNode->numNonNullBranches + 1;
			currNode = currNode->branch[indx];
		}
	}

	// pointer to linked list of indices
	listOfObjects<int> *ptr = currNode->indices;

	// searching if index is already present in the linked list
	while(ptr != nullptr){
		if(ptr->object == indexOfName){
			return false;
		}

		ptr = ptr->next;
	}
	
	// I am inserting new node at the head of linked list
	ptr = currNode->indices;

	// pointing head to new node
	currNode->indices = new listOfObjects<int>(indexOfName);

	// pointing new node to previous first node
	currNode->indices->next = ptr;

	// setting isWord to true
	currNode->isWord = true;

	return true;
}

bool Trie::del(string wordInName, string name)
{	
	// to keep track of the word
	TrieNode *currNode = root;

	// to keep track of the last node from where only single branch is there
	TrieNode *lastBranchNode = nullptr;
	int lastBranchChar = -1;
	int len = wordInName.length();

	// traversing the trie along the wordInName
	for(int i=0; i<len; ++i){
		int indx = (int)(tolower(wordInName[i])) - 97;
		if( currNode->branch[indx] != nullptr){

			// setting lastBranchNode and lastBranchChar appropriately
			if(currNode->numNonNullBranches > 1 || currNode->isWord){
				lastBranchNode = currNode;
				lastBranchChar = indx;
			}

			currNode = currNode->branch[indx];
		}
		else{
			return false;
		}
	}

	// getting the pointer to name in dictionary
	Entry<int> *index_ptr = nameDict->get(name);

	if(index_ptr == nullptr){
		return false;
	}

	// getting the index of name in dictionary
	int hashVal = index_ptr->value;

	listOfObjects<int> *ptrNext = currNode->indices;
	listOfObjects<int> *ptrPrev = nullptr;

	int count = 0;

	// getting number of nodes in linked list
	while(ptrNext != nullptr){
		count ++;
		ptrNext = ptrNext->next;
	}

	ptrNext = currNode->indices;

	// deleting the index of name from linked list
	while( ptrNext != nullptr){

		// if the index is found
		if(ptrNext->object == hashVal){

			// if it is not the first node in linnked list
			if(ptrPrev != nullptr){
				ptrPrev->next = ptrNext->next;
				delete ptrNext;
				return true;
			}
			// if it is the first node in linked list
			else{

				// if list has more than 1 nodes
				if(count > 1){
					currNode->indices = currNode->indices->next;
					return true;
				}

				// if node has no children meaning it's a leaf
				if(currNode->numNonNullBranches == 0){

					// delete the branch containing the node
					recursiveDelete(lastBranchNode->branch[lastBranchChar]);
					lastBranchNode->branch[lastBranchChar] = nullptr;
					lastBranchNode->numNonNullBranches = lastBranchNode->numNonNullBranches - 1; 
					return true;
				}
				else{
					// for case like "ABCD" and "ABCDEF" both are preseent and we are deleting "ABCD"
					currNode->isWord = false;
					return true;
				}
			}
		}
		else{
			ptrPrev = ptrNext;
			ptrNext = ptrNext->next;
		}
	}

	return false;
}

listOfObjects<string> *Trie::completions(string prefix)
{
	TrieNode *currNode = root;
	int len = prefix.length();
	listOfObjects<string> *currCompletions = nullptr;

	// traversing till we reach the end of prefix
	for(int i=0; i<len; ++i){
		int indx = (int)(tolower(prefix[i])) - 97;
		if(currNode->branch[indx] == nullptr){
			// if prefix is not present
			return currCompletions;
		}
		else{
			currNode = currNode->branch[indx];
		}
	}

	recursiveAddCompletions(currNode, currCompletions);

	return currCompletions;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions)
{	
	// safety case
	if(node == nullptr){
		return false;
	}

	// if node is a word then add all the pointed stations by that node to currCompletions
	if (node->isWord)
	{
		if (!addCompletions(node, currCompletions))
		{
			return false;
		}
	}

	TrieNode *currNode = node;

	// calling the function recurrsively on each of it's children
	for (int i = 0; i < NUM_CHARS; i++)
	{
		if (currNode->branch[i] != nullptr)
		{
			if (!recursiveAddCompletions(currNode->branch[i], currCompletions))
			{
				return false;
			}
		}
	}

	return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions)
{	
	// safety case
	if(node == nullptr){	
		return false;
	}

	listOfObjects<int> *ptr = node->indices;

	// adding all the indices in the linked list to currCompletions
	while(ptr != nullptr){
		cout << "lmao" << endl;
		string s = nameDict->getKeyAtIndex(ptr->object);

		listOfObjects<string> *temp = currCompletions;
		currCompletions = new listOfObjects<string>(s);
		currCompletions->next = temp;
		ptr = ptr->next;
	}

	return true;
}

bool Trie::isPresentInCompletions(listOfObjects<string> *completions, string name)
{
	listOfObjects<string> *currCompletion = completions;
	bool isPresent = false;
	while (currCompletion != nullptr)
	{
		if (currCompletion->object == name)
		{
			isPresent = true;
			break;
		}
		currCompletion = currCompletion->next;
	}
	return isPresent;
}

void Trie::freeCompletionList(listOfObjects<string> *completions)
{
	listOfObjects<string> *currCompl = completions;
	while (currCompl != nullptr)
	{
		listOfObjects<string> *toDeleteCompl = currCompl;
		currCompl = currCompl->next;
		delete toDeleteCompl;
	}
	return;
}

bool Trie::isPresent(string wordInName)
{
	TrieNode *currNode = root;
	int len = wordInName.length();

	for (int i = 0; i < len; i++)
	{
		int letter = toupper(wordInName.at(i)) - 'A';

		if (currNode->branch[letter] == nullptr)
		{
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

void Trie::recursivePrintTrie(TrieNode *node, const string &prefix, int branchId, bool siblingsToRight)
{
	if (node != nullptr)
	{
		cout << prefix;

		cout << ((branchId == 0) ? "|-" : (branchId == -1) ? " *"
														   : "|_")
			 << (char)((branchId != -1) ? 'A' + branchId : '*');
		cout << ((branchId == 0) ? '-' : (branchId == -1) ? '*'
														  : '_');

		// If this trie node has isWord set to true, print "(isWord)" and
		// also the list of complete station names (accessed through indices
		// in nameDict) associated with this trie node.
		if (node->isWord)
		{
			cout << "(isWord)";
			listOfObjects<int> *currIndices = node->indices;
			while (currIndices != nullptr)
			{
				cout << endl
					 << prefix << "     " << nameDict->getKeyAtIndex(currIndices->object);
				currIndices = currIndices->next;
			}
		}
		else
		{
			cout << "()";
		}
		cout << endl;
		for (int i = 0; i < NUM_CHARS; i++)
		{
			TrieNode *currNode = node->branch[i];
			bool childrenToRight = false;
			for (int j = i + 1; j < NUM_CHARS; j++)
			{
				if (node->branch[j] != nullptr)
				{
					childrenToRight = true;
					break;
				}
			}
			if (currNode != nullptr)
			{
				recursivePrintTrie(currNode, prefix + ((siblingsToRight) ? "│   " : "    "), i, childrenToRight);
			}
		}
	}
}
// End edit version 1

#endif
