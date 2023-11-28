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

Trie::~Trie() {
	recursiveDelete(root);
}

void Trie::recursiveDelete(TrieNode *node)
{
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

//inserts the given word in total name, and also adds the index of the entire name at the end of listofobjects<int>
bool Trie::insert(string wordInName, int indexOfName)
{
	TrieNode *currNode = root;
	if(currNode==NULL)
	{
		return false;
	}
	int len = wordInName.length();
	if(len>0)
	{
		for(int i=0;i<len;i++)
		{
			int a = wordInName[i];
			if(!(a>=97 && a<97+26 ||a>=65 && a<65+26))//checking for all charcters in the prefic are alphabets or not
			{
				return false;
			}
			if(currNode->branch[a%32-1]==NULL)
			{
				currNode->branch[a%32-1]=new TrieNode();
				currNode->numNonNullBranches++;
				currNode=currNode->branch[a%32-1];
				if(i==len-1)
				{
					currNode->isWord=true;
					currNode->indices=new listOfObjects<int>(indexOfName);
				}
			}
			else//if it is not the null branch
			{
				currNode=currNode->branch[a%32-1];
				if(i==len-1)
				{
					if(currNode->isWord==false)
					{
						currNode->isWord=true;
						currNode->indices= new listOfObjects<int>(indexOfName);
					}
					else
					{
						listOfObjects<int>* index=currNode->indices;
						while(true)
						{
							if(index->next==NULL)
							{
								break;
							}
							index=index->next;
						}
						index->next=new listOfObjects<int>(indexOfName);
					}
				}
				
			}
		}
		return true;
	}
	else//if string is empty
	{
		return false;
	}
}

bool Trie::del(string wordInName, string name)//just delete the all the words of station name in the trie 
{
	TrieNode *lastBranchNode = root;
	TrieNode *lastButoneBranchNode = NULL;
	TrieNode *lastButoneBranchNode_dum = NULL;
	int delete_index=-1;
	int delete_index_dum=-1;
	int lastBranchChar = -1;
	int len = wordInName.length();
	if(len<=0||root==NULL)
	{
		return false;
	}

	for(int i=0;i<len;i++)
	{
		lastBranchChar=int(wordInName[i]);
		if(!((lastBranchChar>=65&&lastBranchChar<65+26)||(lastBranchChar>=97&&lastBranchChar<97+26)))//checking for all charcters in the prefic are alphabets or not
		{
			return false;
		}
		lastBranchNode=lastBranchNode->branch[(lastBranchChar%32)-1];
		if(lastBranchNode==NULL)
		{
			return false;
		}
		if(lastBranchNode->isWord || lastBranchNode->numNonNullBranches>1)
		{//all this work is for after deleting a word, another word which has common letter with the word should not be deleted
			if(i<len-1)
			{
				lastBranchChar=int(wordInName[i+1]);
			}
			lastButoneBranchNode=lastButoneBranchNode_dum;
			delete_index=delete_index_dum;
			lastButoneBranchNode_dum=lastBranchNode;
			delete_index_dum=(lastBranchChar%32)-1;
		}
	}
	int i=0;
	bool found=false;
	listOfObjects<int>* new_Indices=lastBranchNode->indices;
	listOfObjects<int>* new_Indices_dum=lastBranchNode->indices;
	while(new_Indices_dum!=NULL)
	{
		if(i==0 && name==nameDict->getKeyAtIndex(new_Indices_dum->object))
		{
			found=true;
			lastBranchNode->indices=lastBranchNode->indices->next;
			if(lastBranchNode->indices==NULL && lastBranchNode->numNonNullBranches>0)
			{
				lastBranchNode->isWord=false;
				return true;
			}
			else if(lastBranchNode->indices==NULL && lastBranchNode->numNonNullBranches==0)
			{
				if(lastButoneBranchNode!=NULL)
				{
					lastButoneBranchNode->branch[delete_index]=NULL;
					lastButoneBranchNode->numNonNullBranches--;
				}
				else
				{
					root->branch[int(wordInName[i])%32-1]=NULL;
					root->numNonNullBranches--;
				}
				return true;
			}
			return true;
		}
		if(i>0 && name==nameDict->getKeyAtIndex(new_Indices_dum->object))
		{
			found=true;
			new_Indices->next=new_Indices_dum->next;
			return true;
		}
		new_Indices=new_Indices_dum;
		new_Indices_dum=new_Indices_dum->next;
		i++;
	}
	return found;
}


//completions function moves the node to the end of prefix, and calls the addcompletions_main function 
listOfObjects<string> * Trie::completions(string prefix)
{
	TrieNode *currNode = root;
	int len = prefix.length();
	listOfObjects<string> *currCompletions = nullptr;
	if(len==0)
	{
		return NULL;
	}
	for(int i=0;i<len;i++)
	{
		int a=int(prefix[i]);
		if(!((a>=65 && a <65+26) || (a>=97 && a<97+26)))//checking for all charcters in the prefic are alphabets or not
		{
			return NULL;
		}
		if(currNode->branch[a%32 -1]==NULL)
		{
			return NULL;
		}
		currNode=currNode->branch[a%32-1];
	}
	currCompletions=addCompletions_main(currNode);
	return currCompletions;
}


//This function doesn't take listOfObjects as input and returns that list, this is the difference between addcompletions and addcompletions_main
listOfObjects<string>* Trie::addCompletions_main(TrieNode *node)
{
	listOfObjects<string>* All_Completions=new listOfObjects<string>("idk");
	addCompletions(node,All_Completions);
	listOfObjects<string>* Dummy=All_Completions->next;
	delete All_Completions;
	//because I intially added one element because it will pass null, if I don't initialise with one element
	All_Completions=Dummy;
	return All_Completions;
}


//This takes in listOfObjects and move it to the end of the list, and then it adds the strings below it
void Trie::addCompletions(TrieNode *node, listOfObjects<string>* All_Completions)
{
	while(true)
	{
		if(All_Completions->next==NULL)
		{
			break;
		}
		All_Completions=All_Completions->next;
	}
	//moving till we get the null pointer

	if(node->isWord)// if its a end of a word, then add all words at this node and keep adding recursively in the children of this node
	{
		listOfObjects<int>* newone = node->indices;
		while(newone!=NULL)
		{
			All_Completions->next=new listOfObjects<string>(nameDict->getKeyAtIndex(newone->object));
			All_Completions=All_Completions->next;
			newone=newone->next;
		}
	}

	//if there is branch which is not a null, then add all the words in it too
	if(node->numNonNullBranches>0)
	{
		for(int i=0;i<NUM_CHARS;i++)
		{
			if(node->branch[i]!=NULL)
			{
				addCompletions(node->branch[i],All_Completions);
			}
		}
	}
	return;
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
		if (node->isWord)
		{
			cout << "(isWord)";
			listOfObjects<int> *currIndices = node->indices;
			while (currIndices != nullptr)
			{
				cout << endl << prefix << "     " << nameDict->getKeyAtIndex(currIndices->object);
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
			for (int j = i+1; j < NUM_CHARS; j++)
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
