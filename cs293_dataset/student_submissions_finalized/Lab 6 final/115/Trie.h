#ifndef TRIE_H
#define TRIE_H

#ifndef DICTONARY_H
#include "dictionary.h"
#endif

using namespace std;

#define NUM_CHARS 26

class TrieNode
{
	public:
	bool isWord; //Its true only when the word is ended
	listOfObjects<int> *indices; // Indices in stnNameToIndex (also referred to as nameDict in the Trie class) dictionary; non-null only if isWord is true
	int numNonNullBranches;//no of no null branches out of 26 branches
	TrieNode *branch[NUM_CHARS];//pointers to all 26 branches
	// Constructor
	TrieNode()
	{
		isWord = false;//default value is false, because many characters are not at the ending in the word
		indices = nullptr;//default value is NULL, because isWord is false
		numNonNullBranches = 0;
		for (int i = 0; i < NUM_CHARS; i++)
		{
			branch[i] = nullptr;
		}
	}

	// Destructor
	~TrieNode()
	{
		listOfObjects<int> *currIndex = indices;
		while (currIndex != nullptr)
		{
			listOfObjects<int> *toDeleteIndex = currIndex;
			currIndex = currIndex->next;
			delete toDeleteIndex;
		}
	}
};

class Trie
{
 	private:
	Dictionary<int> *nameDict;//dictionary where the entire name of the station name is stored by hashing
	TrieNode *root;
	void recursiveDelete(TrieNode *node);
	void addCompletions(TrieNode *node, listOfObjects<string>* currCompletions);
	listOfObjects<string>* addCompletions_main(TrieNode *node);
	
 	public:
	Trie(Dictionary<int> *nameToIndex);
	~Trie();
	
	bool insert(string wordInName, int indexOfName);
	bool del(string wordInName, string name);
	listOfObjects<string> *completions(string prefix);

	void printTrie();
	void recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight);
};
#endif