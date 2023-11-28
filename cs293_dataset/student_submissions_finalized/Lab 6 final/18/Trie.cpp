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

  //if(isPresent(wordInName)) return false; //already present
  for (int i = 0; i < len; i++) {
    
    int letter = toupper(wordInName.at(i)) - 'A'; //- 'A' because indexing starts from one

    if (currNode->branch[letter] == nullptr) {
      TrieNode *new_child;
      new_child = new TrieNode();
      currNode->branch[letter] = new_child; //this branch becomes non null
      currNode->numNonNullBranches++; //num of non null branches increases
    }
    currNode = currNode->branch[letter];
    if(i==len-1){ //end of word
      if(!currNode->isWord){ //this is the case when there was no station with this word in its name existing in the trie before insert
        currNode->isWord=true;
        currNode->indices = new listOfObjects<int> (indexOfName); //a new linked list is created
      }
      else{ //when the word existed before
        listOfObjects<int> *A = currNode->indices;
        while(A->next != nullptr){
          A = A->next; //tail index of linked list is found
        }
        A->next = new listOfObjects<int> (indexOfName); //tail index is initialized
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
  if(!isPresent(wordInName)) return false; //not found
  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';
    if(currNode->numNonNullBranches>1){
      lastBranchNode = currNode; //if the number of branches of this node is more than 1, last branch node and character changes
      lastBranchChar = letter;
    }
    if(!currNode->isWord){
      currNode = currNode->branch[letter];
    }
  }
  //now currNode->isWord is true
  listOfObjects<int> *index = currNode->indices;
  if(nameDict->getKeyAtIndex(index->object) == name){ //this is the case when the given name is the first element in the list
    if(index->next!=nullptr) {
      currNode->indices = index->next;
      return true;
    }
    else{
      lastBranchNode->branch[lastBranchChar] = nullptr;
      return true;
    }
  }
  else{
    while(index->next!=nullptr){ //this is the case when the given name is not the first element in the list
      if(nameDict->getKeyAtIndex(index->next->object) == name){
        index->next = index->next->next;
        return true;
      }
      index=index->next;
    }
  }
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string> ("");

  // Insert your code here
  for (int i = 0; i < len; i++) {
    int letter = toupper(prefix.at(i)) - 'A';
    if (currNode->branch[letter] == nullptr) break; //if prefix not there
    currNode = currNode->branch[letter];
    if(i==len-1){
      recursiveAddCompletions(currNode, &currCompletions);
    }
  }
  return currCompletions->next;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> **currCompletions) {
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> **currCompletions) {

  // Insert your code here
  if (!node->isWord) return false;
  listOfObjects<int> *index = node->indices;
  while((*currCompletions)->next != nullptr){
    currCompletions = &((*currCompletions)->next); //find the tail index of currCompletions
  }
  while(index != nullptr){ //appending the linked list of indices to currCompletions
    string key = nameDict->getKeyAtIndex(index->object);
    (*currCompletions)->next = new listOfObjects<string> ("");
    (*currCompletions)->next->object = key;
    currCompletions = &((*currCompletions)->next);
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
