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
  for ( auto it:wordInName ){
    char letter = toupper(it);
    int charvalue = letter - 'A';

    if( currNode->branch[charvalue] == nullptr ){
      currNode->branch[charvalue] = new TrieNode;
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[charvalue];
  }

  currNode->isWord = true;
  listOfObjects<int> *newnode = new listOfObjects<int>(indexOfName);
  newnode->next = currNode->indices;
  currNode->indices = newnode;

  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = toupper(wordInName[0]) - 'A';
  int len = wordInName.length();

  for ( int i = 0; i < len ; i++ ){

    char it = wordInName[i];

    char letter = toupper(it);
    int charvalue = letter - 'A';

    if(currNode->isWord || currNode->numNonNullBranches > 1 || currNode == root){
      lastBranchNode = currNode;
      lastBranchChar = charvalue;
    }

    if( currNode->branch[charvalue] == nullptr ){
      return false;
    }
    currNode = currNode->branch[charvalue];


  }

  // char it = wordInName[len-1];
  // char letter = toupper(it);
  // int charvalue = letter - 'A';

  // if( currNode->branch[charvalue] == nullptr ){
  //   return false;
  // }
  // currNode = currNode->branch[charvalue];
  
  if (!currNode->isWord){
    return false;
  }

  listOfObjects<int>* first = currNode->indices;
  listOfObjects<int>* second = currNode->indices->next;

  if( nameDict->getKeyAtIndex(first->object) == name ){
    currNode->indices = second;
    delete first;
    cout<< currNode->numNonNullBranches;
    if(currNode->indices == NULL){
      currNode->isWord = false;
      if(currNode->numNonNullBranches == 0){
        cout<< "deleting dead end"<<endl;
        cout<< lastBranchChar << " "<<endl;
        recursiveDelete(lastBranchNode->branch[lastBranchChar]);
        lastBranchNode->branch[lastBranchChar] = nullptr;
      }
    }
    return true;  
  }

  while( ((second != NULL) ? nameDict->getKeyAtIndex(second->object) : name) != name){
    first = first->next;
    second= second->next;
  }

  if(second == NULL){
    return false;
  }

  first->next = second->next;
  delete second;
  currNode->numNonNullBranches--;
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  for ( auto it:prefix ){
    char letter = toupper(it);
    int charvalue = letter - 'A';
    if(currNode->branch[charvalue] == NULL){
      return currCompletions;
    }

    currNode = currNode->branch[charvalue];
  }
  
  recursiveAddCompletions(currNode, currCompletions);
  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {

  // Insert your code here
  if(node->isWord){
    listOfObjects<int> *temp = node->indices;

    while( temp != nullptr){
      listOfObjects<string>* next_name = new listOfObjects<string>(nameDict->getKeyAtIndex(temp->object));
      next_name->next = currCompletions;
      currCompletions = next_name;
      temp = temp->next;
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
