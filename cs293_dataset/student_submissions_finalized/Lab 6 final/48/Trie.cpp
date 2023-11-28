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
#include <cstring>
#include<bits/stdc++.h>
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
  //creates a charecter if it is not ther
  //keeps last word true
  //adds to the current linked list
  TrieNode *currNode = root;
  int len = wordInName.length();
  // Insert your code here
  for(int i=0;i<len;i++){
    int j=(wordInName[i]|32)-'a';
    if(currNode->branch[j]==nullptr){
      currNode->numNonNullBranches++;
      currNode->branch[j]=new TrieNode();
    }
    currNode=currNode->branch[j];
  }
  currNode->isWord=true;
  listOfObjects <int>* t=new listOfObjects<int>(indexOfName);
  t->next=currNode->indices;
  currNode->indices=t;
  return true;
}

bool Trie::del(string wordInName, string name) {
  //deltes the word
  //deletes the word from the linked list
  //last branch node is uopdated if it has more than one child
  //last branch char is index of child of last branch node  we want
  //recursive delete is called apropriately
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  // Insert your code here
  for(int i=0;i<len;i++){
    int j=(wordInName[i]|32)-'a';
    if(currNode->numNonNullBranches >1 || currNode->isWord){
      lastBranchNode=currNode;
      lastBranchChar=(wordInName[i]|32)-'a';
    }
    currNode=currNode->branch[j];
  }
  int index=nameDict->get(name)->value;
  if(currNode->indices->object == index){
    currNode->indices=currNode->indices->next;
    if(currNode->indices == nullptr){
      if(currNode->numNonNullBranches == 0 ){
        recursiveDelete(lastBranchNode->branch[lastBranchChar]);
        lastBranchNode->branch[lastBranchChar]=nullptr;
      }
      else{
        currNode->isWord=false;
      }
    }
  }
  else{
    listOfObjects <int>* t2=currNode->indices;
    while(t2->next!=nullptr){
      if(t2->next->object == index){
        t2->next=t2->next->next;
        break;
      }
      else{
        t2=t2->next;
      }
    }
  }
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here
  for(int i=0;i<len;i++){
    int j=(prefix[i]|32)-'a';
    currNode=currNode->branch[j];
  }
  currCompletions=new listOfObjects <string>("aa");
  recursiveAddCompletions(currNode,currCompletions);
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
  //merged to linked lists
  // Insert your code here
  listOfObjects <int>* t=node->indices;
  while(t!=nullptr){
    string x=nameDict->getKeyAtIndex(t->object);
    listOfObjects <string>* s=new listOfObjects <string>(x);
    s->next=currCompletions->next;
    currCompletions->next=s;
    t=t->next;
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
