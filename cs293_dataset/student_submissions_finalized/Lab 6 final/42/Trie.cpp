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
  for(int i=0;i<len;i++){ // traversing the trie
      if ((currNode->branch)[toupper(wordInName[i]) - 'A'] == nullptr){
          (currNode->branch)[toupper(wordInName[i]) - 'A'] = new TrieNode();
          if ((currNode->branch)[toupper(wordInName[i]) - 'A'] == nullptr) {
              cout << "Memory allocation failure." << endl;
              return false;
          }
      }
      currNode->numNonNullBranches++; //incrementing numnonnullbranches
      currNode = (currNode->branch)[toupper(wordInName[i]) - 'A'];
  }
  currNode->isWord = true; //changing isWord to true if not already true
  if (currNode->indices == nullptr){ // if linked list was not initialised
      (currNode->indices) = new listOfObjects<int>(indexOfName); // initialising
      return true;
  }
  listOfObjects<int> *node = (currNode->indices);
  while (node->next != nullptr){
      node = node->next; //finding place to insert in linked list
  }
  node->next = new listOfObjects<int>(indexOfName); // inserting a new integer into the linked list
  
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastNode = root; // checks for the last point of branching, or the last node in the path which 
  bool is_leaf = true;
  int del_index = toupper(wordInName[0]) - 'A';
  int len = wordInName.length();


  // Insert your code here

  for (int i=0;i<len;i++){
      if ((currNode->branch)[toupper(wordInName[i]) - 'A'] == nullptr){
          cout<<"Word is not present in the trie"<<endl;
          return false;
      }
      if ((currNode->numNonNullBranches > 1) || (currNode->isWord)){
          lastNode = currNode;
          del_index = toupper(wordInName[i]) - 'A';
      }
      currNode = (currNode->branch)[toupper(wordInName[i]) - 'A'];
  }
  if (!(currNode->isWord)) return false;
  if (currNode->numNonNullBranches > 0) is_leaf = false;

  listOfObjects<int> *node = (currNode->indices);
  listOfObjects<int> *extra = nullptr;
  if (node->next == nullptr){
      if (nameDict->getKeyAtIndex(node->object) != name){
          cout<<"The station "<<name<<" is not part of the list of stations"<<endl;
          return false;
      }
      currNode->isWord = false;
      delete currNode->indices;
      currNode->indices = nullptr;
      if (is_leaf){
          recursiveDelete(lastNode->branch[del_index]);
          lastNode->branch[del_index] = nullptr;
          lastNode->numNonNullBranches-=1;
      }
      return true;
  }
  if (nameDict->getKeyAtIndex(node->object) == name){
      (currNode->indices) = node->next;
      delete node;
      return true;
  }
  while (node->next != nullptr){
      if (nameDict->getKeyAtIndex((node->next)->object) == name){
          extra = (node->next)->next;
          delete node->next;
          node->next = extra;
          return true;
      }
      node = node->next;
  }

  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here
  for(int i=0;i<len;i++){
      if ((currNode->branch)[toupper(prefix[i]) - 'A'] == nullptr){
          return nullptr;
      }
      currNode = (currNode->branch)[toupper(prefix[i]) - 'A'];
  }
  recursiveAddCompletions(currNode, currCompletions);
  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string>* &currCompletions) {
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string>* &currCompletions) {

  // Insert your code here
  if (node == nullptr) return false;
  listOfObjects<int> *index = node->indices;
  if (index == nullptr) return false;
  if (currCompletions == nullptr){
      currCompletions = new listOfObjects<string>(nameDict->getKeyAtIndex(index->object));
      index = index->next;
  }
  listOfObjects<string>* pos_insert = currCompletions;
  while (pos_insert->next != nullptr){
      pos_insert = pos_insert->next;
  }
  while (index != nullptr){
      if (!isPresentInCompletions(currCompletions,nameDict->getKeyAtIndex(index->object))){
          pos_insert->next = new listOfObjects<string>(nameDict->getKeyAtIndex(index->object));
          pos_insert = pos_insert->next;
      }
      index = index->next;
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
