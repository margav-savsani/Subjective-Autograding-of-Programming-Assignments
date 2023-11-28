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

bool Trie::insert(string wordInName, int indexOfName)
{
	// Insert your code here

	TrieNode* temp = root;
	int currLen = 0;

	bool isPresent = false;
	// Go untill you reach the end of the word to be inserted and keep on inserting the new nodes if not already present.
	while(currLen < wordInName.length()){
		if(temp->branch[toupper(wordInName[currLen]) - 'A'] == nullptr){
			isPresent = true;
			temp->branch[toupper(wordInName[currLen]) - 'A'] = new TrieNode();
			temp->numNonNullBranches++;
		}
		temp = temp->branch[toupper(wordInName[currLen]) - 'A'];
		currLen++;
	}
	
	temp->isWord = true;

	// Case for initial insert
	if(temp->indices == nullptr){
		temp->indices = new listOfObjects<int>(indexOfName);
	}
	// Reach the end of the indices listOfObjects and then insert the index.
	else{
		listOfObjects<int>* temp2 = temp->indices;
		while(temp2->next!=nullptr){
			temp2 = temp2->next;
		}
		temp2->next = new listOfObjects<int>(indexOfName);
	}

	return true;
	
}

// function to delete the index of stationName from the indices list of a word
listOfObjects<int>* Trie::deleteIndexOfName(listOfObjects<int>* indices, string name){
	if(indices == nullptr) return nullptr; // This won't happen but still

	listOfObjects<int>* currIndex = indices;
	listOfObjects<int>* prevIndex = nullptr;

	if(currIndex->next == nullptr &&  nameDict->getKeyAtIndex(currIndex->object) == name){
		delete indices;
		return nullptr;
	}

	while(currIndex){
		if(nameDict->getKeyAtIndex(currIndex->object) == name){
			
			if(prevIndex == nullptr) indices = currIndex->next;
			else prevIndex->next = currIndex->next;
			delete currIndex;
			break;
		}
		prevIndex = currIndex;
		currIndex = prevIndex->next;
	}
	return indices;
}


// deletes the station index from the inices list of the word which is contained in the station name.
bool Trie::del(string wordInName, string name)
{
	TrieNode *currNode = root;
	// "lastBranchNode" and "lastBranchChar" is just to store the information that from where we should start recursively delete the word when indices become nullptr.
	TrieNode *lastBranchNode = nullptr;
	int lastBranchChar = -1;
	int len = wordInName.length();

	// Insert your code here
	if(!isPresent(wordInName)) return false;
	else{
		for(int i=0; i<len; i++){
			// getting the correct "lastBranchNode" and "lastBranchChar"
			if((currNode->numNonNullBranches > 1 || currNode->isWord) && currNode != root){
				lastBranchChar = i;
				lastBranchNode = currNode;
			}
			currNode = currNode->branch[toupper(wordInName[i]) - 'A'];
		}
		if(currNode->isWord){
			// deleting the correct index from the indices array.
			currNode->indices = deleteIndexOfName(currNode->indices, name);
			if(currNode->indices == nullptr){
				if(lastBranchChar == -1){
					recursiveDelete(root->branch[toupper(wordInName[0])-'A']);
					root->branch[toupper(wordInName[0])-'A'] = nullptr;
					root->numNonNullBranches--;
				}
				else {
					recursiveDelete(lastBranchNode->branch[toupper(wordInName[lastBranchChar])-'A']);
					lastBranchNode->branch[toupper(wordInName[lastBranchChar])-'A'] = nullptr;
					lastBranchNode->numNonNullBranches--;
				}
			}
		}
	}

	return true;
}


// Just creates a currentCompletions listOfObjects and store the list of completions in that using appropriately the two defined functions, "addCompletions()" and "recursiveAddCompletions()"
listOfObjects<string> *Trie::completions(string prefix)
{
	TrieNode *currNode = root;
	int len = prefix.length();
	listOfObjects<string> *currCompletions = new listOfObjects<string>("");

	for(int i=0;i<len; i++){
		if(!currNode->branch[toupper(prefix[i]) - 'A']) return currCompletions;
		else{
			currNode = currNode->branch[toupper(prefix[i]) - 'A'];
		}
	}
	
	recursiveAddCompletions(currNode, currCompletions);
	
	return currCompletions;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions)
{
	if (node->isWord)
	{
		if (!addCompletions(node, currCompletions))
		{
			return false;
		}
	}

	TrieNode *currNode = node;
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions)
{
	// Insert your code here
	listOfObjects<string> *currObj = currCompletions;
	
	while (currObj->next != nullptr)
	{
		currObj = currObj->next;
	}

	listOfObjects<int> *nodeObj = node->indices;
	while (nodeObj != nullptr)
	{
		if(!isPresentInCompletions(currCompletions, nameDict->getKeyAtIndex(nodeObj->object))){
			if(currObj->object == "") {
				currObj->object = nameDict->getKeyAtIndex(nodeObj->object);
			}
			else {
				currObj->next = new listOfObjects<string>(nameDict->getKeyAtIndex(nodeObj->object));
				currObj = currObj->next;
			}
		}
			nodeObj = nodeObj->next;
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
