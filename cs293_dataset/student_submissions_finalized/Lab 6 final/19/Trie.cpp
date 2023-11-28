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
  

  for(int i = 0; i < len; i++){
    int letter = toupper(wordInName.at(i)) - 'A';
    if(currNode->branch[letter] == nullptr){
      currNode->numNonNullBranches += 1;
      currNode->branch[letter] =  new TrieNode();
    }
    currNode = currNode->branch[letter];
  }
  currNode->isWord = true;
  if(currNode->indices == nullptr){
    currNode->indices = new listOfObjects(indexOfName);
  }
  else{
    listOfObjects<int>* a;
    a = currNode->indices;
    while(a->next != nullptr){
      a = a->next;
    }
    a->next = new listOfObjects(indexOfName);
  }
  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = root;
  int lastBranchChar = -1;
  int len = wordInName.length();
  int i = 0;
  while(i < len){
    if(currNode->numNonNullBranches > 1 || currNode->isWord){
      lastBranchNode = currNode;
      int letter = toupper(wordInName.at(i)) - 'A';
      lastBranchChar = letter;
    }
    int letter = toupper(wordInName.at(i)) - 'A';
    currNode = currNode->branch[letter];
    i++;
  }

  //cout << currNode->indices->object << endl;
  if(currNode->numNonNullBranches > 0 && currNode->indices->next == nullptr){
    currNode->isWord = false;
    currNode->indices = nullptr;
    //HERE DELETE THE INDICES USING DELETE FUNCTION
    return true;
  }

  if(currNode->numNonNullBranches > 0 && currNode->indices->next != nullptr){
    listOfObjects<int>* a = currNode->indices;
    if(name.compare(nameDict->getKeyAtIndex(a->object)) == 0){
      currNode->indices = a->next;
      //HERE DELETE THE INDICES USING DELETE FUNCTION
      return true;
    }
    while(a != nullptr){
      if(name.compare(nameDict->getKeyAtIndex(a->next->object)) == 0){
        a->next = a->next->next;
      }
      a = a->next;
    }
    //HERE DELETE THE INDICES USING DELETE FUNCTION
    return true;
  }
  
  if(currNode->numNonNullBranches == 0 && currNode->indices->next !=  nullptr){
    listOfObjects<int>* a = currNode->indices;
    if(name.compare(nameDict->getKeyAtIndex(a->object)) == 0){
      currNode->indices = a->next;
      //HERE DELETE THE INDICES USING DELETE FUNCTION
      return true;
    }
    while(a != nullptr){
      if(name.compare(nameDict->getKeyAtIndex(a->next->object)) == 0){
        a->next = a->next->next;
        return true;
      }
      a = a->next;
    }
    //HERE DELETE THE INDICES USING DELETE FUNCTION
  }
  if(currNode->numNonNullBranches == 0 && currNode->indices->next == nullptr){
    if(lastBranchNode == root){
      root->numNonNullBranches -= 1;
      int letter = toupper(wordInName.at(0)) - 'A';
      root->branch[letter] = nullptr;
      //cout << "This is the bug" << endl;
      return true;
    }
    //cout << lastBranchNode->numNonNullBranches << endl;
    //cout << lastBranchChar << endl;
    //cout << lastBranchNode->isWord << endl;
    lastBranchNode->numNonNullBranches -= 1;
    lastBranchNode->branch[lastBranchChar] = nullptr;
    return true;
  }
}

listOfObjects<string>* Trie:: station(TrieNode* curr, listOfObjects<string>* end, listOfObjects<string>* totalcompletions){
  if(curr == nullptr){
    return end;
  }
  if(curr->isWord){
    listOfObjects<int>* a = curr->indices;
    while(a != nullptr){
      if(!isPresentInCompletions(totalcompletions,nameDict->getKeyAtIndex(a->object))){
        end->next = new listOfObjects<string> (nameDict->getKeyAtIndex(a->object));
        end = end->next;
        a = a->next;
      }
      else{
        a = a->next;
        continue;
      }
    }
    }
  if(curr->numNonNullBranches == 0){
    return end;
  }
  for (int i=0; i < 26; i++){
    end = station(curr->branch[i], end, totalcompletions);
  }
  return end;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("DUMB");
  for (int i = 0; i < len; i++){
    int letter = toupper(prefix.at(i)) - 'A';
    currNode = currNode->branch[letter];
  }
  station(currNode, currCompletions, currCompletions);
  currCompletions = currCompletions->next;
  return currCompletions;
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

  // Insert your code here
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
