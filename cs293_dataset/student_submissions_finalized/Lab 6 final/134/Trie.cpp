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
  for(int i=0; i<len; i++){
    int letter = toupper(wordInName.at(i)) - 'A';
    if(currNode->branch[letter] == NULL){
      currNode->branch[letter] = new TrieNode;
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[letter];
  }
  // found currNode
  if(currNode->indices == NULL){
    currNode->isWord = true;
    currNode->indices = new listOfObjects(indexOfName);
    return true;
  }
  // done if currNode has no indicces stroed
  listOfObjects<int> *currObjPar = currNode->indices;
  if(currObjPar->object == indexOfName)
    return true;
  while(currObjPar->next != NULL){
    if(indexOfName == currObjPar->next->object)
      return true;
    currObjPar = currObjPar->next;
  }
  // done if currNode has indices stored
  currObjPar->next = new listOfObjects(indexOfName);
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();
  for(int i=0; i<len; i++){
    int letter = toupper(wordInName.at(i)) - 'A';
    if(currNode->branch[letter] == NULL)
      return false;
    else{
      if(currNode->numNonNullBranches > 1){
        lastBranchNode = currNode;
        lastBranchChar = letter;
      }
      currNode = currNode->branch[letter];
    }
  }
  if(currNode->indices == NULL)
    return false; // if word exists as prefix
  // setting of lastBranchNode and lastBranchChar is done.
  // absence of wordInName is taken care
  listOfObjects<int> *prevcurrObj = nullptr;
  listOfObjects<int> *currObj = currNode->indices;
  while(currObj != NULL){
    if(name == nameDict->getKeyAtIndex(currObj->object)){
      if(prevcurrObj != nullptr)
        prevcurrObj->next = currObj->next;
      else{
        currNode->indices = currObj->next;
        if(currNode->indices == NULL)
          currNode->isWord = false;
      }
      break;
    }
    prevcurrObj = currObj;
    currObj = currObj->next;
  }
  if(currObj==NULL)
    return false;
  delete currObj;
  // setting and deleting done
  // absence of name is taken care
  if(currNode->indices == NULL && currNode->numNonNullBranches == 0){
    recursiveDelete(lastBranchNode->branch[lastBranchChar]);
    lastBranchNode->branch[lastBranchChar] = NULL;
    lastBranchNode->numNonNullBranches--;
  }
  // deletion of empty tree brach done if exists
  return true;
}

//void Trie::recursiveCompletions(TrieNode *node, listOfObjects<string> *currCompletions){

//}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  // traversing to proper currNode while returning if there is no match
  for(int i=0; i<len; i++){
    int letter = toupper(prefix.at(i)) - 'A';
    if(currNode->branch[letter] == NULL){
      return nullptr;
    }
    currNode = currNode->branch[letter];
  }
  // found currNode
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
/*
  listOfObjects<int> *currIntObj = node->indices;
  // this while loop goes through elements in list of node
  while(currIntObj != NULL){
    listOfObjects<string> *currIndexComp = currCompletions;
    string currInsString = nameDict->getKeyAtIndex(currIntObj->object);
    // if the currComplete is empty, first element is added
    if(currIndexComp == nullptr){
      currIndexComp = new listOfObjects(currInsString);
      currIntObj = currIntObj->next;
      continue;
    }
    // this loop goes through elements in list currComplete to check for repeatation
    while(currIndexComp->object != currInsString && currIndexComp->next != nullptr){
      currIndexComp = currIndexComp->next;
    }
    // if the match's found, it skips adding and continuous for next element of node's list (currIntObj)
    if(currIndexComp->object == currInsString){
      currIntObj = currIntObj->next;
      continue;
    }
    else{ // if there is no match, it safely adds element
      currIndexComp->next = new listOfObjects(currInsString);
      currIntObj = currIntObj->next;
    }
  }
*/
//////////////////////////////////////////////
  if(node->isWord==false)
    return false;
  listOfObjects<int> *currIntObj = node->indices;
  string currInsString = nameDict->getKeyAtIndex(currIntObj->object);
  listOfObjects<string> *varcurrComp = currCompletions;
  if(varcurrComp == NULL){
    varcurrComp = new listOfObjects(currInsString);
    currIntObj = currIntObj->next;
    currCompletions = varcurrComp;
  }
  // done inserting if currCompletions is empty
  while(varcurrComp->next != NULL){
    varcurrComp = varcurrComp->next;
  }
  // found the last entry in currCompletions, so it works as stack. 
  while(currIntObj!=nullptr){
    string currInsString = nameDict->getKeyAtIndex(currIntObj->object);
    varcurrComp->next = new listOfObjects(currInsString);
    varcurrComp = varcurrComp->next;
    currIntObj = currIntObj->next;
  }
  // inserted everything
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
