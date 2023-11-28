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
  for(int i=0;i<len;i++){
    int index = toupper(wordInName.at(i)) - 'A';
    if(!currNode->branch[index]){
      currNode->branch[index] = new TrieNode();
      currNode->numNonNullBranches +=1;
    }
    currNode=currNode->branch[index];
  }
  //last trienode marked as leaf
  currNode->isWord=true;
  //singly linked list created at leaf
  listOfObjects<int> *last=currNode->indices;
  //when initial indices is empty
  if(last==NULL){
    currNode->indices= new listOfObjects<int>(indexOfName);
    return true;
  }
  //when initial indices contains some hash values
  while(last->next!=NULL){
    last = last->next;
  }
  last->next = new listOfObjects<int>(indexOfName);
  return true;
}



bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here
  TrieNode *present_node=nullptr;
  for(int i=0;i<len;i++){
    int index= toupper(wordInName.at(i)) - 'A';
    //for empty trie returning false
    if(!currNode->branch[index])return false;
    currNode=currNode->branch[index];
    if(currNode->isWord){
      present_node=currNode;
    }
  }
  //if the indices contains some hash values then enter this loop
  if(currNode->isWord){
    listOfObjects<int> *last=currNode->indices;
    //if indices contain only single hash value
    if(last->next==NULL){
      if(nameDict->getKeyAtIndex(last->object)==name){
        //delete(last);
        //currNode->indices=nullptr;
        last=last->next;
        currNode->isWord=false;
        return true;
      }
    }
    //if more than one hash values in indices
    else{
      if(nameDict->getKeyAtIndex(last->object)==name){
        //when the first hash value matches
        currNode->indices=last->next;
        //delete(last);
        return true;
      }
      while(nameDict->getKeyAtIndex(last->next->object)!=name && last->next!=NULL){
        //traverse to go to the point which matches
        last=last->next;
      }
      if(nameDict->getKeyAtIndex(last->next->object)==name){
        //matched.delete here.
        listOfObjects<int> *t=last->next;
        last->next=last->next->next;
        //delete(last->next);
        return true;
      }
      return false;
    }
  }
  //control reaches here when the indices for the wordInName is empty
  return false;
}



listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;

  // Insert your code here
  //to find the ending character of the given prefix
  for(int i=0;i<len;i++){
    int index=toupper(prefix.at(i)) - 'A';
    if(!currNode->branch[index]){
      return currCompletions;
    }
    currNode=currNode->branch[index];
  }
  //calling recursiveAddCompletions function which will add the stations in the currNode
  recursiveAddCompletions(currNode, *&currCompletions);
  return currCompletions;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
  //currCompletion passed by reference so that changes in it must be reflected outside the function
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
  //currCompletion passed by reference so that changes in it must be reflected outside the function
  // Insert your code here
  if(node->isWord){
    //to get the last hash value in indices
    listOfObjects<string> *last=currCompletions;
    //list of hash values created to get corresponding strings
    listOfObjects<int> *h_val=node->indices;
    //stores the strings corresponding to the hash values in h_val list
    listOfObjects<string> *final=new listOfObjects<string>(nameDict->getKeyAtIndex(h_val->object));
    if(!currCompletions) currCompletions=final;
    else{
      while(last->next !=NULL){
        //to get the last string in last list
        last=last->next;
      }
      last->next=final;
    }
    while(h_val->next !=NULL){
      //traversing the h_val list and storing hash values
      h_val=h_val->next;
      listOfObjects<string> *temp=new listOfObjects<string>(nameDict->getKeyAtIndex(h_val->object));
      //adding the new list to the final list
      final->next=temp;
      final=final->next;
    }
    final=currCompletions;
    return true;
  }
  //control reaches here if isWord for the input node is false
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
