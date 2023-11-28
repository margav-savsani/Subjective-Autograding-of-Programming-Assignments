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

int findindex(char c){
  return (toupper(c) - 'A') ;
}

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

  for(int i=0; i<len; i++){
    while (currNode->branch[findindex(wordInName[i])] != nullptr){
      currNode = currNode->branch[findindex(wordInName[i])];
      i++;
      if (i == len){
        currNode->isWord = true;
        listOfObjects<int> *curr = currNode->indices;
        if (curr == NULL){
          currNode->indices = new listOfObjects(indexOfName);
          return true;
        }

        while(curr->next != NULL){
          curr = curr->next;
        }
        curr->next = new listOfObjects(indexOfName);
        return true;
        
      }
    }

    currNode->numNonNullBranches += 1;
    TrieNode *newNode = new TrieNode();
    currNode->branch[findindex(wordInName[i])] = newNode;
    currNode = newNode; 
    if (i == len-1) { 
      currNode->isWord = true;
      listOfObjects<int> *curr = newNode->indices;
      newNode->indices = new listOfObjects(indexOfName);
      return true;
    }
        
  }

  return false;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = -1;
  int len = wordInName.length();
  int k = 0;

  for( int i=0 ; i < len; i++){
    currNode = currNode->branch[findindex(wordInName[i])];
    if ((currNode->isWord || currNode->numNonNullBranches > 1) && i != len-1){
      lastBranchNode = currNode;
      k = i+1;
    }
  }
  listOfObjects<int>* currindex = currNode->indices;
  listOfObjects<int>* previndex = nullptr;
  while(nameDict->getKeyAtIndex(currindex->object) != name){
    previndex = currindex;
    currindex = currindex->next;
  }
  if (previndex == nullptr){
    if(currindex->next == nullptr) {currNode->indices = nullptr; currNode->isWord=false;}
    else currNode->indices = currindex->next;
  }
  else{
    previndex->next= currindex->next;
  }

  if (currNode->isWord || currNode->numNonNullBranches > 0) return true;
  else{
    recursiveDelete(lastBranchNode->branch[findindex(wordInName[k])]);
    lastBranchNode->branch[findindex(wordInName[k])] = nullptr;
    lastBranchNode->numNonNullBranches -= 1;
    return true;
  }
  
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  for(int i=0; i<len; i++){
    if (currNode->branch[findindex(prefix[i])]==nullptr) return nullptr; 
    currNode = currNode->branch[findindex(prefix[i])];
  }
  recursiveAddCompletions(currNode,currCompletions);
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

  listOfObjects<int>* currIndex = node->indices;
  while(currIndex != nullptr){
    listOfObjects<string>* temp = currCompletions;
    if (currCompletions == nullptr) currCompletions = new listOfObjects<string>(nameDict->getKeyAtIndex(currIndex->object));
    else {
      while(temp->next != nullptr) temp = temp->next;
      temp->next = new listOfObjects<string>(nameDict->getKeyAtIndex(currIndex->object));
      temp = temp->next;
    } 
    currIndex = currIndex->next;
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
