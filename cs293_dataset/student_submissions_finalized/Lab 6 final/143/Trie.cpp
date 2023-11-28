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
  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';
    if(currNode->branch[letter]==nullptr){
      currNode->branch[letter] = new TrieNode();
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[letter];
    listOfObjects <int> *currNodeindex = currNode->indices;
    if(i == len-1){
      currNode->isWord = true;
      if(currNode->indices == nullptr){
        currNode->indices = new listOfObjects <int> (indexOfName);
      }
      else{
        while(currNodeindex->next!=nullptr){
          if(currNodeindex->next->object==indexOfName){
            return false;
          }
          currNodeindex = currNodeindex->next;
        }
        currNodeindex->next = new listOfObjects <int> (indexOfName);
      }
    }
  }
  

  return true;
}

bool Trie::del(string wordInName, string name) {
  bool one = false;
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  if(isPresent(wordInName)){
    for(int i = 0 ;i < len; i++){
      int letter = toupper(wordInName.at(i)) - 'A';
      if(currNode->numNonNullBranches>=2 || (currNode->indices!=nullptr&&currNode->numNonNullBranches!=0)){
        lastBranchNode = currNode;
        lastBranchChar = letter;
      }
      else if(root->numNonNullBranches==1 && lastBranchNode==nullptr){
        lastBranchNode = root; 
        lastBranchChar = letter;
      }
      currNode = currNode->branch[letter];
      listOfObjects <int> *currNodeindex = currNode->indices;
      if(i == len-1){
        if(currNode->numNonNullBranches>=1 && currNode->indices->next==nullptr){
          currNode->indices = nullptr;
          currNode->isWord =false;
        }
        else{
        if(currNodeindex->object == nameDict->get(name)->value){
          if(currNodeindex->next!=nullptr){
            currNode->indices=currNode->indices->next;
          }
          
          else{
            one = true;
          }
        }
        else{
          while(currNodeindex->next!=nullptr){
            if(currNodeindex->next->object==nameDict->get(name)->value){
              currNodeindex->next = currNodeindex->next->next;
              break;
            }
            currNodeindex = currNodeindex->next;
          }
       }
      }
      if(one){
        lastBranchNode->numNonNullBranches--;
        lastBranchNode->branch[lastBranchChar] = nullptr;
      }
      }
  }
  }
  else{
    return false;
  }
  return true;
}
listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  for(int i = 0;i < len;i++){
    int letter = toupper(prefix.at(i)) - 'A';
    currNode = currNode->branch[letter];
    if(i == len-1){
      recursiveAddCompletions(currNode,currCompletions);
    }
  }
  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> * &currCompletions) {
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> * &currCompletions) {
  if(currCompletions==nullptr){
    listOfObjects<string> *head=  nullptr;
    listOfObjects<string> *tail=  nullptr;
    listOfObjects <int> *first = node->indices; 
    listOfObjects <string> *node = new listOfObjects <string> (nameDict->getKeyAtIndex(first->object));
    head = node;
    tail = node;
    while(first->next!=nullptr){
      first = first->next;
      listOfObjects <string> *node = new listOfObjects <string> (nameDict->getKeyAtIndex(first->object));
      tail->next = node;
      tail = node;
    }
    currCompletions = head;
    
    
  }
  
  else{
    listOfObjects<string> *head=  currCompletions;
    listOfObjects<string> *tail=  currCompletions;
    while(tail->next!=nullptr){
     tail = tail->next;
    }
    listOfObjects <int> *first = node->indices; 
    while(first!=nullptr){
      if(isPresentInCompletions(currCompletions,nameDict->getKeyAtIndex(first->object))){
        first = first->next;
      }
      else{
        listOfObjects <string> *node = new listOfObjects <string> (nameDict->getKeyAtIndex(first->object));
        tail->next = node;
        tail = node;
        first = first->next;
      }
    }
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