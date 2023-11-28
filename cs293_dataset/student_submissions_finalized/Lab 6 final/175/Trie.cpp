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
  for (int i = 0; i < len; i++){ // go to the location
    int letter = toupper(wordInName.at(i)) - 'A';
    if (currNode->branch[letter] == nullptr){
      currNode->numNonNullBranches += 1; // increment this number
      currNode->branch[letter] = new TrieNode();
    }
    currNode = currNode->branch[letter];
  }
  currNode->isWord = true;
  if (currNode->indices == nullptr){
    currNode->indices = new listOfObjects<int>(indexOfName); // add the station name to indices
  }
  else{
    listOfObjects<int> *ind = currNode->indices, *ind1 = nullptr;
    while(ind != nullptr){
      ind1 = ind;
      ind = ind->next;
    }
    ind1->next = new listOfObjects<int>(indexOfName); // add the station name to indices
  }
  return true;
}

bool Trie::del(string wordInName, string name) {
  if (!(isPresent(wordInName))){ // to check if the word is present or not
    return false;
  }
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr; // stores the pointer whose branch needs to be deleted
  int lastBranchChar = -1; // the branch which is to be deleted
  int len = wordInName.length();
  for (int i = 0; i < len; i++){ // go to the location
    int letter = toupper(wordInName.at(i)) - 'A';
    if (i == 0){
      lastBranchNode = currNode;
      lastBranchChar = letter;
    }
    if (currNode->isWord || currNode->numNonNullBranches > 1){ // if the node has something following it then we cant delete it
      lastBranchNode = currNode;
      lastBranchChar = letter;
    }
    currNode = currNode->branch[letter];
  }
  listOfObjects<int> *ind_curr = currNode->indices, *ind_curr1 = nullptr;
  while (ind_curr != nullptr){
    if (name == nameDict->getKeyAtIndex(ind_curr->object)){ // remove the current station's name from the indices list
      break;
    }
    ind_curr1 = ind_curr;
    ind_curr = ind_curr->next;
  }
  if (ind_curr1 != nullptr){
    ind_curr1->next = ind_curr->next;
  }
  else{
    currNode->indices = ind_curr->next;
  }
  ind_curr = currNode->indices;
  if (ind_curr == nullptr && currNode->numNonNullBranches == 0){ // if nothing follows the current node then set the node to nullptr
    lastBranchNode->branch[lastBranchChar] = nullptr;
    lastBranchNode->numNonNullBranches -= 1;
  }
  else if (ind_curr == nullptr && currNode->numNonNullBranches != 0){ // else just set the variable isword to false
    currNode->isWord = false;
  }
  return true;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = nullptr;
  for (int i = 0; i < len; i++){ // go to the location
    int letter = toupper(prefix.at(i)) - 'A';
    if (currNode->branch[letter] == nullptr) {
      return nullptr;
    }
    currNode = currNode->branch[letter];
  }
  recursiveAddCompletions(currNode, currCompletions); // call this function
  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) {
  if (node->isWord) {
    if (!addCompletions(node, currCompletions)) { // calls this function
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

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *&currCompletions) { //add the node's indices to currcompletions
  TrieNode *tmp = node;
  listOfObjects<string> *currCompletions1 = currCompletions, *curr_tmp = nullptr;//curr_tmp points to the last nose of the list
  while(currCompletions1 != nullptr){
    curr_tmp = currCompletions1;
    currCompletions1 = currCompletions1->next;
  }
  listOfObjects<int> *tmp1 = tmp->indices;
  while(tmp1 != nullptr){
    if (curr_tmp != nullptr){
      if (!(isPresentInCompletions(currCompletions, nameDict->getKeyAtIndex(tmp1->object)))){
        curr_tmp->next = new listOfObjects<string>(nameDict->getKeyAtIndex(tmp1->object)); //add the value to the list
        curr_tmp = curr_tmp->next;
      }
    }
    else{
      currCompletions = new listOfObjects<string>(nameDict->getKeyAtIndex(tmp1->object)); //add the value to the list
      curr_tmp = currCompletions;
    }
    tmp1 = tmp1->next;
  }
  return true;
}

bool Trie::isPresentInCompletions(listOfObjects<string> *&completions, string name) {
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

void Trie::freeCompletionList(listOfObjects<string> *&completions) {
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
