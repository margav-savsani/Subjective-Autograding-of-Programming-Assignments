#ifndef TRIE_CPP
#define TRIE_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef TRIE_H
#include "updated_Trie.h"
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
	// cout << "insertyo\n";
  TrieNode *currNode = root;
  int len = wordInName.length();

  // Insert your code here
  string currWord = wordInName;
	while (len > 0)
	{
		// cout << "nextIter\n";
		if (currNode->branch[(int(currWord[0])-65)] != nullptr)
		{
			// cout << "while->if\n";
			currNode = currNode->branch[(int(currWord[0])-65)];
			for (int i=0; i<len; i++)             // This loop is similar to currWord=currWord[1:]
				currWord[i]=currWord[i+1];
			len--;

			// cout << "len: "<< len << " while->ifo\n" << currWord << endl;
		}

		else 
		{
			// cout << "halt\n";
			TrieNode* newNode = new TrieNode();
			currNode->branch[(int(currWord[0])-65)] = newNode;
			currNode->numNonNullBranches++;
			if (len == 1)
				newNode->isWord = true;
				
			for (int i=0; i<len; i++)             // This loop is similar to currWord=currWord[1:]
				currWord[i]=currWord[i+1];
			len--;
			currNode = newNode;
		}
	
	}	
		// cout << "yoyo\n";
		if (currNode->isWord)
		{
			// cout << "isWeird\n";
			//listOfObjects<int> *indx;
			//indx = currNode->indices;
			if (currNode->indices == nullptr) currNode->indices = new listOfObjects<int> (indexOfName);
			else {listOfObjects<int> *index=currNode->indices;
				while (index != nullptr)
				{	
					if (index->next != nullptr) index = index->next;
					else {index->next = new listOfObjects<int> (indexOfName); break;}
				}
			}
			
		}
	
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here
  string currWord = wordInName;
  while (len > 0)
  {
   	// cout << "nextIter\n";
   	if (currNode->branch[int(currWord[0]) - 65] != nullptr) 
   	{
			// cout << currWord << len << endl;
			currNode = currNode->branch[(int(currWord[0])-65)];
			for (int i=0; i<len; i++)             // This loop is similar to currWord=currWord[1:]
				currWord[i]=currWord[i+1];
			len--;
    }
    
    else {cout << "No such Stations exists\n"; return false;}
	}                                        // This while loop makes the currNode to point at the last node of Trie
	
	
	if (currNode->isWord)
	{
		// cout << "true\n";
		listOfObjects<int> *index=currNode->indices;     // Note that currNode->indices must contains atleast one index, if not return false
		listOfObjects<int> *prev=currNode->indices;      // previous node of index
		while (index != nullptr)
		{
			if ((name == nameDict->getKeyAtIndex(index->object)) && (prev == index))     // This case occurs if the index to be removed is directly connected to currNode
				{/*cout << "inside If\n"; */prev = nullptr; break;}
			else if (name == nameDict->getKeyAtIndex(index->object))                     // This is for not the above case
				{/*cout << "inside elseIf\n"; */prev->next = index->next; break;}
			else {
				prev = index;
				index = index->next;
				// cout << "inside Else\n"; 
			}
		}
	}
	return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  currCompletions = new listOfObjects<string>("qwert");
	string currWord = prefix;
  // Insert your code here
  while (len > 0)
  {
  	if (currNode->branch[int(currWord[0]) - 65] != nullptr) {
			currNode = currNode->branch[(int(currWord[0])-65)];
			for (int i=0; i<len; i++)             // This loop is similar to currWord=currWord[1:]
				currWord[i]=currWord[i+1];
			len--;
  	}
  	
  	else {
  		cout << "No such station name with provided prefix exists\n";
  		break;
  	}
  }                                           // This while loop makes the currNode to point at the last node of Trie
  
  if (len == 0) recursiveAddCompletions(currNode, currCompletions);
  return currCompletions->next;
  
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
  if(node->isWord)
  {
  	listOfObjects<int> *currIndices = node->indices;
  	listOfObjects<string> *name = currCompletions;
  	while (currIndices != nullptr) {
			while(name->next != nullptr) name = name->next;
			name->next = new listOfObjects<string> (nameDict->getKeyAtIndex(currIndices->object));
			currIndices = currIndices->next;
  	}
  	
  	return true;
  }
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
