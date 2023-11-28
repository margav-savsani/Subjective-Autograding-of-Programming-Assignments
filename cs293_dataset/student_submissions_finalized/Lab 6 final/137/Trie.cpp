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

void Trie::updateindexOfName(listOfObjects<int> *indices, int indexOfName){
  //Function to update the indices list of a node with isWord true. 
  listOfObjects<int> *index = indices;
  while(indices->next != nullptr)
  {
    indices = indices->next;
  }
  indices->next = new listOfObjects<int>(indexOfName);
  return;
}

bool Trie::insert(string wordInName, int indexOfName) {
  //Function to insert strings in the trie.
  TrieNode *currNode = root;
  int len = wordInName.length();

  // Insert your code here
  for(int i = 0; i<len; i++)
  {
    int letter = int(wordInName[i]) - 65;
    if(letter < 0 || letter >= NUM_CHARS)
    {
      letter = letter - 32;
    }
    if(i<len-1)
    {
      if(currNode->branch[letter] == NULL)
      {
        currNode->branch[letter] = new TrieNode();   //creating a new node if the branch is null
        currNode->numNonNullBranches++;
        currNode = currNode->branch[letter];
      }
      else
      {
        currNode = currNode->branch[letter];
      }
    }
    else
    {
      if(currNode->branch[letter] == NULL)
      {
        currNode->branch[letter] = new TrieNode();
        currNode->numNonNullBranches++;
        currNode = currNode->branch[letter];
        currNode->isWord = true;
        currNode->indices = new listOfObjects<int>(indexOfName);     //adding indexOfName in the indices of the node.
        return true;
      }
      else
      {
        currNode = currNode->branch[letter];
        if(!currNode->isWord)
        {
          currNode->isWord = true;
          currNode->indices = new listOfObjects<int>(indexOfName);
          return true;
        }
        else
        {
          updateindexOfName(currNode->indices,indexOfName);    //calling the updateindexOfName function to insert indexOfName in the indices of the node.
          return true;
        }
      }
    }
  }
  return false;
}

void Trie::deleteindexofName(listOfObjects<int> *indices, int indexOfName){
  //function to delete indexOfName from the indices of the node.
  if(indices->next->object == indexOfName)
  {
    indices->next = indices->next->next;
  }
  else
  {
    deleteindexofName(indices->next, indexOfName);
  }
}

void Trie::deletewordInName(string wordInName, listOfObjects<TrieNode*> *multi){
  //function to delete the word from trie if it has only one value in the indices list.
  TrieNode *currNode = root;
  int len = wordInName.length();
  for(int i=0; i<len; i++)
  {
    int letter = int(wordInName[i]) - 65;
    if(letter < 0 || letter >= NUM_CHARS)
    {
      letter = letter - 32;
    }
    if(multi->next != NULL)
    {
      if(currNode == multi->object)   //removing the node from multi if we traverse it.
      {
        multi = multi->next;
      }
    }
    if(multi->next == NULL)
    {
      currNode->branch[letter] = nullptr;    //removing the word from the trie.
      break;
    }
    currNode = currNode->branch[letter];   //moving to the child node.
  }
  return;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  listOfObjects<TrieNode*> *multi = NULL;   //list to store all the nodes of a word which have more than one child node.
  listOfObjects<TrieNode*> *temp = NULL;

  // Insert your code here
  if(isPresent(wordInName))   //checking is the word is present in trie.
  {
    for(int i=0; i<len; i++)
    {
      int letter = int(wordInName[i]) - 65;
      if(letter < 0 || letter >= NUM_CHARS)
      {
        letter = letter - 32;
      }
      currNode = currNode->branch[letter];
      if(currNode->numNonNullBranches > 1 || currNode->isWord == true)    //adding the nodes with more than one child nodes to multi.
      {
        if(multi == NULL)
        {
          multi = new listOfObjects<TrieNode*>(currNode);
          temp = multi;
        }
        else
        {
          multi->next = new listOfObjects<TrieNode*>(currNode);
          multi = multi->next;
        }
      }
      if(i==len-1)    //deleting the index value.
      {
        if(currNode->indices->object == nameDict->get(name)->value)
        {
          if(currNode->indices->next != NULL)   //checking if index is the only element in the indices list.
          {
            currNode->indices = currNode->indices->next;
          }
          else
          {
            if(currNode->numNonNullBranches > 0)
            {
              currNode->indices = nullptr;
              currNode->isWord = false;
            }
            else
            {
              multi = temp;
              deletewordInName(wordInName , multi);   //deleting the word if index is the only word in the indices list.
            }
          }
        }
        else
        {
          deleteindexofName(currNode->indices, nameDict->get(name)->value);
        }
      }
    }
    return true;
  }
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  //function to compute all the station names from a given prefix.
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here
  for(int i=0; i<len; i++)
  {
    int letter = int(prefix[i]) - 65;
    if(letter<0 || letter>= NUM_CHARS)
    {
      letter = letter - 32;
    }
    currNode = currNode->branch[letter];
  }
  recursiveAddCompletions(currNode,currCompletions);    //adding station names to the list.
  if(currCompletions->next != NULL)
  {
    if(currCompletions->object == currCompletions->next->object)
    {
      return currCompletions->next;
    }
    else
    {
      return currCompletions;
    }
  }
  else
  {
    return currCompletions;
  }
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
  if (node->isWord) {
    if(currCompletions == NULL)
    {
      currCompletions = new listOfObjects<string>(nameDict->getKeyAtIndex(node->indices->object));
    }
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
  //function to add station name to the completions list.
  // Insert your code here
  listOfObjects<int> *index = node->indices;
  listOfObjects<string> *com = currCompletions;
  if(com != NULL)
  {
    while(com->next != NULL)
    {
      com = com->next;
    }
  }
  while(index != NULL)
  {
    if(com == NULL)
    {
      com = new listOfObjects<string>(nameDict->getKeyAtIndex(index->object));
    }
    else
    {    
      if(!isPresentInCompletions(currCompletions, nameDict->getKeyAtIndex(index->object)))    //checking if a completion is present in the list.
      {
        com->next = new listOfObjects<string>(nameDict->getKeyAtIndex(index->object));    //adding the station name to the list.
        com = com->next;
      }
    }
    index = index->next;
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
    if(letter < 0 || letter >= NUM_CHARS)
    {
      letter = letter - 32;
    }
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
